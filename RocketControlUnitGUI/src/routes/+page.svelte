<script lang="ts">
	import { getModalStore, SlideToggle } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';
	import { onMount } from 'svelte';
    import { writable } from 'svelte/store';
    import type { RecordModel } from 'pocketbase';
	import back from '$lib/assets/test.svg';
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

	export const relayStatus = writable<RecordModel | null>(null);

	// Create a writable store to hold the CombustionControlStatus data
	export const combustionControlStatus = writable<RecordModel | null>(null);

	// Create a writable store to hold the RcuTemp data
	export const rcuTemp = writable<RecordModel | null>(null);

	// Create a writable store to hold the PadBoxStatus data
	export const padBoxStatus = writable<RecordModel | null>(null);

	let ac1_open: boolean = false;
	let ac2_open: boolean = false;
	let pbv1_open: boolean = false;
	let pbv2_open: boolean = false;
	let pbv3_open: boolean = false;

	let power_enable_checked: boolean = false;
	let sol1_open: boolean = false;
	let sol2_open: boolean = false;
	let sol3_open: boolean = false;
	let sol4_open: boolean = false;
	let sol5_open: boolean = false;
	let sol6_open: boolean = false;
	let sol7_open: boolean = false;
	let sol8a_open: boolean = false;
	let sol8b_open: boolean = false;
	let padbox_cont1_checked: boolean = false;
	let padbox_cont2_checked: boolean = false;
	let padbox_box1_checked: boolean = false;
	let padbox_box2_checked: boolean = false;

	onMount(async () => {
		// Subscribe to changes in the 'RelayStatus' collection
		PB.collection('RelayStatus').subscribe('*', function (e) {
			// Update the RelayStatus data store whenever a change is detected
			relayStatus.set(e.record);
		});

		// Subscribe to changes in the 'CombustionControlStatus' collection
		PB.collection('CombustionControlStatus').subscribe('*', function (e) {
			// Update the CombustionControlStatus data store whenever a change is detected
			combustionControlStatus.set(e.record);
		});

		// Subscribe to changes in the 'RcuTemp' collection
		PB.collection('RcuTemp').subscribe('*', function (e) {
			// Update the RcuTemp data store whenever a change is detected
			rcuTemp.set(e.record);
		});

		// Subscribe to changes in the 'PadBoxStatus' collection
		PB.collection('PadBoxStatus').subscribe('*', function (e) {
			// Update the PadBoxStatus data store whenever a change is detected
			padBoxStatus.set(e.record);
		});
		
		const resultList = await PB.collection('RelayStatus').getList(1, 1, {
			sort: '-created',
		});
		
    	ac1_open = resultList.items[0].ac1_open;
		ac2_open = resultList.items[0].ac2_open
		pbv1_open = resultList.items[0].pbv1_open
		pbv2_open = resultList.items[0].pbv2_open
		pbv3_open = resultList.items[0].pbv3_open
		sol1_open = resultList.items[0].sol1_open
		sol2_open = resultList.items[0].sol2_open
		sol3_open = resultList.items[0].sol3_open
		sol4_open = resultList.items[0].sol4_open
		sol5_open = resultList.items[0].sol5_open
		sol6_open = resultList.items[0].sol6_open
		sol7_open = resultList.items[0].sol7_open
		sol8a_open = resultList.items[0].sol8a_open
		sol8b_open = resultList.items[0].sol8b_open
	})

	// $: ac1_open = $relayStatus?.ac1_open || false;	
	// $: ac2_open = $relayStatus?.ac2_open || false;
	// $: pbv1_open = $relayStatus?.pbv1_open || false;
	// $: pbv2_open = $relayStatus?.pbv2_open || false;
	// $: pbv3_open = $relayStatus?.pbv3_open || false;
	// $: sol1_open = $relayStatus?.sol1_open || false;
	// $: sol2_open = $relayStatus?.sol2_open || false;
	// $: sol3_open = $relayStatus?.sol3_open || false;
	// $: sol4_open = $relayStatus?.sol4_open || false;
	// $: sol5_open = $relayStatus?.sol5_open || false;
	// $: sol6_open = $relayStatus?.sol6_open || false;
	// $: sol7_open = $relayStatus?.sol7_open || false;
	// $: sol8a_open = $relayStatus?.sol8a_open || false;
	// $: sol8b_open = $relayStatus?.sol8b_open || false;

	function writePadBoxChange() {
		// Create a change on the 'PadBoxStatus' collection
		PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'cont1': padbox_cont1_checked,
			'cont2': padbox_cont2_checked,
			'box1_on': padbox_box1_checked,
			'box2_on': padbox_box2_checked
		});
	}

	function writeRelayStatusChange() {
		// Create a change on the 'RelayStatus' collection
		PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': ac1_open,
			'ac2_open': ac2_open,
			'pbv1_open': pbv1_open,
			'pbv2_open': pbv2_open,
			'sol1_open': sol1_open,
			'sol2_open': sol2_open
		});
	}

	function writeCombustionControlStatusChange() {
		// Create a change on the 'CombustionControlStatus' collection
		PB.collection('CombustionControlStatus').create ({
			// Write a new record with all current values
			'mev_power_enable': power_enable_checked
		});
	}

	function handleAC1Change(e: any) {
		const target = e.target;
		writeRelayStatusChange();
    	ac1_open = target.checked;
	}

	function handleAC2Change(e: any) {
		const target = e.target;
    	ac2_open = target.checked;
    	console.log(target.checked);

		writeRelayStatusChange();
	}

	function handlePBV1Change(e: any) {
		const target = e.target;
    	pbv1_open = target.checked;
    	console.log(target.checked);

		writeRelayStatusChange();
	}

	function handlePBV2Change(e: any) {
		const target = e.target;
    	pbv2_open = target.checked;
    	console.log(target.checked);

		writeRelayStatusChange();
	}

	function handlePowerEnableChange(e: any) {
		const target = e.target;
    	power_enable_checked = target.checked;
    	console.log(target.checked);

		writeCombustionControlStatusChange();
	}

	function handleSOL1Change(e: any) {
		const target = e.target;
    	sol1_open = target.checked;
    	console.log(target.checked);

		writeRelayStatusChange();
	}

	function handleSOL2Change(e: any) {
		const target = e.target;
    	sol2_open = target.checked;
    	console.log(target.checked);

		writeRelayStatusChange();
	}

	function handleCont1Change(e: any) {
		const target = e.target;
    	padbox_cont1_checked = target.checked;
    	console.log(target.checked);

		writePadBoxChange();
	}

	function handleCont2Change(e: any) {
		const target = e.target;
    	padbox_cont2_checked = target.checked;
    	console.log(target.checked);

		writePadBoxChange();
	}

	function handleBox1Change(e: any) {
		const target = e.target;
    	padbox_box1_checked = target.checked;
    	console.log(target.checked);

		writePadBoxChange();
	}

	function handleBox2Change(e: any) {
		const target = e.target;
    	padbox_box2_checked = target.checked;
    	console.log(target.checked);

		writePadBoxChange();
	}

