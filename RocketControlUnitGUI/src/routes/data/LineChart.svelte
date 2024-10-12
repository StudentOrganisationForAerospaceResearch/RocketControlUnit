<script lang="ts">
	import { onMount, onDestroy } from 'svelte';
	import { fetchPaginatedData, subscribeToCollection, unsubscribeFromCollection } from '../../data';
	import { Chart, LineController, LineElement, PointElement, LinearScale, Title, CategoryScale } from 'chart.js';
  
	Chart.register(LineController, LineElement, PointElement, LinearScale, Title, CategoryScale);
  
	interface RecordData {
	  [key: string]: any;
	}
  
	export let collection: string;
	export let fields: string[] = [];
  
	let chartData: RecordData[] = [];
	let chart: Chart | null = null;
	let canvasContainer: HTMLCanvasElement | null = null;
	const MAX_DATA_POINTS = 10;
	let isUpdating = false;
	let dynamicFields: string[] = [];
  

	async function getInitialData() {
	  try {
		await fetchPaginatedData(collection, handleFirstBatch, 1);
	  } catch (error) {
		console.error(`Error fetching initial data for ${collection}:`, error);
	  }
	}
  
	function sendToChart(batchData: RecordData[]) {
	  chartData = [...chartData, ...batchData];
  
	  if (chartData.length > MAX_DATA_POINTS) {
		chartData = chartData.slice(-MAX_DATA_POINTS);
	  }
  
	  if (!isUpdating) {
		isUpdating = true;
		requestAnimationFrame(() => {
		  createOrUpdateChart();
		  isUpdating = false;
		});
	  }
	}
  
	async function handleFirstBatch(batchData: RecordData[]) {
	  console.log('Fetched batch data for', collection, ':', batchData);
	  if (batchData.length > 0) {
		determineFields(batchData[0]);
		const transformedBatch = batchData.map(transformData);
		console.log('Transformed batch data for', collection, ':', transformedBatch);
		sendToChart(transformedBatch);
	  } else {
		console.warn('No records fetched for', collection);
	  }
	}
  
	function determineFields(record: RecordData) {
	  if (fields.length === 0) {
		dynamicFields = Object.keys(record).filter((key) => key !== 'id' && key !== 'created');
	  }
	}
  
	function transformData(record: RecordData): RecordData {
	  const dataFields = fields.length ? fields : dynamicFields;
	  const transformed: RecordData = {};
	  dataFields.forEach(field => {
		transformed[field] = record[field];
	  });
	  return transformed;
	}
  
	function createOrUpdateChart() {
	  if (!canvasContainer) return;
  
	  const dataFields = fields.length ? fields : dynamicFields;
	  if (dataFields.length === 0) {
		console.warn(`No fields available for chart creation for ${collection}.`);
		return;
	  }
  
	  const chartConfigData = {
		labels: chartData.map((_, index) => index.toString()),
		datasets: dataFields.map((field) => ({
		  label: field,
		  data: chartData.map((d) => d[field] !== undefined ? d[field] : 0),
		  borderColor: generateColorForField(field),
		  fill: false,
		})),
	  };
  
	  console.log('Chart configuration data for', collection, ':', chartConfigData);
  
	  if (chart) {
		chart.data = chartConfigData;
		chart.update();
	  } else {
		chart = new Chart(canvasContainer, {
		  type: 'line',
		  data: chartConfigData,
		  options: {
			responsive: true,
			maintainAspectRatio: false,
			scales: {
			  x: {
				title: { display: true, text: 'Data Points', color: '#777' },
				grid: { color: 'rgba(200, 200, 200, 0.1)' },
				ticks: { color: '#777' }
			  },
			  y: {
				title: { display: true, text: 'Value', color: '#777' },
				beginAtZero: true,
				grid: { color: 'rgba(200, 200, 200, 0.1)' },
				ticks: { color: '#777' }
			  },
			},
			plugins: {
			  legend: {
				display: true,
				position: 'top',
				labels: { color: '#333', font: { size: 12, weight: 500 } }
			  },
			  tooltip: {
				backgroundColor: 'rgba(0,0,0,0.7)',
				titleColor: '#FFF',
				bodyColor: '#FFF',
				cornerRadius: 4,
			  }
			},
			elements: {
			  line: { borderWidth: 2 },
			  point: { radius: 3, hoverRadius: 5, backgroundColor: '#FFF', borderWidth: 1.5 },
			}
		  },
		});
	  }
	}
  
	function generateColorForField(field: string): string {
	  const colors = ['#FF0000', '#00FF00', '#0000FF', '#FFFF00', '#FF00FF', '#00FFFF'];
	  const index = fields.length ? fields.indexOf(field) : dynamicFields.indexOf(field);
	  return colors[index % colors.length];
	}
  
	// Function to handle real-time updates
	function handleRealTimeUpdate(record: RecordData) {
	  const transformedRecord = transformData(record);
	  sendToChart([transformedRecord]);
	}
  
	// On mount, fetch initial data and start real-time updates
	onMount(() => {
	  getInitialData(); // Fetch initial data
	  subscribeToCollection(collection, handleRealTimeUpdate); // Subscribe to real-time updates
	});
  
	// On destroy, clean up subscriptions
	onDestroy(() => {
	  unsubscribeFromCollection(collection); // Unsubscribe from real-time updates when component is destroyed
	});
  </script>
  
  <div class="chart-container">
	<h1>{collection} Graph</h1>
	<canvas bind:this={canvasContainer}></canvas>
  </div>
  
  <style>
	.chart-container {
	  display: flex;
	  flex-direction: column;
	  width: 400px;
	  height: 300px;
	  position: relative;
	  background: linear-gradient(135deg, #495a8f 0%, #495f9f 100%);
	  border-radius: 12px;
	  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
	  padding: 20px;
	  margin: 20px;
	  justify-content: space-evenly;
	  align-items: center;
	}
  
	canvas {
	  width: 100%;
	  height: 100%;
	  display: block;
	}
  </style>
  