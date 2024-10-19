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

  // Smoothed target rotation values
  let smoothedRotationX = 0;
  let smoothedRotationY = 0;
  let smoothedRotationZ = 0;

  // Rotation speed for smooth animation
  const rotationSpeed = 0.002;

  // Smoothing factor for EMA (between 0 and 1)
  const smoothingFactor = 0.1; // Adjust this value as needed

  // Handle data updates from real-time subscription
  function handleDataUpdate(data: RecordData) {
    // Parse the gyro values safely
    const rawRotationX = parseFloat(data.gyro_x) || 0;
    const rawRotationY = parseFloat(data.gyro_y) || 0;
    const rawRotationZ = parseFloat(data.gyro_z) || 0;

    // Apply Exponential Moving Average for smoothing
    smoothedRotationX = smoothingFactor * rawRotationX + (1 - smoothingFactor) * smoothedRotationX;
    smoothedRotationY = smoothingFactor * rawRotationY + (1 - smoothingFactor) * smoothedRotationY;
    smoothedRotationZ = smoothingFactor * rawRotationZ + (1 - smoothingFactor) * smoothedRotationZ;
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
    fetchPaginatedData('Imu', handleFirstBatch, 1); // Adjust batch size if needed

    // Subscribe to real-time updates after initial data fetch
    subscribeToCollection('Imu', handleDataUpdate);
  });

  onDestroy(() => {
    // Clean up the subscription when the component is destroyed
    unsubscribeFromCollection('Imu');
  });

  // Use frame to update rotation smoothly
  useFrame((ctx, delta) => {
    // Interpolate towards the smoothed rotations for smooth animation
    currentRotationX += (smoothedRotationX - currentRotationX) * rotationSpeed * delta;
    currentRotationY += (smoothedRotationY - currentRotationY) * rotationSpeed * delta;
    currentRotationZ += (smoothedRotationZ - currentRotationZ) * rotationSpeed * delta;
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
