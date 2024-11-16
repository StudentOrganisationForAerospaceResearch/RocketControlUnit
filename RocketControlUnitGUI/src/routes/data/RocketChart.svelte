<script lang="ts">
  import { T } from '@threlte/core';
  import { interactivity, GLTF } from '@threlte/extras';
  import { tweened } from 'svelte/motion';
  import { onMount, onDestroy } from 'svelte';
  import {
    getCollectionData,
    subscribeToCollection,
    unsubscribeFromCollection,
  } from '../../StoreService';
  import { cubicOut } from 'svelte/easing';

  type RecordData = { [key: string]: any };

  const path_to_rocket = "../../model/Pegasus_XL.glb";
  let gltf: any;

  

  interactivity();

  // Define tweened values for smoother transitions
  const rotationX = tweened(0, { duration: 1000, easing: cubicOut });
  const rotationY = tweened(0, { duration: 1000, easing: cubicOut });
  const rotationZ = tweened(0, { duration: 1000, easing: cubicOut });

  // Handle data updates
  function handleDataUpdate(data: RecordData) {
    const rawRotationX = parseFloat(data.gyro_x) || 0;
    const rawRotationY = parseFloat(data.gyro_y) || 0;
    const rawRotationZ = parseFloat(data.gyro_z) || 0;

    // Update tweened values
    rotationX.set(rawRotationX);
    rotationY.set(rawRotationY);
    rotationZ.set(rawRotationZ);
  }

  async function fetchInitialData() {
    await getCollectionData('Imu', 10, (pageData) => {
      if (pageData.length > 0) {
        handleDataUpdate(pageData[pageData.length - 1]);
      }
    });
  }

  onMount(() => {
    fetchInitialData();
    subscribeToCollection('Imu', handleDataUpdate);
  });

  onDestroy(() => {
    unsubscribeFromCollection('Imu');
  });
</script>

<!-- Model Container -->
<div class="model-container">
  <!-- Perspective Camera -->
  <T.PerspectiveCamera
    makeDefault
    fov={70}
    position={[0, 0, 5]}
    on:create={({ ref }) => ref.lookAt(0, 0, 0)}
  />

  <!-- Directional Light -->
  <T.DirectionalLight position={[10, 10, 10]} intensity={1} castShadow />

  <!-- GLTF Model -->
  <GLTF
    url={path_to_rocket}
    bind:gltf
    position={[0, 0, 0]}
    rotation={[$rotationX, $rotationY, $rotationZ]}
    scale={[0.5, 0.5, 0.5]}
  />
</div>

<style>
  /* Model Container Styles */
  .model-container {
    width: 1000px;
    height: 300px;
    margin: 20px;
    border-radius: 16px;
    /* overflow: hidden; */
    box-shadow: 0 15px 35px rgba(0, 255, 255, 0.1);
    position: relative;
    background: linear-gradient(135deg, #0f2027 0%, #203a43 50%, #2c5364 100%);
    display: flex;
    justify-content: center;
    align-items: center;
  }

  /* Canvas Styling */
  canvas {
    border-radius: 12px;
    width: 100%;
    height: 100%;
    display: block;
  }

  /* Responsive Design */
  @media (max-width: 480px) {
    .model-container {
      width: 90%;
      height: 250px;
      padding: 15px;
      margin: 10px auto;
    }
  }
</style>
