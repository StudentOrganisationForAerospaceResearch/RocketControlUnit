// StoreService.ts
import PocketBase from 'pocketbase';

const pb = new PocketBase('http://127.0.0.1:8090');
let isAuthenticated = false;
pb.autoCancellation(false);

// Define the RecordData type explicitly for PocketBase records
export type RecordData = { [key: string]: any };

// Function to authenticate PocketBase before any data fetch or subscription
async function authenticate() {
    if (!isAuthenticated) {
        const email = import.meta.env.VITE_EMAIL;
        const password = import.meta.env.VITE_PASSWORD;

        try {
            await pb.admins.authWithPassword(email, password);
            isAuthenticated = true;
            console.log('Authenticated successfully');
        } catch (error) {
            console.error('Authentication failed:', error);
            throw new Error('Authentication failed');
        }
    }
}

/**
 * Fetch paginated data from the specified collection in PocketBase.
 * @param collectionName The name of the collection to fetch data from.
 * @param batchSize The number of records to fetch per page.
 * @param onPageFetched Callback function to process fetched records.
 */
export async function getCollectionData(
    collectionName: string,
    batchSize: number,
    onPageFetched: (data: RecordData[]) => void
): Promise<void> {
    await authenticate();

    try {
        const response = await pb.collection(collectionName).getList(1, batchSize, {
            sort: '-created', // Fetch the most recent records first
        });

        if (response.items.length > 0) {
            onPageFetched(response.items); // Send data to the callback
        } else {
            console.warn(`No data found for collection: ${collectionName}`);
        }
    } catch (error) {
        console.error(`Error fetching data for collection ${collectionName}:`, error);
    }
}

/**
 * Subscribe to a collection in PocketBase for real-time updates.
 * @param collectionName The name of the collection to subscribe to.
 * @param callback Callback function to process new real-time updates.
 */
export async function subscribeToCollection(collectionName: string, callback: (data: RecordData) => void) {
    await authenticate();

    try {
        pb.collection(collectionName).subscribe('*', (e) => {
            if (e.record) {
                callback(e.record);
            } else {
                console.warn(`Received empty record in collection ${collectionName} real-time update.`);
            }
        });
        console.log(`Subscribed to real-time updates for collection: ${collectionName}`);
    } catch (error) {
        console.error(`Error subscribing to collection ${collectionName}:`, error);
    }
}

/**
 * Unsubscribe from a collection in PocketBase to stop real-time updates.
 * @param collectionName The name of the collection to unsubscribe from.
 */
export function unsubscribeFromCollection(collectionName: string) {
    try {
        pb.collection(collectionName).unsubscribe('*');
        console.log(`Unsubscribed from real-time updates for collection: ${collectionName}`);
    } catch (error) {
        console.error(`Error unsubscribing from collection ${collectionName}:`, error);
    }
}
    