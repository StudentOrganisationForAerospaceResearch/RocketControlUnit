<script lang="ts">
	import { getModalStore, SlideToggle, modeCurrent } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';
	import { onMount } from 'svelte';
	import { writable } from 'svelte/store';
	import PocketBase from 'pocketbase';
	import BackgroundDark from './background-dark.svelte';
	import BackgroundLight from './background-light.svelte';

	const modalStore = getModalStore();

	const PB = new PocketBase('http://127.0.0.1:8090');

	let nextStatePending: string = '';
	function confirmStateChange(state: string): void {
		nextStatePending = state;
		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: `Are you sure you wish to proceed to ${state}?`,
			response: (r: boolean) => {
				if (r) {
					async function writeStateChange(state: string) {
						await PB.collection('CommandMessage').create({
							target: 'NODE_DMB',
							command: stateCommands[state]
						});
					}
					writeStateChange(nextStatePending);
					// nextState(nextStatePending); // Uncomment this line to test state transition
				}
				nextStatePending = '';
			}
		};
		modalStore.trigger(modal);
	}
	const states = {
		RS_PRELAUNCH: 'Pre-Launch',
		RS_FILL: 'Fill',
		RS_ARM: 'Arm',
		RS_IGNITION: 'Ignition',
		RS_LAUNCH: 'Launch',
		RS_BURN: 'Burn',
		RS_COAST: 'Coast',
		RS_DESCENT: 'Descent',
		RS_RECOVERY: 'Recovery',
		RS_ABORT: 'Abort',
		RS_TEST: 'Test'
	};

	// Define a type for the keys of the `states` object
	type StateKey =
		| 'RS_PRELAUNCH'
		| 'RS_FILL'
		| 'RS_ARM'
		| 'RS_IGNITION'
		| 'RS_LAUNCH'
		| 'RS_BURN'
		| 'RS_COAST'
		| 'RS_DESCENT'
		| 'RS_RECOVERY'
		| 'RS_ABORT'
		| 'RS_TEST';

	// Use the `StateKey` type to index the `states` object
	function getStateName(key: StateKey) {
		return states[key];
	}

	// Create a reverse mapping of states
	const stateCommands: Record<string, string> = Object.entries(states).reduce(
		(acc: Record<string, string>, [key, value]) => {
			acc[value] = key;
			return acc;
		},
		{}
	);

	function nextState(state: string) {
		currentState.set(state);
	}

    let BackgroundComponent: any;

    $: {
        if ($modeCurrent) {
            BackgroundComponent = BackgroundLight;
        } else {
            BackgroundComponent = BackgroundDark;
        }
    }

	let containerElement: any;

	onMount(() => {
		containerElement = document.querySelector('.container') as HTMLElement;

		// Define the resize handler
		const handleResize = () => {
			if (containerElement) {
				let containerWidth = containerElement.offsetWidth;
				document.documentElement.style.setProperty('--container-width', `${containerWidth}px`);
				document.documentElement.style.setProperty(
					'--container-width-unitless',
					`${containerWidth}`
				);
			} else {
				console.error('No element with class "container" found');
			}
		};

		// Call the resize handler once on mount
		handleResize();

		// Attach the resize handler to the resize event
		window.addEventListener('resize', handleResize);

		// Return a cleanup function to remove the event listener when the component is destroyed
		return () => {
			window.removeEventListener('resize', handleResize);
		};
	});

	const ac1_open = writable(undefined);
	const ac2_open = writable(undefined);

	const pbv1_open = writable(undefined);
	const pbv2_open = writable(undefined);
	const pbv3_open = writable(undefined);
	const pbv4_open = writable(undefined);

	const sol5_open = writable(undefined);
	const sol6_open = writable(undefined);
	const sol7_open = writable(undefined);
	const sol8a_open = writable(undefined);
	const sol8b_open = writable(undefined);

	const continuity1 = writable(undefined);
	const continuity2 = writable(undefined);
	const box1_on = writable(undefined);
	const box2_on = writable(undefined);

	const vent_open = writable(undefined);
	const drain_open = writable(undefined);
	const mev_open = writable(undefined);

	const rcu_tc1_temperature = writable(undefined);
	const rcu_tc2_temperature = writable(undefined);

	const battery_voltage = writable(undefined);
	const power_source = writable(undefined);

	const upper_pv_pressure = writable(undefined);

	const rocket_mass = writable(undefined);

	const nos1_mass = writable(undefined);
	const nos2_mass = writable(undefined);

	const ib_pressure = writable(undefined);
	const lower_pv_pressure = writable(undefined);

	const pv_temperature = writable(undefined);

	const pt1_pressure = writable(undefined);
	const pt2_pressure = writable(undefined);
	const pt3_pressure = writable(undefined);
	const pt4_pressure = writable(undefined);

	const sob_tc1_temperature = writable(undefined);
	const sob_tc2_temperature = writable(undefined);

	$: ac1_display = $ac1_open === undefined ? 'N/A' : $ac1_open ? 'ON' : 'OFF';
	$: ac2_display = $ac2_open === undefined ? 'N/A' : $ac2_open ? 'ON' : 'OFF';

	$: pbv1_display = $pbv1_open === undefined ? 'N/A' : $pbv1_open ? 'OPEN' : 'CLOSE';
	$: pbv2_display = $pbv2_open === undefined ? 'N/A' : $pbv2_open ? 'OPEN' : 'CLOSE';
	$: pbv3_display = $pbv3_open === undefined ? 'N/A' : $pbv3_open ? 'OPEN' : 'CLOSE';
	$: pbv4_display = $pbv4_open === undefined ? 'N/A' : $pbv4_open ? 'CLOSE' : 'OPEN';

	$: sol5_display = $sol5_open === undefined ? 'N/A' : $sol5_open ? 'OPEN' : 'CLOSE';
	$: sol6_display = $sol6_open === undefined ? 'N/A' : $sol6_open ? 'OPEN' : 'CLOSE';
	$: sol7_display = $sol7_open === undefined ? 'N/A' : $sol7_open ? 'OPEN' : 'CLOSE';
	$: sol8a_display = $sol8a_open === undefined ? 'N/A' : $sol8a_open ? 'OPEN' : 'CLOSE';
	$: sol8b_display = $sol8b_open === undefined ? 'N/A' : $sol8b_open ? 'OPEN' : 'CLOSE';

	$: continuity1_display = $continuity1 === undefined ? 'N/A' : $continuity1;
	$: continuity2_display = $continuity2 === undefined ? 'N/A' : $continuity2;

	$: box1_display = $box1_on === undefined ? 'N/A' : $box1_on ? 'LIVE' : 'DEAD';
	$: box2_display = $box2_on === undefined ? 'N/A' : $box2_on ? 'LIVE' : 'DEAD';

	$: vent_display = $vent_open === undefined ? 'N/A' : $vent_open ? 'OPEN' : 'CLOSED';
	$: drain_display = $drain_open === undefined ? 'N/A' : $drain_open ? 'OPEN' : 'CLOSED';

	$: rcu_tc1_display = $rcu_tc1_temperature === undefined ? 'N/A' : $rcu_tc1_temperature;
	$: rcu_tc2_display = $rcu_tc2_temperature === undefined ? 'N/A' : $rcu_tc2_temperature;

	$: mev_display = $mev_open === undefined ? 'N/A' : $mev_open ? 'OPEN' : 'CLOSED';

	$: battery_display = $battery_voltage === undefined ? 'N/A' : $battery_voltage;
	$: power_display = $power_source === undefined ? 'N/A' : $power_source ? 'ONBOARD' : 'GROUND';

	$: upper_pv_display = $upper_pv_pressure === undefined ? 'N/A' : $upper_pv_pressure;

	$: rocket_mass_display = $rocket_mass === undefined ? 'N/A' : $rocket_mass;

	$: nos1_mass_display = $nos1_mass === undefined ? 'N/A' : $nos1_mass;
	$: nos2_mass_display = $nos2_mass === undefined ? 'N/A' : $nos2_mass;

	$: ib_pressure_display = $ib_pressure === undefined ? 'N/A' : $ib_pressure;
	$: lower_pv_display = $lower_pv_pressure === undefined ? 'N/A' : $lower_pv_pressure;

	$: pv_temperature_display = $pv_temperature === undefined ? 'N/A' : $pv_temperature;

	$: pt1_pressure_display = $pt1_pressure === undefined ? 'N/A' : $pt1_pressure;
	$: pt2_pressure_display = $pt2_pressure === undefined ? 'N/A' : $pt2_pressure;
	$: pt3_pressure_display = $pt3_pressure === undefined ? 'N/A' : $pt3_pressure;
	$: pt4_pressure_display = $pt4_pressure === undefined ? 'N/A' : $pt4_pressure;

	$: sob_tc1_display = $sob_tc1_temperature === undefined ? 'N/A' : $sob_tc1_temperature;
	$: sob_tc2_display = $sob_tc2_temperature === undefined ? 'N/A' : $sob_tc2_temperature;

	onMount(async () => {
		// Subscribe to changes in the 'RelayStatus' collection
		PB.collection('RelayStatus').subscribe('*', function (e) {
			ac1_open.set(e.record.ac1_open);
			ac2_open.set(e.record.ac2_open);

			pbv1_open.set(e.record.pbv1_open);
			pbv2_open.set(e.record.pbv2_open);
			pbv3_open.set(e.record.pbv3_open);
			pbv4_open.set(e.record.pbv4_open);

			sol5_open.set(e.record.sol5_open);
			sol6_open.set(e.record.sol6_open);
			sol7_open.set(e.record.sol7_open);
			sol8a_open.set(e.record.sol8a_open);
			sol8b_open.set(e.record.sol8b_open);
		});

		// Subscribe to changes in the 'CombustionControlStatus' collection
		PB.collection('CombustionControlStatus').subscribe('*', function (e) {
			// Update the CombustionControlStatus data store whenever a change is detected
			vent_open.set(e.record.vent_open);
			drain_open.set(e.record.drain_open);
			mev_open.set(e.record.mev_open);
		});

		// Subscribe to changes in the 'RcuTemp' collection
		PB.collection('RcuTemperature').subscribe('*', function (e) {
			// Update the RcuTemp data store whenever a change is detected
			rcu_tc1_temperature.set(e.record.tc1_temperature);
			rcu_tc2_temperature.set(e.record.tc2_temperature);
		});

		// Subscribe to changes in the 'PadBoxStatus' collection
		PB.collection('PadBoxStatus').subscribe('*', function (e) {
			// Update the PadBoxStatus data store whenever a change is detected
			continuity1.set(e.record.continuity_1);
			continuity2.set(e.record.continuity_2);
			box1_on.set(e.record.box1_on);
			box2_on.set(e.record.box2_on);
		});

		// Subscribe to changes in the 'Battery' collection
		PB.collection('Battery').subscribe('*', function (e) {
			// Update the Battery data store whenever a change is detected
			battery_voltage.set(e.record.voltage);
			power_source.set(e.record.power_source);
		});

		// Subscribe to changes in the 'DmbPressure' collection
		PB.collection('DmbPressure').subscribe('*', function (e) {
			// Update the DmbPressure data store whenever a change is detected
			upper_pv_pressure.set(e.record.upper_pv_pressure);
		});

		// Subscribe to changes in the 'LaunchRailLoadCell' collection
		PB.collection('LaunchRailLoadCell').subscribe('*', function (e) {
			// Update the LaunchRailLoadCell data store whenever a change is detected
			rocket_mass.set(e.record.rocket_mass);
		});

		// Subscribe to changes in the 'NosLoadCell' collection
		PB.collection('NosLoadCell').subscribe('*', function (e) {
			// Update the NosLoadCell data store whenever a change is detected
			nos1_mass.set(e.record.nos1_mass);
			nos2_mass.set(e.record.nos2_mass);
		});

		// Subscribe to changes in the 'PbbPressure' collection
		PB.collection('PbbPressure').subscribe('*', function (e) {
			// Update the PbbPressure data store whenever a change is detected
			ib_pressure.set(e.record.ib_pressure);
			lower_pv_pressure.set(e.record.lower_pv_pressure);
		});

		// Subscribe to changes in the 'PbbTemperature' collection
		PB.collection('PbbTemperature').subscribe('*', function (e) {
			// Update the PbbTemperature data store whenever a change is detected
			pv_temperature.set(e.record.pv_temperature);
		});

		// Subscribe to changes in the 'RcuPressure' collection
		PB.collection('RcuPressure').subscribe('*', function (e) {
			// Update the RcuPressure data store whenever a change is detected
			pt1_pressure.set(e.record.pt1_pressure);
			pt2_pressure.set(e.record.pt2_pressure);
			pt3_pressure.set(e.record.pt3_pressure);
			pt4_pressure.set(e.record.pt4_pressure);
		});

		// Subscribe to changes in the 'SobTemperature' collection
		PB.collection('SobTemperature').subscribe('*', function (e) {
			// Update the SobTemperature data store whenever a change is detected
			sob_tc1_temperature.set(e.record.tc1_temperature);
			sob_tc2_temperature.set(e.record.tc2_temperature);
		});

		// Subscribe to changes in the 'SystemState' collection
		PB.collection('SystemState').subscribe('*', function (e) {
			// Update the SystemState data store whenever a change is detected

			const state = e.record.rocket_state;
			nextState(getStateName(state));
		});
	});

	async function handleSliderChange(
		e: any,
		target: string,
		openCommand: string,
		closeCommand: string
	) {
		e.preventDefault();

		// Determine the command based on the current value of the slider
		const command = e.target.checked ? openCommand : closeCommand;

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create({
			// Write a new record with all current values
			target: target,
			command: command
		});
	}

	async function writeLoadCellCommandMessage(target: string, command: string, weight_kg: number) {
		await PB.collection('LoadCellCommands').create({
			target: target,
			command: command,
			weight: weight_kg
		});
	}

	function confirmRemoveWeight(loadcell: string) {
		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Remove All Weight',
			response: (r: boolean) => {
				if (r) {
					writeLoadCellCommandMessage(loadcell, "CALIBRATE", 0);
					promptEnterNumberOfWeights(loadcell);
				} else {
					writeLoadCellCommandMessage(loadcell, "CANCEL", 0);
				}
			}
		};
		modalStore.trigger(modal);
	}

	let numberOfWeights = 0;

	function promptEnterNumberOfWeights(loadcell: string) {
		const modal: ModalSettings = {
			type: 'prompt',
			title: 'Enter number of weights',
			valueAttr: { type: 'number', required: true },
			response: async (r: any) => {
				if (r) {
					// The modal was confirmed, set the number of weights
					numberOfWeights = parseInt(r);
					if (numberOfWeights > 0) {
						promptEnterWeight(loadcell);
					}
				}
			}
		};
		modalStore.trigger(modal);
	}

	function promptEnterWeight(loadcell: string) {
		const modal: ModalSettings = {
			type: 'prompt',
			title: `Enter Weight (kg) (${numberOfWeights} remaining)`,
			valueAttr: { type: 'text', required: true },
			response: async (r: any) => {
				if (r) {
					// If this is the last weight, send the finish command
					if (numberOfWeights === 1) {
						writeLoadCellCommandMessage(loadcell, "FINISH", parseFloat(r));
					} else {
						// The modal was confirmed, send the calibrate command
						writeLoadCellCommandMessage(loadcell, "CALIBRATE", parseFloat(r));
					}

					// Decrease the number of weights and open the modal again if there are more weights to enter
					numberOfWeights--;
					if (numberOfWeights > 0) {
						promptEnterWeight(loadcell);
					}
				} else {
					// The modal was cancelled, send a cancel command
					writeLoadCellCommandMessage(loadcell, "CANCEL", 0);
				}
			}
		};
		modalStore.trigger(modal);
	}

	async function performTare(loadcell: string) {
		writeLoadCellCommandMessage(loadcell, "TARE", 0);
	}

	// NOTE: This seems odd but since the event will switch these MUST be swapped
	// Open to alternate ways of doing it. Everything I tried didn't work.
	async function handleIgnition(e: MouseEvent) {
		await handleSliderChange(e, 'NODE_RCU', 'RCU_IGNITE_PAD_BOX1', 'RCU_KILL_BOX1');
		await handleSliderChange(e, 'NODE_RCU', 'RCU_KILL_PAD_BOX2', 'RCU_IGNITE_PAD_BOX2');
	}

