<script lang="ts">
  import { onMount, onDestroy } from 'svelte';
  import { fetchPaginatedData, subscribeToCollection, unsubscribeFromCollection } from '../../data'; // Import the new subscription function
  import type { Map, Marker } from 'leaflet'; // Import only the types statically

  type RecordData = { [key: string]: any };

  let map: Map | null = null;
  let L: typeof import('leaflet'); 
  let center: [number, number] = [51.505, -0.09]; 
  let realTimeMarker: Marker | null = null;
  let isUpdating = false;

  // Function to throttle updates
 // Function to throttle updates
function throttle(func: (...args: any[]) => void, limit: number) {
  let lastFunc: ReturnType<typeof setTimeout>; // Specify type for the timer
  let lastRan: number | undefined;
  return (...args: any[]) => {
    if (!lastRan) {
      func(...args);
      lastRan = Date.now();
    } else {
      clearTimeout(lastFunc);
      lastFunc = setTimeout(() => {
        if ((Date.now() - lastRan!) >= limit) {
          func(...args);
          lastRan = Date.now();
        }
      }, limit - (Date.now() - lastRan));
    }
  };
}

  // Function to fetch and process data one by one
  async function getData() {
    try {
      await fetchPaginatedData("Gps", throttledUpdateMapWithSingleRecord, 10); 
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  }

  // Function to update map with a single record
  function updateMapWithSingleRecord(data: RecordData[]) {
    if (!map || data.length === 0 || isUpdating) return;

    const record = data[0]; 
    const { latitude, longitude } = record;

    // Check for null or undefined values
    if (!latitude || !longitude || !latitude.minutes || !longitude.minutes) {
      console.error('Invalid data received for latitude or longitude:', record);
      return;
    }

    const lat = latitude.degrees + (latitude.minutes/6000000);
    const long = longitude.degrees + (longitude.minutes/600000);

    isUpdating = true;

    // Check if real-time marker exists
    if (realTimeMarker) {
      realTimeMarker.setLatLng([lat, long]).setOpacity(0.7).bindPopup(`Lat: ${lat}, Long: ${long}`).openPopup();
      // Smoother map panning effect
      map.flyTo([lat, long], map.getZoom(), { duration: 0.5 });
    } else {
      realTimeMarker = L.marker([lat, long], { 
        draggable: false, 
        autoPan: false, 
        autoPanPadding: [50, 50] 
      }).addTo(map)
        .bindPopup(`Lat: ${lat}, Long: ${long}`)
        .openPopup();
    }

    setTimeout(() => {
      isUpdating = false;
    }, 500); // Allow some time before updating again
  }

  // Throttle the update function to limit its execution frequency
  const throttledUpdateMapWithSingleRecord = throttle(updateMapWithSingleRecord, 1000);

  // Function to handle real-time updates
  function handleRealTimeUpdate(record: RecordData) {
    throttledUpdateMapWithSingleRecord([record]); // Convert single record to array for the update function
  }

  // On mount, initialize the map and start real-time tracking
  onMount(async () => {
    if (typeof window !== 'undefined') {
      L = await import('leaflet'); 

      map = L.map('map', {
        zoomControl: false,
        inertia: true,
        inertiaDeceleration: 1000
      }).setView(center, 20);

      L.tileLayer('http://{s}.google.com/vt/lyrs=s,h&x={x}&y={y}&z={z}', {
        maxZoom: 20,
        subdomains:['mt0','mt1','mt2','mt3']
      }).addTo(map);

      // Subscribe to real-time updates for the 'Gps' collection
      subscribeToCollection('Gps', handleRealTimeUpdate);

      // Fetch initial data
      getData();
    }
  });

  // On destroy, clean up subscriptions
  onDestroy(() => {
    unsubscribeFromCollection('Gps'); // Unsubscribe from real-time updates when component is destroyed
  });
</script>

<style>
  @import 'leaflet/dist/leaflet.css'; 

  #map {
    height: 50vh; 
    width: 50vh; 
  }
</style>

<!-- Map container -->
<div id="map"></div>
