<script lang="ts">
	import LineChart from './LineChart.svelte'; 
	import MapChart from './MapChart.svelte';
	import RocketChart from './RocketChart.svelte';
	import {Canvas} from '@threlte/core';
  </script>
  
  <main>
	<!-- <div style="display: flex; flex-direction: column; align-items: center;">
	  <LineChart collection="Rcupressure" />
	  <LineChart collection="RcuTemperature" />
	 <LineChart collection="Imu" />
	</div> -->
<!-- 	
	<MapChart />  -->
	<div class="canvas-container">
		<Canvas>
			<RocketChart />
		</Canvas>
	</div>
	
	
  </main>
  
  <style>
	main {
	  display: flex;
	  flex-direction: row;
	  align-items: center;
	  justify-content: center;
	  padding: 20px;
	}

	.canvas-container{
		width:800px;
		height:600px;
	}
  </style>
  