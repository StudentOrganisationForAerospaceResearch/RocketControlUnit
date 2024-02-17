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
	
	export const ac1_checked = writable<boolean>(false);


	let ac1_open: boolean = false;
	let ac2_open: boolean = false;
	let pbv1_open: boolean = false;
	let pbv2_open: boolean = false;
	let pbv3_open: boolean = false;

	// let ac1_checked: boolean = false;
	// let ac2_checked: boolean = false;
	// let ac1_checked: boolean;
	let ac2_checked: boolean;
	let pbv1_checked: boolean = false;
	let pbv2_checked: boolean = false;
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


	// async function getRelayRecord() {
		
	// 	const resultListRelay = await PB.collection('RelayStatus').getList(1, 1, {
	// 		sort: '-created',
	// 	});

	// 	ac1_open = resultListRelay.items[0].ac1_open
	// 	ac2_open = resultListRelay.items[0].ac2_open
	// 	pbv1_open = resultListRelay.items[0].pbv1_open
	// 	pbv2_open = resultListRelay.items[0].pbv2_open
	// 	pbv3_open = resultListRelay.items[0].pbv3_open
	// 	sol1_open = resultListRelay.items[0].sol1_open
	// 	sol2_open = resultListRelay.items[0].sol2_open
	// 	sol3_open = resultListRelay.items[0].sol3_open
	// 	sol4_open = resultListRelay.items[0].sol4_open
	// 	sol5_open = resultListRelay.items[0].sol5_open
	// 	sol6_open = resultListRelay.items[0].sol6_open
	// 	sol7_open = resultListRelay.items[0].sol7_open
	// 	sol8a_open = resultListRelay.items[0].sol8a_open
	// 	sol8b_open = resultListRelay.items[0].sol8b_open		

	// }


	onMount(async () => {
		console.log("Called");
		// Subscribe to changes in the 'RelayStatus' collection
		PB.collection('RelayStatus').subscribe('*', function (e) {
			// Update the RelayStatus data store whenever a change is detected
			relayStatus.set(e.record);
			ac1_checked.set(e.record.ac1_open);
    		ac2_checked = e.record.ac2_open;
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
		
		const resultListRelay = await PB.collection('RelayStatus').getList(1, 1, {
			sort: '-created',
		});

		ac1_open = resultListRelay.items[0].ac1_open
		ac2_open = resultListRelay.items[0].ac2_open
		pbv1_open = resultListRelay.items[0].pbv1_open
		pbv2_open = resultListRelay.items[0].pbv2_open
		pbv3_open = resultListRelay.items[0].pbv3_open
		sol1_open = resultListRelay.items[0].sol1_open
		sol2_open = resultListRelay.items[0].sol2_open
		sol3_open = resultListRelay.items[0].sol3_open
		sol4_open = resultListRelay.items[0].sol4_open
		sol5_open = resultListRelay.items[0].sol5_open
		sol6_open = resultListRelay.items[0].sol6_open
		sol7_open = resultListRelay.items[0].sol7_open
		sol8a_open = resultListRelay.items[0].sol8a_open
		sol8b_open = resultListRelay.items[0].sol8b_open

		console.log('in record: ', ac1_open);
			
		const resultListPadBox = await PB.collection('PadBoxStatus').getList(1, 1, {
			sort: '-created',
		});

		continuity_1 = resultListPadBox.items[0].continuity_1
		continuity_2 = resultListPadBox.items[0].continuity_2
		box1_on = resultListPadBox.items[0].box1_on
		box2_on= resultListPadBox.items[0].box2_on



	})

	$: ac1_open = $relayStatus?.ac1_open || false;
	$: ac2_open = $relayStatus?.ac2_open || false;
	$: pbv1_open = $relayStatus?.pbv1_open || false;
	$: pbv2_open = $relayStatus?.pbv2_open || false;
	$: pbv3_open = $relayStatus?.pbv3_open || false;
	$: sol1_open = $relayStatus?.sol1_open || false;
	$: sol2_open = $relayStatus?.sol2_open || false;
	$: sol3_open = $relayStatus?.sol3_open || false;
	$: sol4_open = $relayStatus?.sol4_open || false;
	$: sol5_open = $relayStatus?.sol5_open || false;
	$: sol6_open = $relayStatus?.sol6_open || false;
	$: sol7_open = $relayStatus?.sol7_open || false;
	$: sol8a_open = $relayStatus?.sol8a_open || false;
	$: sol8b_open = $relayStatus?.sol8b_open || false;

	$: continuity_1 = $padBoxStatus?.continuity_1 || false;
	$: continuity_2 = $padBoxStatus?.continuity_2 || false;
	$: box1_on = $padBoxStatus?.box1_on || false;
	$: box2_on = $padBoxStatus?.box2_on || false;

	console.log('after react ', ac1_open);


	async function writePadBoxChange() {
		// Create a change on the 'PadBoxStatus' collection
		await PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'cont1': padbox_cont1_checked,
			'cont2': padbox_cont2_checked,
			'box1_on': padbox_box1_checked,
			'box2_on': padbox_box2_checked
		});
	}



	async function writeRelayStatusChange() {
		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': ac1_open,
			'ac2_open': ac2_open,
			'pbv1_open': pbv1_open,
			'pbv2_open': pbv2_open,
			'sol1_open': sol1_open,
			'sol2_open': sol2_open
		});

	}

	// function writeCombustionControlStatusChange() {
	// 	// Create a change on the 'CombustionControlStatus' collection
	// 	PB.collection('CombustionControlStatus').create ({
	// 		// Write a new record with all current values
	// 		'mev_power_enable': power_enable_checked
	// 	});
	// }

	async function handleAC1Change(e: any) {
		console.log(ac1_open);
		const target = e.target;
		const checked = target.checked;

		ac1_checked.set(checked);

		console.log('checked: ', ac1_checked);

		writeRelayStatusChange();
		console.log(ac1_open);


				// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': checked,
			'ac2_open': ac2_checked,
			'pbv1_open': pbv1_checked,
			'pbv2_open': pbv2_checked,
			'sol1_open': sol1_checked,
			'sol2_open': sol2_checked
		});
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

	// function handlePowerEnableChange(e: any) {
	// 	const target = e.target;
    // 	power_enable_checked = target.checked;
    // 	console.log(target.checked);

	// 	writeCombustionControlStatusChange();
	// }

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

	let lineColors = {
		horizontal1: 'red',
		horizontal2: 'red',
		horizontal3: 'green',
		horizontal4: 'yellow',
		horizontal5: 'blue',
		horizontal6: 'blue',
		horizontal7: 'blue',
		horizontal8: 'blue',
		horizontal9: 'blue',
		vertical0: 'red',
		vertical1: 'red',
		vertical2: 'green',
		vertical3: 'yellow',
		vertical4: 'blue',
		vertical5: 'blue',
		vertical6: 'blue',
		vertical7: 'blue',
		vertical8: 'blue',


  	};

	function changeColor(line: keyof typeof lineColors, color: string) {
    	lineColors[line] = color;
	}

	