</script>

<div class="container">
	<svelte:component this={BackgroundComponent} />

	<div class="ac1_slider">
		<SlideToggle
			name="ac1_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$ac1_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_AC1', 'RCU_CLOSE_AC1')}
		>
			{ac1_display}</SlideToggle
		>
	</div>

	<div class="ac2_slider">
		<SlideToggle
			name="ac2_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$ac2_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_AC2', 'RCU_CLOSE_AC2')}
		>
			{ac2_display}</SlideToggle
		>
	</div>

	<div class="pbv1_slider">
		<SlideToggle
			name="pbv1_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv1_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV1', 'RCU_CLOSE_PBV1')}
		>
			{pbv1_display}</SlideToggle
		>
	</div>

	<div class="pbv2_slider">
		<SlideToggle
			name="pbv2_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv2_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV2', 'RCU_CLOSE_PBV2')}
		>
			{pbv2_display}</SlideToggle
		>
	</div>

	<div class="pbv3_slider">
		<SlideToggle
			name="pbv3_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv3_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV3', 'RCU_CLOSE_PBV3')}
		>
			{pbv3_display}</SlideToggle
		>
	</div>

	<div class="pbv4_slider">
		<SlideToggle
			name="pbv4_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv4_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV4', 'RCU_CLOSE_PBV4')}
		>
			{pbv4_display}</SlideToggle
		>
	</div>
	
	<div class="sol5_slider">
		<SlideToggle
			name="sol5_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol5_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL5', 'RCU_CLOSE_SOL5')}
		>
			{sol5_display}</SlideToggle
		>
	</div>

	<div class="sol6_slider">
		<SlideToggle
			name="sol6_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol6_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL6', 'RCU_CLOSE_SOL6')}
		>
			{sol6_display}</SlideToggle
		>
	</div>

	<div class="sol7_slider">
		<SlideToggle
			name="sol7_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol7_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL7', 'RCU_CLOSE_SOL7')}
		>
			{sol7_display}</SlideToggle
		>
	</div>

	<div class="sol8a_slider">
		<SlideToggle
			name="sol8a_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol8a_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL8A', 'RCU_CLOSE_SOL8A')}
		>
			{sol8a_display}</SlideToggle
		>
	</div>

	<div class="sol8b_slider">
		<SlideToggle
			name="sol8b_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol8b_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL8B', 'RCU_CLOSE_SOL8B')}
		>
			{sol8b_display}</SlideToggle
		>
	</div>

	<div class="vent_slider">
		<SlideToggle
			name="vent_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$vent_open}
			on:click={(e) => handleSliderChange(e, 'NODE_DMB', 'RSC_OPEN_VENT', 'RSC_CLOSE_VENT')}
		>
			{vent_display}</SlideToggle
		>
	</div>

	<div class="drain_slider">
		<SlideToggle
			name="drain_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$drain_open}
			on:click={(e) => handleSliderChange(e, 'NODE_DMB', 'RSC_OPEN_DRAIN', 'RSC_CLOSE_DRAIN')}
		>
			{drain_display}</SlideToggle
		>
	</div>

	<div class="power_source_slider">
		<SlideToggle
			name="power_source_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$power_source}
			on:click={(e) =>
				handleSliderChange(
					e,
					'NODE_DMB',
					'RSC_POWER_TRANSITION_ONBOARD',
					'RSC_POWER_TRANSITION_EXTERNAL'
				)}
		>
			{power_display}</SlideToggle
		>
	</div>

	{#if $currentState === states.RS_IGNITION}
		<div class="box1_slider">
			<SlideToggle
				name="box1_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$box1_on}
				on:click={handleIgnition}
			>
				{box1_display}</SlideToggle
			>
		</div>

		<div class="box2_slider">
			<SlideToggle
				name="box2_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$box2_on}
				on:click={handleIgnition}
			>
				{box2_display}</SlideToggle
			>
		</div>
	{/if}

	<div class="nos1_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("NOS1")}
		>
			TARE
		</button>
	</div>

	<div class="nos1_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => {
				writeLoadCellCommandMessage("NOS1", "CANCEL", 0);
				confirmRemoveWeight("NOS1");}}
		>
			CAL
		</button>
	</div>

	<div class="nos2_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("NOS2")}
		>
			TARE
		</button>
	</div>

	<div class="nos2_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => {
				writeLoadCellCommandMessage("NOS2", "CANCEL", 0);	
				confirmRemoveWeight("NOS2");}}
		>
			CAL
		</button>
	</div>

	<div class="rail_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("LaunchRail")}
		>
			TARE
		</button>
	</div>

	<div class="rail_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => { 
				writeLoadCellCommandMessage("LaunchRail", "CANCEL", 0);
				confirmRemoveWeight("LaunchRail");}}
		>
			CAL
		</button>
	</div>

	<div class="rcu_tc1">
		<p>{rcu_tc1_display}</p>
	</div>

	<div class="rcu_tc2">
		<p>{rcu_tc2_display}</p>
	</div>

	<div class="nos1">
		<p>{nos1_mass_display}</p>
	</div>

	<div class="nos2">
		<p>{nos2_mass_display}</p>
	</div>

	<div class="pt1_pressure">
		<p>{pt1_pressure_display}</p>
	</div>

	<div class="pt2_pressure">
		<p>{pt2_pressure_display}</p>
	</div>

	<div class="pt3_pressure">
		<p>{pt3_pressure_display}</p>
	</div>

	<div class="pt4_pressure">
		<p>{pt4_pressure_display}</p>
	</div>

	<div class="box1_continuity">
		<p>{continuity1_display}</p>
	</div>

	<div class="box2_continuity">
		<p>{continuity2_display}</p>
	</div>

	<div class="mev_status">
		<p>{mev_display}</p>
	</div>

	<div class="battery_voltage">
		<p>{battery_display}</p>
	</div>

	<div class="upper_pv_pressure">
		<p>{upper_pv_display}</p>
	</div>

	<div class="rocket_mass">
		<p>{rocket_mass_display}</p>
	</div>

	<div class="ib_pressure">
		<p>{ib_pressure_display}</p>
	</div>

	<div class="lower_pv_pressure">
		<p>{lower_pv_display}</p>
	</div>

	<div class="pv_temperature">
		<p>{pv_temperature_display}</p>
	</div>

	<div class="sob_tc1">
		<p>{sob_tc1_display}</p>
	</div>

	<div class="sob_tc2">
		<p>{sob_tc2_display}</p>
	</div>

	<!-- Render different buttons based on the current state -->
	{#if $currentState === states.RS_PRELAUNCH}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.51);"
			on:click={() => confirmStateChange(states.RS_FILL)}>Go to Fill</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.55);"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_FILL}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.51);"
			on:click={() => confirmStateChange(states.RS_PRELAUNCH)}>Go to Pre-Launch</button
		>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => confirmStateChange(states.RS_ARM)}>Go to Arm</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.55);"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_ARM}
		<button
			class="btn variant-filled-warning next-state-btn"
			style="top: calc(var(--container-width) * 0.51);"
			on:click={() => confirmStateChange(states.RS_IGNITION)}>Go to Ignition</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.55);"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_IGNITION}
		<button
			class="btn variant-filled-error next-state-btn"
			style="top: calc(var(--container-width) * 0.51);"
			on:click={() => nextState(states.RS_LAUNCH)}>LAUNCH</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.55);"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_ABORT}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.55);"
			on:click={() => confirmStateChange(states.RS_PRELAUNCH)}>Go to Pre-Launch</button
		>
	{:else if $currentState === states.RS_LAUNCH}
		<h1>nice rocket bro</h1>
	{/if}