</script>

<main> 
	<div id="background" style="background-image: url({back}); background-repeat: no-repeat; background-size: 100%; background-position: center top; position:fixed; top: 0; left: 0; right:0; bottom:0; width: 100%; height: 100%;"></div>

	<SlideToggle name="ac1_slider" bind:checked={ac1_open} on:change={handleAC1Change}> AC1 {$relayStatus && 'ac1_open' in $relayStatus ? $relayStatus.ac1_open : 'N/A'}</SlideToggle>
	<SlideToggle name="ac2_slider" bind:checked={ac2_open} on:change={handleAC2Change}> AC2 {$relayStatus && 'ac2_open' in $relayStatus ? $relayStatus.ac2_open : 'N/A'}</SlideToggle>

	<SlideToggle name="pbv1_slider" bind:checked={pbv1_open} on:change={handlePBV1Change}> PV1 {$relayStatus && 'pbv1_open' in $relayStatus ? $relayStatus.pbv1_open : 'N/A'}</SlideToggle>
	<SlideToggle name="pbv2_slider" bind:checked={pbv2_open} on:change={handlePBV2Change}> PV2 {$relayStatus && 'pbv2_open' in $relayStatus ? $relayStatus.pbv2_open : 'N/A'}</SlideToggle>

	<SlideToggle name="power_enable_slider" on:change={handlePowerEnableChange}> Power Enable {$combustionControlStatus && 'mev_power_enable' in $combustionControlStatus ? $combustionControlStatus.mev_power_enable : 'N/A'}</SlideToggle>

	<SlideToggle name="sol1_slider" bind:checked={sol1_open} on:change={handleSOL1Change}> SOL1 {$relayStatus && 'sol1_open' in $relayStatus ? $relayStatus.sol1_open : 'N/A'}</SlideToggle>
	<SlideToggle name="sol2_slider" bind:checked={sol2_open} on:change={handleSOL2Change}> SOL2 {$relayStatus && 'sol2_open' in $relayStatus ? $relayStatus.sol2_open : 'N/A'}</SlideToggle> -->

	<SlideToggle name="padbox_cont1_slider" on:change={handleCont1Change}> Cont1 {$padBoxStatus && 'cont1' in $padBoxStatus ? $padBoxStatus.cont1 : 'N/A'}</SlideToggle>
	<SlideToggle name="padbox_cont2_slider" on:change={handleCont2Change}> Cont2 {$padBoxStatus && 'cont2' in $padBoxStatus ? $padBoxStatus.cont2 : 'N/A'}</SlideToggle>
	<SlideToggle name="padbox_box1_slider" on:change={handleBox1Change}> Box1 {$padBoxStatus && 'box1_on' in $padBoxStatus ? $padBoxStatus.box1_on : 'N/A'}</SlideToggle>
	<SlideToggle name="padbox_box2_slider" on:change={handleBox2Change}> Box2 {$padBoxStatus && 'box2_on' in $padBoxStatus ? $padBoxStatus.box2_on : 'N/A'}</SlideToggle>

	<h1>TC1 {$rcuTemp && 'tc1_temp' in $rcuTemp ? $rcuTemp.tc1_temp: 'N/A'}</h1>
	<h1>TC2 {$rcuTemp && 'tc2_temp ' in $rcuTemp ? $rcuTemp.tc2_temp : 'N/A'}</h1>
	
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