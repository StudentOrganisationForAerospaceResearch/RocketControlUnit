<script lang="ts">
    import { onMount } from 'svelte';
    import PocketBase from 'pocketbase';
    import { writable } from 'svelte/store';
    import type { RecordModel } from 'pocketbase';

    // Create a writable store to hold the sensor data
    export const sensorData = writable<RecordModel | null>(null);

    let PB;
           
    onMount(() => {
        PB = new PocketBase("http://127.0.0.1:8090");

        // Subscribe to changes in the 'sensors' collection
        PB.collection('sensors').subscribe('*', function (e) {
            // Update the sensor data store whenever a change is detected
            sensorData.set(e.record);
        });
    });
</script>

<svelte:head></svelte:head>

<div class="sensor-data">
    <h2>Sensor Data</h2>
    <p>PressureTransducer: {$sensorData && 'tc1' in $sensorData ? $sensorData.tc1 : 'N/A'}</p>
</div>

<style>
    .sensor-data {
        display: flex;
        flex-direction: column;
        align-items: center;
        padding: 1em;
    }

    .sensor-data h2, .sensor-data p {
        margin: 0;
        text-align: center;
    }
</style>