</div>

<style>
	.container {
		position: relative;
		width: 100%;
		height: 100%;
	}

	@media (min-width: 576px) {
		.container {
			max-width: 100%;
		}
	}

	.next-state-btn {
		position: absolute;
		left: 8%;
		width: 200px;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1400));
	}

	.ac1_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.025);
		left: 8.6%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.ac2_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.10);
		left: 80%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.pbv1_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.118);
		left: 35.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.pbv2_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.188);
		left: 35.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.pbv3_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.275);
		left: 35.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.pbv4_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.144);
		left: 47.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.sol5_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.269);
		left: 63.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.sol6_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.313);
		left: 63.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.sol7_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.356);
		left: 63.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.sol8a_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.396);
		left: 63.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.sol8b_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.44);
		left: 63.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.vent_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.152);
		left: 85.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.drain_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.265);
		left: 85.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.power_source_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.025);
		left: 95.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.box1_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.415);
		left: 12.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.box2_slider {
		position: absolute;
		top: calc(var(--container-width) * 0.433);
		left: 12.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
		font-size: 16px;
	}

	.nos1_tare_button {
		position: absolute;
		top: calc(var(--container-width) * 0.176);
		left: 11.1%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}

	.nos1_cal_button {
		position: absolute;
		top: calc(var(--container-width) * 0.195);
		left: 11.0%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}

	.nos2_tare_button {
		color: #04AA6D;
		position: absolute;
		top: calc(var(--container-width) * 0.246);
		left: 11.1%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}

	.nos2_cal_button {
		color: #04AA6D;
		position: absolute;
		top: calc(var(--container-width) * 0.265);
		left: 11.0%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}
	
	.rail_tare_button {
		position: absolute;
		top: calc(var(--container-width) * 0.078);
		left: 69.1%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}

	.rail_cal_button {
		position: absolute;
		top: calc(var(--container-width) * 0.097);
		left: 69.1%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1900));
	}

	.rcu_tc1 {
		position: absolute;
		top: calc(var(--container-width) * 0.065);
		left: 5.6%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.rcu_tc2 {
		position: absolute;
		top: calc(var(--container-width) * 0.065);
		left: 9.2%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.nos1 {
		position: absolute;
		top: calc(var(--container-width) * 0.187);
		left: 7.6%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.nos2 {
		position: absolute;
		top: calc(var(--container-width) * 0.255);
		left: 7.6%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.pt1_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.117);
		left: 14.7%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.pt2_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.1882);
		left: 14.7%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.pt3_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.2743);
		left: 14.9%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.pt4_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.188);
		left: 42%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.box1_continuity {
		position: absolute;
		top: calc(var(--container-width) * 0.372);
		left: 14.7%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.box2_continuity {
		position: absolute;
		top: calc(var(--container-width) * 0.386);
		left: 14.7%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.mev_status {
		position: absolute;
		top: calc(var(--container-width) * 0.069);
		left: 93.9%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.battery_voltage {
		position: absolute;
		top: calc(var(--container-width) * 0.049);
		left: 93.9%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.upper_pv_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.104);
		left: 92.9%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.rocket_mass {
		position: absolute;
		top: calc(var(--container-width) * 0.09);
		left: 74.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.ib_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.391);
		left: 93.1%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.lower_pv_pressure {
		position: absolute;
		top: calc(var(--container-width) * 0.345);
		left: 90.3%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.pv_temperature {
		position: absolute;
		top: calc(var(--container-width) * 0.345);
		left: 95.5%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.sob_tc1 {
		position: absolute;
		top: calc(var(--container-width) * 0.1405);
		left: 69%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}

	.sob_tc2 {
		position: absolute;
		top: calc(var(--container-width) * 0.179);
		left: 69%;
		transform: translate(-50%, -50%) scale(calc(var(--container-width-unitless) / 1500));
		font-size: 14px;
	}
</style>