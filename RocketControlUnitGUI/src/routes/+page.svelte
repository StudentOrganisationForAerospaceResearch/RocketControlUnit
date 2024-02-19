<script lang="ts">
	import { getModalStore, SlideToggle } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';
	import { onMount } from 'svelte';
    import { writable } from 'svelte/store';
	import background from '$lib/assets/background.svg';
	import PocketBase from 'pocketbase';

	const modalStore = getModalStore();
	
	const PB = new PocketBase("http://127.0.0.1:8090");

	let nextStatePending: string = '';
	function confirmStateChange(state: string): void {
		nextStatePending = state;
		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: `Are you sure you wish to proceed to ${state}?`,
			response: (r: boolean) => {
				if (r) {
					nextState(nextStatePending);
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

	function nextState(state: string) {
		currentState.set(state);
	}

	const ac1_open = writable<boolean>(false);
	const ac2_open = writable<boolean>(false);

	const pbv1_open = writable<boolean>(false);
	const pbv2_open = writable<boolean>(false);
	const pbv3_open = writable<boolean>(false);	

	const sol1_open = writable<boolean>(false);		
	const sol2_open = writable<boolean>(false);
	const sol3_open = writable<boolean>(false);
	const sol4_open = writable<boolean>(false);
	const sol5_open = writable<boolean>(false);
	const sol6_open = writable<boolean>(false);
	const sol7_open = writable<boolean>(false);
	const sol8a_open = writable<boolean>(false);
	const sol8b_open = writable<boolean>(false);

	const continuity1 = writable<boolean>(false);
	const continuity2= writable<boolean>(false);
	const box1_on = writable<boolean>(false);
	const box2_on = writable<boolean>(false);

	const vent_open = writable<boolean>(false);
	const drain_open = writable<boolean>(false);
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

	const ib_temperature = writable(undefined);
	const pv_temperature = writable(undefined);

	const pt1_pressure = writable(undefined);
	const pt2_pressure = writable(undefined);
	const pt3_pressure = writable(undefined);
	const pt4_pressure = writable(undefined);

	const sob_tc1_temperature = writable(undefined);
	const sob_tc2_temperature = writable(undefined);

	$: rcu_tc1_display = $rcu_tc1_temperature === undefined ? 'N/A' : $rcu_tc1_temperature;
	$: rcu_tc2_display = $rcu_tc2_temperature === undefined ? 'N/A' : $rcu_tc2_temperature;

	$: mev_display = $mev_open === undefined ? 'N/A' : ($mev_open ? 'OPEN' : 'CLOSED');

	$: battery_display = $battery_voltage === undefined ? 'N/A' : $battery_voltage;
	$: power_display = $power_source === undefined ? 'N/A' : $power_source;

	$: upper_pv_display = $upper_pv_pressure === undefined ? 'N/A' : $upper_pv_pressure;

	$: rocket_mass_display = $rocket_mass === undefined ? 'N/A' : $rocket_mass;

	$: nos1_mass_display = $nos1_mass === undefined ? 'N/A' : $nos1_mass;
	$: nos2_mass_display = $nos2_mass === undefined ? 'N/A' : $nos2_mass;

	$: ib_pressure_display = $ib_pressure === undefined ? 'N/A' : $ib_pressure;
	$: lower_pv_display = $lower_pv_pressure === undefined ? 'N/A' : $lower_pv_pressure;

	$: ib_temperature_display = $ib_temperature === undefined ? 'N/A' : $ib_temperature;
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

			sol1_open.set(e.record.sol1_open);
			sol2_open.set(e.record.sol2_open);
			sol3_open.set(e.record.sol3_open);
			sol4_open.set(e.record.sol4_open);
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
			ib_temperature.set(e.record.ib_temperature);
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
	})

	async function handleAC1Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_AC1' : 'RCU_CLOSE_AC1';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}
	
	async function handleAC2Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_AC2' : 'RCU_CLOSE_AC2';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handlePBV1Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_PBV1' : 'RCU_CLOSE_PBV1';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handlePBV2Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_PBV2' : 'RCU_CLOSE_PBV2';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handlePBV3Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_PBV3' : 'RCU_CLOSE_PBV3';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL1Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL1' : 'RCU_CLOSE_SOL1';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL2Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL2' : 'RCU_CLOSE_SOL2';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL3Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL3' : 'RCU_CLOSE_SOL3';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL4Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL4' : 'RCU_CLOSE_SOL4';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL5Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL5' : 'RCU_CLOSE_SOL5';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL6Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL6' : 'RCU_CLOSE_SOL6';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL7Change(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL7' : 'RCU_CLOSE_SOL7';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL8AChange(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL8A' : 'RCU_CLOSE_SOL8A';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleSOL8BChange(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_SOL8B' : 'RCU_CLOSE_SOL8B';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleBoxChange(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_KILL_PAD_BOX1' : 'RCU_IGNITE_BOX1';

		// Create a change on the 'RelayStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_RCU',
			'command': command,
		});
	}

	async function handleVentChange(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_VENT' : 'RCU_CLOSE_VENT';

		// Create a change on the 'CombustionControlStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_DMB',
			'command': command,
		});
	}

	async function handleDrainChange(e: any) {
		// Determine the command based on the current value of the slider
		const command = e.target.checked ? 'RCU_OPEN_DRAIN' : 'RCU_CLOSE_DRAIN';

		// Create a change on the 'CombustionControlStatus' collection
		await PB.collection('CommandMessage').create ({
			// Write a new record with all current values
			'target': 'NODE_DMB',
			'command': command,
		});
	}

</script>

