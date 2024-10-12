<script lang="ts">
  import { T, useFrame } from '@threlte/core';
  import { interactivity, GLTF } from '@threlte/extras';
  import { onMount, onDestroy } from 'svelte';
  import {
    fetchPaginatedData,
    subscribeToCollection,
    unsubscribeFromCollection
  } from '../../data';

  type RecordData = { [key: string]: any };

  const path_to_rocket = "/Pegasus_XL.glb";
  let gltf: any;

  interactivity();

  // Fields we're interested in
  const fields = ['gyro_x', 'gyro_y', 'gyro_z'];

  // Current rotation values
  let currentRotationX = 0;
  let currentRotationY = 0;
  let currentRotationZ = 0;

  // Target rotation values based on fetched data
  let targetRotationX = 0;
  let targetRotationY = 0;
  let targetRotationZ = 0;

  // Rotation speed for smooth animation
  const rotationSpeed = 1;

  // Handle data updates from real-time subscription
  function handleDataUpdate(data: RecordData) {
    // Parse the gyro values safely
    targetRotationX = parseFloat(data.gyro_x) || 0;
    targetRotationY = parseFloat(data.gyro_y) || 0;
    targetRotationZ = parseFloat(data.gyro_z) || 0;
  }

  // Handle the first batch of fetched paginated data
  function handleFirstBatch(batchData: RecordData[]) {
    if (batchData.length > 0) {
      // Use the latest record from the initial fetch
      const latestRecord = batchData[batchData.length - 1];
      handleDataUpdate(latestRecord);
    } else {
      console.warn('No records fetched for initial data.');
    }
  }

  onMount(() => {
    // Fetch existing paginated data from PocketBase
    fetchPaginatedData('Imu', handleFirstBatch, 10); // Adjust batch size if needed

    // Subscribe to real-time updates after initial data fetch
    subscribeToCollection('Imu', handleDataUpdate);
  });

  onDestroy(() => {
    // Clean up the subscription when the component is destroyed
    unsubscribeFromCollection('Imu');
  });

  // Use frame to update rotation smoothly
  useFrame((ctx, delta) => {
    // 'delta' is the time since last frame in seconds

    // Interpolate towards the target rotations for smooth animation
    currentRotationX += (targetRotationX - currentRotationX) * rotationSpeed * delta;
    currentRotationY += (targetRotationY - currentRotationY) * rotationSpeed * delta;
    currentRotationZ += (targetRotationZ - currentRotationZ) * rotationSpeed * delta;
  });
</script>

<T.PerspectiveCamera
  makeDefault
  position={[10, 20, 20]}
  on:create={({ ref }) => {
    ref.lookAt(0, 0, 0);
  }}
/>

<T.DirectionalLight position={[10, 5, 10]} castShadow />

<GLTF
  url={path_to_rocket}
  bind:gltf
  position={[0, 0, 0]}
  rotation={[currentRotationX, currentRotationY, currentRotationZ]}
/>
