<script lang="ts">
import { onMount } from 'svelte';
import HexaBox from './HexaBox.svelte';
import CompassRose from './compass-rose-dark.svelte';
import { Canvas } from '@threlte/core'
import RocketVis from './rocketvis.svelte'
import Settings from './setpane.svelte'
let autoRotate: boolean = false
let enableDamping: boolean = true
let rotateSpeed: number = 1
let zoomToCursor: boolean = false
let zoomSpeed: number = 1
let minPolarAngle: number = 0
let maxPolarAngle: number = Math.PI
let enableZoom: boolean = true

let fieldNames = ['LAT','LON', 'ALT (TOTAL)', '', '', 'ALT-GEO'];
let fieldText = [1,2,3,' ',' ',6];

onMount(() => {
});

</script>

<style>
    .gps-box {
        display: flex;
        justify-content: center; 
        width: 60vw;
    }
    .rocket-vis {
        position: relative;
        display: flex;
        justify-content: center; 
        align-items: center;
        width: 80vw;
        height: 40vh;
    }
    .rocket-vis-3d {
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        display: flex;
        justify-content: center;
        width: 70vw;
        height: 30vh;
    }
</style>

<main>
	<p>ROCKET PAGE</p>

    <div class="flex-auto px-3.5 pt-3.5 pb-12 rounded-2xl border border-solid border-zinc-300 max-md:pr-5 max-md:max-w-full">
    </div> 
    
    <div class="gps-box">
        <HexaBox bind:fieldNames={fieldNames} bind:fieldTexts={fieldText}/>
    </div>

    <!-- <canvas bind:this={container}></canvas> -->

    <!-- <div class="rocket-vis">
        <svelte:component this={CompassRose}/>
        <div class="rocket-vis-3d">
        <Canvas>
            <RocketVis
              {enableDamping}
              {autoRotate}
              {rotateSpeed}
              {zoomToCursor}
              {zoomSpeed}
              {minPolarAngle}
              {maxPolarAngle}
              {enableZoom}
            />
          </Canvas>
        </div>
    </div> -->

    <div class="rocket-vis">
        <svelte:component this={CompassRose}/>
            <div class="rocket-vis-3d">
                <Canvas>
                    <RocketVis
                      {enableDamping}
                      {autoRotate}
                      {rotateSpeed}
                      {zoomToCursor}
                      {zoomSpeed}
                      {minPolarAngle}
                      {maxPolarAngle}
                      {enableZoom}
                    />
                </Canvas>
            </div>
    </div>

    <div class="rocket-vis">

      </div>
      <!-- <Settings
        bind:enableDamping
        bind:autoRotate
        bind:rotateSpeed
        bind:zoomToCursor
        bind:zoomSpeed
        bind:minPolarAngle
        bind:maxPolarAngle
        bind:enableZoom
      /> -->
</main>