<script lang="ts">
import { onMount } from 'svelte';
import HexaBox from './HexaBox.svelte';
import CompassRose from './compass-rose-dark.svelte';
import * as THREE from 'three';

let fieldNames = ['LAT','LON', 'ALT (TOTAL)', '', '', 'ALT-GEO'];
let fieldText = [1,2,3,' ',' ',6];

let container;

onMount(() => {
    container = document.createElement('div');
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, container.clientWidth / container.clientHeight, 0.1, 1000);
    const renderer = new THREE.WebGLRenderer();

    renderer.setSize(container.clientWidth, container.clientHeight);
    container.appendChild(renderer.domElement);

    const geometry = new THREE.BoxGeometry();
    const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
    const cube = new THREE.Mesh(geometry, material);
    scene.add(cube);

    camera.position.z = 5;

    const animate = function () {
        requestAnimationFrame(animate);

        // Use quaternion for rotation
        cube.quaternion.multiply(new THREE.Quaternion().setFromAxisAngle(new THREE.Vector3(0, 1, 0), 0.01));

        renderer.render(scene, camera);
};

animate();
});

</script>

<style>
    .gps-box {
        display: flex;
        justify-content: center; 
        width: 60vw;
    }
    .rocket-vis {
        display: flex;
        justify-content: center; 
        width: 80vw;
    }
</style>


<svelte:head></svelte:head>

<main>
	<p>ROCKET PAGE</p>

    <div class="flex-auto px-3.5 pt-3.5 pb-12 rounded-2xl border border-solid border-zinc-300 max-md:pr-5 max-md:max-w-full">
    </div> 
    
    <div class="gps-box">
        <HexaBox bind:fieldNames={fieldNames} bind:fieldTexts={fieldText}/>
    </div>

    <div class="rocket-vis">
        <svelte:component this={CompassRose}/>
        <div bind:this={container}></div>
    </div>
    
</main>