<script lang="ts">
	import { PB } from '$lib/database-client';
	import { modeCurrent } from '@skeletonlabs/skeleton';
	import { onMount } from 'svelte';

	let data = [];

	var options: any = {
        series: [{
          data: data.slice()
        }],
		title: {
          text: 'Dynamic Updating Chart',
          align: 'right',
		  offsetY: 30,
		  style: {
			color: '#ff22ff',
		  },
        },
		grid: {
			show: true,
			borderColor: '#ff22ff',
			yaxis: {
				lines: {
					show: true
				}
			}, 
		},

        chart: {
          id: 'realtime',
          height: 350,
          type: 'line',
          animations: {
            enabled: true,
            easing: 'linear',
            dynamicAnimation: {
              speed: 500
            }
          },
          toolbar: {
            show: false
          },
          zoom: {
            enabled: false
          }
        },
        dataLabels: {
          enabled: false
        },
        stroke: {
          curve: 'smooth'
        },
        markers: {
          size: 0
        },
        legend: {
          show: false
        },
		xaxis: {
			type: 'category',
			tickPlacement: 'on',
			position: 'bottom',
			range: 10,
			labels: {
				show: true,
				hideOverlappingLabels: true,
				style: {
					colors: "#ff22ff",
				},
			},
			axisBorder: {
				color: '#ff22ff',
			},
			axisTicks: {
				show: true,
				color: '#ff22ff',
			},
			
			title: {
				text: "x axis name",
				style: {
					color: "#ff22ff",
				},
			},
		},
		yaxis: {},
		tooltip: {
			theme: "light"
		},
    };

	var chart:any = null;

	async function make_line_chart(options: any) {
		if ($modeCurrent){
			options = change_options_for_mode("light", options);
		} else{
			options = change_options_for_mode("dark", options);
		}

		console.log(options)

		const ApexCharts = (await import('apexcharts')).default
		chart = new ApexCharts(document.querySelector('.container'), options);
		chart.render();
	}

	function get_class_color(class_name: string){
		// Create an element with the bg-primary-500 class
        const el = document.createElement('div');
        el.className = class_name;

		document.body.appendChild(el);
        // Get the computed background color
        const color = getComputedStyle(el).backgroundColor;
        // Remove the element from the body
        document.body.removeChild(el);

		return color
	}

	function rgb_str_to_hex(color: string){
		var rgb_vec = (color.split("(")[1].split(")")[0]).split(",");
		var hex_str = "#";
		hex_str += parseInt(rgb_vec[0]).toString(16);
		hex_str += parseInt(rgb_vec[1]).toString(16);
		hex_str += parseInt(rgb_vec[2]).toString(16);
		return hex_str;
	}

	function change_options_for_mode(mode: string, options:any):any {
		if (mode.localeCompare("light") == 0){
			options.title.style.color = rgb_str_to_hex(get_class_color('bg-tertiary-800'));
			options.chart.background = rgb_str_to_hex(get_class_color('bg-surface-50'));
			options.xaxis.labels.style.colors = rgb_str_to_hex(get_class_color('bg-tertiary-800'));
			options.xaxis.axisBorder.color = rgb_str_to_hex(get_class_color('bg-tertiary-800'));
			options.xaxis.axisTicks.color = rgb_str_to_hex(get_class_color('bg-tertiary-800'));
			options.xaxis.title.style.color = rgb_str_to_hex(get_class_color('bg-tertiary-800'));
			options.grid.borderColor = rgb_str_to_hex(get_class_color('bg-tertiary-700'));
			options.yaxis = {
				show: true,
				logBase: 10,
				labels: {
					show: true,
					align: 'right',
					style: {
						colors: rgb_str_to_hex(get_class_color('bg-tertiary-800')),
					},
				},
				axisBorder: {
					show: true,
					color: rgb_str_to_hex(get_class_color('bg-tertiary-800')),
				},
				axisTicks: {
					show: true,
					borderType: 'solid',
					color: rgb_str_to_hex(get_class_color('bg-tertiary-800')),
				},
				title: {
					text: "height",
					rotate: -90,
					style: {
						color: rgb_str_to_hex(get_class_color('bg-tertiary-800')),
					},
				},
			};
			options.tooltip.theme = "light";
		} else if(mode.localeCompare("dark") == 0){
			options.title.style.color = rgb_str_to_hex(get_class_color('bg-tertiary-400'));
			options.chart.background = rgb_str_to_hex(get_class_color('bg-surface-900'));
			options.xaxis.labels.style.colors = rgb_str_to_hex(get_class_color('bg-tertiary-400'));
			options.xaxis.axisBorder.color = rgb_str_to_hex(get_class_color('bg-tertiary-400'));
			options.xaxis.axisTicks.color = rgb_str_to_hex(get_class_color('bg-tertiary-400'));
			options.xaxis.title.style.color = rgb_str_to_hex(get_class_color('bg-tertiary-400'));
			options.grid.borderColor = rgb_str_to_hex(get_class_color('bg-tertiary-500'));
			options.yaxis = {
				show: true,
				logBase: 10,
				labels: {
					show: true,
					align: 'right',
					style: {
						colors: rgb_str_to_hex(get_class_color('bg-tertiary-400')),
					},
				},
				axisBorder: {
					show: true,
					color: rgb_str_to_hex(get_class_color('bg-tertiary-400')),
				},
				axisTicks: {
					show: true,
					borderType: 'solid',
					color: rgb_str_to_hex(get_class_color('bg-tertiary-400')),
				},
				title: {
					text: "height",
					rotate: -90,
					style: {
						color: rgb_str_to_hex(get_class_color('bg-tertiary-400')),
					},
				},
			}
			options.tooltip.theme = "dark";
		}
		return options;
	}

	let mounted = false;

	$: {
		if (mounted){
			if ($modeCurrent){
				options = change_options_for_mode("light", options);
			} else{
				options = change_options_for_mode("dark", options);
			}
			if (chart != null){
				(async () => {chart.updateOptions(options);})();
			}
		}
    }

	onMount(() => {
		options.series[0].color = rgb_str_to_hex(get_class_color('bg-primary-500'));
		make_line_chart(options);

		mounted = true;
	});




	let intervalId: any;
	let last_val = 50;
	let record = null;
    onMount(() => {
        intervalId = setInterval(async () => {
			last_val =+ Math.floor(Math.random() * 60) - 30
            // await PB.collection('Test').create({
            //     height: last_val,
            // });
			data.push(last_val);
			chart.updateSeries([{
				data: data
			}])

        }, 500); // 5000 milliseconds = 5 seconds
    });







</script>

<svelte:head></svelte:head>

<main>
	<!-- <div class="tool-tip variant-ghost-primary">23</div> -->
	<div class="container"/>
</main>


<style>
	.container {
		width: 500px;
		height: 500px;
	}

</style>