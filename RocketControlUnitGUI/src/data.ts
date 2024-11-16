  // data.ts
  import PocketBase from 'pocketbase';
  

  const ADMIN_EMAIL: string = import.meta.env.VITE_EMAIL;
  const ADMIN_PASSWORD: string = import.meta.env.VITE_PASSWORD;


  const pb = new PocketBase('http://127.0.0.1:8090');
  pb.autoCancellation(false);

  let isAuthenticated = false;



  // Function to authenticate the admin user
  export async function authenticate() {
    if (!isAuthenticated) {
      await pb.admins.authWithPassword(ADMIN_EMAIL, ADMIN_PASSWORD);
      isAuthenticated = true;
    }
  }

  type RecordData = { [key: string]: any };
  export type AllData = { [collectionName: string]: RecordData[] };

  // Fetch paginated data with existing logic
  export async function fetchPaginatedData(
    collectionName: string,
    sendToChart: (data: RecordData[]) => void,
    batchSize: number = 10
  ) {
    console.log(`Fetching data from collection: ${collectionName}`);
    let page = 1;
    let hasMoreData = true;

    try {
      await authenticate(); // Authenticate once before fetching data

      while (hasMoreData) {
        console.log('Fetching data from collection:', collectionName, 'Page:', page);
        const records = await pb.collection(collectionName).getList(page, batchSize);
        console.log('Fetched records:', records.items);

        if (records.items.length === 0) {
          console.warn(`No records found for ${collectionName} on page ${page}.`);
          break;
        }

        const dynamicKeys = Object.keys(records.items[0]).filter(key => key !== 'id' && key !== 'created');

        const transformedBatch: RecordData[] = records.items.map((record: RecordData) => {
          const transformedRecord: RecordData = {};
          dynamicKeys.forEach(key => {
            transformedRecord[key] = record[key];
          });
          return transformedRecord;
        });

        console.log('Transformed batch:', transformedBatch);
        sendToChart(transformedBatch);

        if (records.items.length < batchSize) {
          hasMoreData = false;
        } else {
          page += 1;
        }
      }
      console.log('All data fetched for collection:', collectionName);
    } catch (error) {
      console.error('Error fetching paginated data for collection:', collectionName, error);
    }
  }

  // Real-time subscription to a collection
  export async function subscribeToCollection(
    collectionName: string,
    handleDataUpdate: (data: RecordData) => void
  ) {
    try {
      await authenticate(); // Ensure we're authenticated before subscribing

      // Subscribe to the collection for any changes
      pb.collection(collectionName).subscribe('*', function (e) {
        console.log(`Received real-time update for collection ${collectionName}:`, e.record);
        handleDataUpdate(e.record);
      });

      console.log(`Subscribed to real-time updates for collection: ${collectionName}`);
    } catch (error) {
      console.error(`Error subscribing to collection ${collectionName}:`, error);
    }
  }

  // Function to unsubscribe from a collection (optional)
  export async function unsubscribeFromCollection(collectionName: string) {
    try {
      await authenticate(); // Ensure we're authenticated before unsubscribing

      // Unsubscribe from the collection
      pb.collection(collectionName).unsubscribe('*');

      console.log(`Unsubscribed from real-time updates for collection: ${collectionName}`);
    } catch (error) {
      console.error(`Error unsubscribing from collection ${collectionName}:`, error);
    }
  }
