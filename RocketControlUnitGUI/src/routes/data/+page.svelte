<script lang="ts">
	import { ib_pressure, lower_pv_pressure, start_subscriptions } from '$lib/store';
	import { get_class_color, rgb_str_to_hex } from '$lib/utils';
	import { modeCurrent } from '@skeletonlabs/skeleton';
	import { onMount } from 'svelte';

	let ib_pressure_data_points: any[] = [];
	var ib_pressure_options: any = {
        series: [{
          data: ib_pressure_data_points.slice()
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
              speed: 1
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
	var ib_pressure_chart:any = null;

	let pv_pressure_data_points: (string | number)[] = [];
	var pv_pressure_options: any = {
        series: [{
          data: pv_pressure_data_points.slice()
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
              speed: 330
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
	var pv_pressure_chart:any = null;

	async function make_line_chart(options: any, chart_name: string) {
		if ($modeCurrent){
			options = change_options_for_mode("light", options);
		} else{
			options = change_options_for_mode("dark", options);
		}

		const ApexCharts = (await import('apexcharts')).default
		if (chart_name === "ib_pressure_chart"){
			ib_pressure_chart = new ApexCharts(document.querySelector('.containera'), options);
			ib_pressure_chart.render();
		}
		else if (chart_name === "pv_pressure_chart"){
			pv_pressure_chart = new ApexCharts(document.querySelector('.containerb'), options);
			pv_pressure_chart.render();
		}
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
				ib_pressure_options = change_options_for_mode("light", ib_pressure_options);
				pv_pressure_options = change_options_for_mode("light", pv_pressure_options);
			} else{
				ib_pressure_options = change_options_for_mode("dark", ib_pressure_options);
				pv_pressure_options = change_options_for_mode("dark", pv_pressure_options);
			}
			if (ib_pressure_chart != null){
				(async () => {ib_pressure_chart.updateOptions(ib_pressure_options);})();
			}
			if (pv_pressure_chart != null){
				(async () => {pv_pressure_chart.updateOptions(pv_pressure_options);})();
			}
		}
    }

	onMount(() => {
		start_subscriptions();
		ib_pressure_options.series[0].color = rgb_str_to_hex(get_class_color('bg-primary-500'));
		make_line_chart(ib_pressure_options, "ib_pressure_chart");
		pv_pressure_options.series[0].color = rgb_str_to_hex(get_class_color('bg-primary-500'));
		make_line_chart(pv_pressure_options, "pv_pressure_chart");
		mounted = true;
	});

	$: {
		if(mounted){
			if(typeof $ib_pressure !== "undefined" && ib_pressure_chart != null){
				ib_pressure_data_points.push($ib_pressure);
				ib_pressure_chart.updateSeries([{data: ib_pressure_data_points}])
			}
			if(typeof $lower_pv_pressure !== "undefined" && pv_pressure_chart != null){
				pv_pressure_data_points.push($lower_pv_pressure);
				pv_pressure_chart.updateSeries([{data: pv_pressure_data_points}])
			}
		}
    }

</script>

<svelte:head></svelte:head>

<main>
	<!-- <div class="tool-tip variant-ghost-primary">23</div> -->
	<div class="containera"/>
	<div class="containerb"/>
</main>


<style>
	.containera {
		width: 500px;
		height: 500px;
	}

	.containerb {
		width: 500px;
		height: 500px;
	}

</style>