</script>


<svelte:head></svelte:head>


<main> 
	
	<svg viewBox="0 0 170 80" width="100%" height="100%">
		<!-- Horizontal Lines -->
		<!-- Red -->
		<line x1="10" y1="10" x2="60" y2="10" stroke={lineColors.horizontal1} />
		<line x1="10" y1="30" x2="60" y2="30" stroke={lineColors.horizontal2} />

		<!-- Green -->
		<line x1="10" y1="60" x2="60" y2="60" stroke={lineColors.horizontal3} />

		<!-- Yellow -->
		<line x1="60" y1="20" x2="120" y2="20" stroke={lineColors.horizontal4} />

		<!-- Blue -->
		<line x1="90" y1="35" x2="100" y2="35" stroke={lineColors.horizontal5} />
		<line x1="90" y1="40" x2="105" y2="40" stroke={lineColors.horizontal6} />
		<line x1="90" y1="45" x2="110" y2="45" stroke={lineColors.horizontal7} />
		<line x1="90" y1="50" x2="140" y2="50" stroke={lineColors.horizontal8} />
		<line x1="90" y1="55" x2="145" y2="55" stroke={lineColors.horizontal9} />
	  
		<!-- Vertical Lines -->

		<!-- Red -->
		<line x1="60" y1="10" x2="60" y2="20" stroke={lineColors.vertical0} />
		<line x1="60" y1="20" x2="60" y2="30" stroke={lineColors.vertical1} />

		<!-- Green -->
		<line x1="60" y1="30" x2="60" y2="60" stroke={lineColors.vertical2} />

		<!-- Yellow-->
		<line x1="80" y1="10" x2="80" y2="20" stroke={lineColors.vertical3} />

		<!-- Blue -->
		<line x1="100" y1="20" x2="100" y2="35" stroke={lineColors.vertical4} />
		<line x1="105" y1="20" x2="105" y2="40" stroke={lineColors.vertical5} />
		<line x1="110" y1="20" x2="110" y2="45" stroke={lineColors.vertical6} />
		<line x1="140" y1="10" x2="140" y2="50" stroke={lineColors.vertical7} />
		<line x1="145" y1="10" x2="145" y2="55" stroke={lineColors.vertical8} />
	</svg>


	<p>{ac1_open}</p>
	<div>
		<input type="color" bind:value={lineColors.horizontal1} on:change={() => changeColor('horizontal1', lineColors.horizontal1)} />
		<input type="color" bind:value={lineColors.horizontal2} on:change={() => changeColor('horizontal2', lineColors.horizontal2)} />
		<input type="color" bind:value={lineColors.horizontal3} on:change={() => changeColor('horizontal3', lineColors.horizontal3)} />
		<input type="color" bind:value={lineColors.vertical1} on:change={() => changeColor('vertical1', lineColors.vertical1)} />
		<input type="color" bind:value={lineColors.vertical2} on:change={() => changeColor('vertical2', lineColors.vertical2)} />
	</div>

	<SlideToggle name="ac1_slider" bind:checked={$ac1_checked} on:change={handleAC1Change}> AC1 {ac1_open}</SlideToggle>
	<SlideToggle name="ac2_slider" bind:checked={ac2_open} on:change={handleAC2Change}> AC2 {ac2_open}</SlideToggle>

	<SlideToggle name="pbv1_slider" bind:checked={pbv1_open} on:change={handlePBV1Change}> PV1 {pbv1_open}</SlideToggle>
	<SlideToggle name="pbv2_slider" bind:checked={pbv2_open} on:change={handlePBV2Change}> PV2 {pbv2_open}</SlideToggle>

	<SlideToggle name="sol1_slider" bind:checked={sol1_open} on:change={handleSOL1Change}> SOL1 {sol1_open}</SlideToggle>
	<SlideToggle name="sol2_slider" bind:checked={sol2_open} on:change={handleSOL2Change}> SOL2 {sol2_open}</SlideToggle>

	<SlideToggle name="padbox_cont1_slider"  bind:checked={continuity_1} on:change={handleCont1Change}> Cont1 {continuity_1}</SlideToggle>
	<SlideToggle name="padbox_cont2_slider"  bind:checked={continuity_2} on:change={handleCont2Change}> Cont2 {continuity_2}</SlideToggle>
	<SlideToggle name="padbox_box1_slider"  bind:checked={box1_on} on:change={handleBox1Change}> Box1 {box1_on}</SlideToggle>
	<SlideToggle name="padbox_box2_slider"  bind:checked={box2_on} on:change={handleBox2Change}> Box2 {box2_on}</SlideToggle>

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

	@keyframes glow {
		0% {
			box-shadow:
				0 0 5px #00ff00,
				0 0 10px #00ff00,
				0 0 15px #00ff00,
				0 0 20px #00ff00;
		}
		100% {
			box-shadow:
				0 0 10px #00ff00,
				0 0 20px #00ff00,
				0 0 30px #00ff00,
				0 0 40px #00ff00;
		}
	}

	svg {
		width: 100%;
		height: 70px;
  	}

	line {
        stroke-width: 0.3;
    }



</style>
