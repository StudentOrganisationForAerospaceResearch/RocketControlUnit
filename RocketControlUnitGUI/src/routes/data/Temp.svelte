<script lang="ts">
	import { onMount } from 'svelte';
	import { fetchPaginatedData } from '../../test'; 
	import { Chart, LineController, LineElement, PointElement, LinearScale, Title, CategoryScale } from 'chart.js';


	Chart.register(LineController, LineElement, PointElement, LinearScale, Title, CategoryScale);

	interface PressureData {
		pt1: number;
		pt2: number;
		pt3: number;
		pt4: number;
	}

	export let collection: string;

	let pressureData: PressureData[] = []; 
	let chart: Chart | null = null; 
	let canvasContainer: HTMLCanvasElement | null = null; 
	let MAX_DATA_POINTS = 10;
	let isUpdating = false; 

	function sendToChart(batchData: PressureData[]) {
		pressureData = [...pressureData, ...batchData]; 

		
		if (pressureData.length > MAX_DATA_POINTS) {
			pressureData = pressureData.slice(-MAX_DATA_POINTS); 
		}

		// Use requestAnimationFrame --> Needs to be worked on!
		if (!isUpdating) {
			isUpdating = true;
			requestAnimationFrame(() => {
				createOrUpdateChart();
				isUpdating = false;
			});
		}
	}

	
	onMount(() => {
		fetchPaginatedData(collection, sendToChart, 1).catch((error) => {
			console.error('Error fetching paginated data:', error);
		}); 
	});

	
	function createOrUpdateChart() {
		if (!canvasContainer) return; 

		const chartData = {
			labels: pressureData.map((_, index) => index.toString()), 
			datasets: [
				{ label: 'pt1', data: pressureData.map((d) => d.pt1), borderColor: 'red', fill: false },
				{ label: 'pt2', data: pressureData.map((d) => d.pt2), borderColor: 'green', fill: false },
				{ label: 'pt3', data: pressureData.map((d) => d.pt3), borderColor: 'blue', fill: false },
				{ label: 'pt4', data: pressureData.map((d) => d.pt4), borderColor: 'purple', fill: false },
			],
		};

		if (chart) {
			
			chart.data = chartData;
			chart.update();
		} else {
			chart = new Chart(canvasContainer, {
				type: 'line',
				data: chartData,
				options: {
					responsive: true,
					maintainAspectRatio: false,
					scales: {
						x: { 
							title: { display: true, text: 'Data Points', color: '#777' },
							grid: {
								color: 'rgba(200, 200, 200, 0.1)', // Light grid lines
							},
							ticks: {
								color: '#777', // X-axis label color
							}
						},
						y: { 
							title: { display: true, text: 'Pressure', color: '#777' }, 
							beginAtZero: true,
							grid: {
								color: 'rgba(200, 200, 200, 0.1)', // Light grid lines
							},
							ticks: {
								color: '#777', // Y-axis label color
							}
						},
					},
					plugins: {
						legend: {
							display: true,
							position: 'top',
							labels: {
								color: '#333', // Legend label color
								font: {
									size: 12,
									weight: 500
								}
							}
						},
						tooltip: {
							backgroundColor: 'rgba(0,0,0,0.7)',
							titleColor: '#FFF',
							bodyColor: '#FFF',
							cornerRadius: 4,
						}
					},
					elements: {
						line: {
							borderWidth: 2,
						},
						point: {
							radius: 3,
							hoverRadius: 5,
							backgroundColor: '#FFF',
							borderWidth: 1.5,
						}
					}
				},
			});
		}
	}
</script>

<!-- Canvas for the chart -->
<div class="chart-container">
	<h1 style="justify-contents: space-evenly">{collection} graph</h1>
	<canvas bind:this={canvasContainer}></canvas>
</div>

<style>
	.chart-container {
		display:flex;
		flex-direction: column;
		width: 400px; /* Set the desired square width */
		height: 300px; /* Set the desired square height */
		position: relative; /* Ensures the chart fits inside the container */
		background: linear-gradient(135deg, #495a8f 0%, #495f9f 100%); /* Gradient background */
		border-radius: 12px; /* Rounded corners */
		box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* Subtle shadow */
		padding: 20px; /* Padding around canvas */
		margin: 20px; /* Space around the chart container */
		justify-content: space-evenly;
		align-items: center;
	}

	canvas {
		width: 100%; /* Make canvas take full width of the container */
		height: 100%; /* Make canvas take full height of the container */
		display: block;
	}
</style>