<main> 
	<div id="background" style="background-image: url({background}); background-repeat: no-repeat; background-size: 100%; background-position: center top; position:fixed; top: 0; left: 0; right:0; bottom:0; width: 100%; height: 100%;"></div>

	<SlideToggle name="ac1_slider" bind:checked={$ac1_open} on:change={handleAC1Change}> AC1 {$ac1_open}</SlideToggle>
	<SlideToggle name="ac2_slider" bind:checked={$ac2_open} on:change={handleAC2Change}> AC2 {$ac2_open}</SlideToggle>

	<SlideToggle name="pbv1_slider" bind:checked={$pbv1_open} on:change={handlePBV1Change}> PV1 {$pbv1_open}</SlideToggle>
	<SlideToggle name="pbv2_slider" bind:checked={$pbv2_open} on:change={handlePBV2Change}> PV2 {$pbv2_open}</SlideToggle>
	<SlideToggle name="pbv3_slider" bind:checked={$pbv3_open} on:change={handlePBV3Change}> PV3 {$pbv3_open}</SlideToggle>

	<SlideToggle name="sol1_slider" bind:checked={$sol1_open} on:change={handleSOL1Change}> SOL1 {$sol1_open}</SlideToggle>
	<SlideToggle name="sol2_slider" bind:checked={$sol2_open} on:change={handleSOL2Change}> SOL2 {$sol2_open}</SlideToggle>
	<SlideToggle name="sol3_slider" bind:checked={$sol3_open} on:change={handleSOL3Change}> SOL3 {$sol3_open}</SlideToggle>
	<SlideToggle name="sol4_slider" bind:checked={$sol4_open} on:change={handleSOL4Change}> SOL4 {$sol4_open}</SlideToggle>
	<SlideToggle name="sol5_slider" bind:checked={$sol5_open} on:change={handleSOL5Change}> SOL5 {$sol5_open}</SlideToggle>
	<SlideToggle name="sol6_slider" bind:checked={$sol6_open} on:change={handleSOL6Change}> SOL6 {$sol6_open}</SlideToggle>
	<SlideToggle name="sol7_slider" bind:checked={$sol7_open} on:change={handleSOL7Change}> SOL7 {$sol7_open}</SlideToggle>
	<SlideToggle name="sol8a_slider" bind:checked={$sol8a_open} on:change={handleSOL8AChange}> SOL8A {$sol8a_open}</SlideToggle>
	<SlideToggle name="sol8b_slider" bind:checked={$sol8b_open} on:change={handleSOL8BChange}> SOL8B {$sol8b_open}</SlideToggle>

	<SlideToggle name="box1_slider" bind:checked={$box1_on} on:change={handleBoxChange}> Ignitor Boxes {$box1_on}</SlideToggle>

	<SlideToggle name="vent_slider" bind:checked={$vent_open} on:change={handleVentChange}> Vent {$vent_open}</SlideToggle>
	<SlideToggle name="drain_slider" bind:checked={$drain_open} on:change={handleDrainChange}> Drain {$drain_open}</SlideToggle>

	<p>RCU TC1 Temperature: {rcu_tc1_display}</p>
	<p>RCU TC2 Temperature: {rcu_tc2_display}</p>

	<p>MEV: {mev_display}</p>

	<p>Battery Voltage: {battery_display}</p>
	<p>Power Source: {power_display}</p>

	<p>Upper PV Pressure: {upper_pv_display}</p>

	<p>Rocket Mass: {rocket_mass_display}</p>

	<p>NOS1 Mass: {nos1_mass_display}</p>
	<p>NOS2 Mass: {nos2_mass_display}</p>

	<p>IB Pressure: {ib_pressure_display}</p>
	<p>Lower PV Pressure: {lower_pv_display}</p>

	<p>IB Temperature: {ib_temperature_display}</p>
	<p>PV Temperature: {pv_temperature_display}</p>

	<p>PT1 Pressure: {pt1_pressure_display}</p>
	<p>PT2 Pressure: {pt2_pressure_display}</p>
	<p>PT3 Pressure: {pt3_pressure_display}</p>
	<p>PT4 Pressure: {pt4_pressure_display}</p>

	<p>SOB TC1 Temperature: {sob_tc1_display}</p>
	<p>SOB TC2 Temperature: {sob_tc2_display}</p>
	
	<!-- Render different buttons based on the current state -->
	{#if $currentState === states.RS_PRELAUNCH}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="bottom: 80px;"
			on:click={() => confirmStateChange(states.RS_FILL)}>Go to Fill</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="bottom: 30px;"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_FILL}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="bottom: 80px;"
			on:click={() => confirmStateChange(states.RS_PRELAUNCH)}>Go to Pre-Launch</button
		>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="bottom: 130px;"
			on:click={() => confirmStateChange(states.RS_ARM)}>Go to Arm</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="bottom: 30px;"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_ARM}
		<button
			class="btn variant-filled-warning next-state-btn"
			style="bottom: 80px;"
			on:click={() => confirmStateChange(states.RS_IGNITION)}>Go to Ignition</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="bottom: 30px;"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_IGNITION}
		<button
			class="btn variant-filled-error next-state-btn"
			style="bottom: 80px;"
			on:click={() => nextState(states.RS_LAUNCH)}>LAUNCH</button
		>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="bottom: 30px;"
			on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button
		>
	{:else if $currentState === states.RS_ABORT}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="bottom: 30px;"
			on:click={() => confirmStateChange(states.RS_PRELAUNCH)}>Go to Pre-Launch</button
		>
	{:else if $currentState === states.RS_LAUNCH}
		<h1>nice rocket bro</h1>
	{/if}
</main>

<style>
	#background {
		z-index: -1;
	}
	.next-state-btn {
		position: fixed;
		left: 100px;
		width: 200px;
	}
</style>