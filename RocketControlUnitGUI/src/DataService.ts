// src/data/DataService.ts
import PocketBase from 'pocketbase';



export class DataService {
  private pocketBaseInstance = new PocketBase('http://127.0.0.1:8090');
  private isAuthenticated = false;
  

  async authenticate(email: string, password: string) {
    if (!this.isAuthenticated) {
      await this.pocketBaseInstance.admins.authWithPassword(email, password);
      this.isAuthenticated = true;
      
    }
  }

  async fetchPaginatedData(collectionName: string, page: number, batchSize: number) {
    return await this.pocketBaseInstance.collection(collectionName).getList(page, batchSize);
  }

  subscribeToCollection(collectionName: string, callback: (data: any) => void) {
    this.pocketBaseInstance.collection(collectionName).subscribe('*', (e) => callback(e.record));
    console.log(`Subscribed to real-time updates for collection: ${collectionName}`);
  }

  unsubscribeFromCollection(collectionName: string) {
    this.pocketBaseInstance.collection(collectionName).unsubscribe('*');
    console.log(`Unsubscribed from real-time updates for collection: ${collectionName}`);
  }
}
