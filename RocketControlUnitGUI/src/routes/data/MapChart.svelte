<script lang="ts">
  import { onMount, onDestroy } from 'svelte';
  import {
    getCollectionData,
    subscribeToCollection,
    unsubscribeFromCollection,
  } from '../../StoreService';
  import type { Map, Marker } from 'leaflet';

  // Define the RecordData type
  interface RecordData {
    latitude: { degrees: number; minutes: number };
    longitude: { degrees: number; minutes: number };
    [key: string]: any; // Include other fields if necessary
  }

  let map: Map | null = null;
  let L: typeof import('leaflet');
  let center: [number, number] = [51.505, -0.09];
  let realTimeMarker: Marker | null = null;

  // Update map with new data
  function updateMap(record: RecordData) {
    if (!map) return;

    const { latitude, longitude } = record;

    if (!latitude || !longitude || !latitude.minutes || !longitude.minutes) {
      console.error('Invalid data for latitude or longitude:', record);
      return;
    }

    // const lat = latitude.degrees + latitude.minutes / 6000000;
    // const long = longitude.degrees + longitude.minutes / 600000;
    const lat = latitude.degrees
    const long = longitude.degrees

    if (realTimeMarker) {
      realTimeMarker.setLatLng([lat, long]).bindPopup(`Lat: ${lat}, Long: ${long}`).openPopup();
      map.flyTo([lat, long], map.getZoom());
    } else {
      realTimeMarker = L.marker([lat, long]).addTo(map).bindPopup(`Lat: ${lat}, Long: ${long}`).openPopup();
    }
  }

  // Fetch initial data from PocketBase
  async function fetchInitialData() {
    await getCollectionData('Gps', 10, (pageData: RecordData[]) => {
      if (pageData.length > 0) {
        updateMap(pageData[pageData.length - 1]); // Use the latest record
      }
    });
  }

  // Handle real-time updates
  function handleRealTimeUpdate(record: RecordData) {
    updateMap(record);
  }

  onMount(async () => {
    if (typeof window !== 'undefined') {
      L = await import('leaflet');

      map = L.map('map', { zoomControl: false }).setView(center, 13);

      L.tileLayer('http://{s}.google.com/vt/lyrs=s,h&x={x}&y={y}&z={z}', {
        maxZoom: 20,
        subdomains: ['mt0', 'mt1', 'mt2', 'mt3'],
      }).addTo(map);

      // Fetch initial data
      fetchInitialData();

      // Subscribe to real-time updates
      subscribeToCollection('Gps', handleRealTimeUpdate);
    }
  });

  onDestroy(() => {
    unsubscribeFromCollection('Gps');
  });
</script>

<style>
  /* Import Leaflet CSS */
  @import 'leaflet/dist/leaflet.css';

  /* Styles for the map container */
  .map-container {
    width: 400px;
    height: 300px;
    margin: 20px;
    border-radius: 16px;
    overflow: hidden;
    box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1); /* Neutral shadow */
    position: relative;
    background-color: #f8f9fa; /* Light gray background */
    display: flex;
    justify-content: center;
    align-items: center;
  }

  #map {
    height: 100%;
    width: 100%;
    border-radius: 12px;
  }

  /* Leaflet customizations */
  :global(.leaflet-container) {
    background: none !important;
  }

  /* Zoom control styles */
  :global(.leaflet-control-zoom) {
    border: none !important;
    background: none !important;
    box-shadow: none !important;
  }

  :global(.leaflet-control-zoom-in),
  :global(.leaflet-control-zoom-out) {
    background-color: #ffffff !important;
    color: #495057 !important;
    border: 1px solid #ced4da !important;
    width: 36px !important;
    height: 36px !important;
    line-height: 34px !important;
    font-size: 20px !important;
    transition: all 0.3s ease;
    border-radius: 4px !important;
  }

  :global(.leaflet-control-zoom-in:hover),
  :global(.leaflet-control-zoom-out:hover) {
    background-color: #e9ecef !important;
    color: #212529 !important;
  }

  /* Popup styles */
  :global(.leaflet-popup-content-wrapper) {
    background-color: #ffffff !important;
    color: #212529 !important;
    border-radius: 8px !important;
    box-shadow: 0 2px 15px rgba(0, 0, 0, 0.1) !important;
  }

  :global(.leaflet-popup-tip) {
    background-color: #ffffff !important;
  }

  :global(.leaflet-popup-close-button) {
    color: #6c757d !important;
  }

  /* Responsive design adjustments */
  @media (max-width: 480px) {
    .map-container {
      width: 90%;
      height: 250px;
      padding: 15px;
      margin: 10px auto;
    }
  }
</style>


<!-- Map container -->
<div class="map-container">
  <div id="map"></div>
</div>
