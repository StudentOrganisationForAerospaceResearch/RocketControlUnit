<script lang='ts'>
	import { onMount } from 'svelte';
	import { writable } from 'svelte/store';
	import PocketBase from 'pocketbase';
	
	const PB = new PocketBase('http://127.0.0.1:8090');
	
	const latitude = writable();
	const longitude = writable();

	$: latitude_display = $latitude === undefined ? 'N/A' : $latitude ? 'ON' : 'OFF';
	$: longitude_display = $longitude === undefined ? 'N/A' : $longitude ? 'ON' : 'OFF';
	
	onMount(async () => {
	  // Subscribe to changes in the 'Gps' collection 
	  PB.collection('Gps').subscribe('*', function (e) {
		latitude.set(e.record.latitude);
		longitude.set(e.record.longitude);
	  });
	});
</script>


<div>
	<div class="latitude">
		<p>Latitude: {latitude_display}</p>
	</div>
	<div class="longitude">
		<p>Longitude: {longitude_display}</p>
	</div>
</div>


<!DOCTYPE html>
<html lang='ts'>
	<head>
		<meta charset="utf-8">
		<title>Display a map on a webpage</title>
		<meta name="viewport" content="initial-scale=1,maximum-scale=1,user-scalable=no">
		<link href="https://api.mapbox.com/mapbox-gl-js/v3.2.0/mapbox-gl.css" rel="stylesheet">
		<script src="https://api.mapbox.com/mapbox-gl-js/v3.2.0/mapbox-gl.js"></script>

		<style>
			body { margin: 0; padding: 0; }
			/* #map { position: absolute; top: 0; bottom: 0; width: 100%; } */
			#map { position: fixed; width:800px; height: 800px; }
		</style>

	</head>

	<body>
		<div id="map"></div>
		<script>
			mapboxgl.accessToken = 'add your token here';
			const map = new mapboxgl.Map({
				container: 'map', // container ID
				center: [-74.5, 40], // starting position [lng, lat]
				zoom: 9 // starting zoom
			});
		</script>
	</body>
</html>

