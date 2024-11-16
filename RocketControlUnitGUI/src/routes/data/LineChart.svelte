<script lang="ts">
    import { onMount, onDestroy } from 'svelte';
    import { Chart, LineController, LineElement, PointElement, LinearScale, Title, CategoryScale } from 'chart.js';
    import { subscribeToCollection, unsubscribeFromCollection, getCollectionData } from '../../StoreService';

    Chart.register(LineController, LineElement, PointElement, LinearScale, Title, CategoryScale);

    export let collection: string;
    export let fields: string[] = [];
    export let maxDataPoints: number = 10;

    interface RecordData {
        [key: string]: number | string;
    }

    let chart: Chart | null = null;
    let canvasContainer: HTMLCanvasElement | null = null;
    let dynamicFields: string[] = [];
    let chartData: RecordData[] = [];
    let indexCounter: number = 1; 

    function initializeChart(data: RecordData[]) {
        if (!canvasContainer) return;

        dynamicFields = fields.length ? fields : Object.keys(data[0] || {}).filter(key => key !== 'id' && key !== 'created');

        const labels = Array.from({ length: data.length }, (_, i) => indexCounter + i); // Increment by 1 for each point
        const datasets = dynamicFields.map(field => ({
            label: field,
            data: data.map(d => d[field] as number || 0),
            borderColor: '#FFFFFF',
            backgroundColor: '#FFFFFF',
            borderWidth: 2,
            pointRadius: 5,
            pointHoverRadius: 7,
            pointBackgroundColor: '#FFFFFF',
            fill: false,
        }));

        chart = new Chart(canvasContainer, {
            type: 'line',
            data: { labels, datasets },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                animation: false, // Disable animation for instant updates
                scales: {
                    x: {
                        title: { display: true, text: 'Index Counter', color: '#FFFFFF' },
                        grid: { color: 'rgba(255, 255, 255, 0.3)' },
                        ticks: { color: '#FFFFFF' }
                    },
                    y: {
                        title: { display: true, text: 'Value', color: '#FFFFFF' },
                        beginAtZero: true,
                        grid: { color: 'rgba(255, 255, 255, 0.3)' },
                        ticks: { color: '#FFFFFF' }
                    },
                },
                plugins: {
                    legend: { display: true, labels: { color: '#FFFFFF' } },
                    title: {
                        display: true,
                        text: `${collection} Graph`,
                        color: '#FFFFFF',
                        font: { size: 18, weight: 'bold' }
                    }
                },
            },
        });
    }

    function updateChart(data: RecordData[]) {
        if (!chart) return;

        const labels = Array.from({ length: data.length }, (_, i) => indexCounter + i); // Update labels incrementally
        chart.data.labels = labels;

        // Update datasets with new rolling window data
        chart.data.datasets.forEach((dataset, i) => {
            dataset.data = data.map(d => d[dynamicFields[i]] as number || 0);
        });

        chart.update('none'); // Use 'none' to update instantly without animations
    }

    function handleRollingWindow(record: RecordData) {
        chartData.push(record);

        // Maintain a rolling window of maxDataPoints
        if (chartData.length > maxDataPoints) {
            chartData.shift();
            indexCounter += 1; // Increment the indexCounter by 1 when shifting data
        }

        updateChart(chartData);
    }

    onMount(() => {
        // Fetch initial data
        getCollectionData(collection, maxDataPoints, (pageData) => {
            chartData = pageData.slice(-maxDataPoints); // Keep only the most recent records

            if (!chart) {
                initializeChart(chartData);
            } else {
                updateChart(chartData);
            }
        });

        // Subscribe to real-time updates
        subscribeToCollection(collection, handleRollingWindow);
    });

    onDestroy(() => {
        // Unsubscribe when the component is destroyed
        unsubscribeFromCollection(collection);
    });
</script>

<div class="chart-container">
    <canvas bind:this={canvasContainer}></canvas>
</div>

<style>
    .chart-container {
        display: flex;
        flex-direction: column;
        width: 400px;
        height: 300px;
        position: relative;
        background: linear-gradient(135deg, #0f2027 0%, #203a43 50%, #2c5364 100%);
        border-radius: 16px;
        box-shadow: 0 15px 35px rgba(0, 255, 255, 0.1);
        padding: 20px;
        margin: 20px;
        justify-content: center;
        align-items: center;
        overflow: hidden;
    }

    canvas {
        width: 100%;
        height: calc(100% - 33px);
        display: block;
        border-radius: 12px;
        background-color: rgba(255, 255, 255, 0.05);
        box-shadow: inset 0 0 15px rgba(0, 255, 255, 0.1);
    }
</style>
