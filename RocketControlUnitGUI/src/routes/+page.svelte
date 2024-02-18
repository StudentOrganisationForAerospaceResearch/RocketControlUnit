<script lang="ts">
	import { getModalStore, SlideToggle } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';
	import { onMount } from 'svelte';
    import { writable } from 'svelte/store';
	import PocketBase from 'pocketbase';

	const modalStore = getModalStore();

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

	let ac1_open = writable<boolean>(false);
	let ac2_open = writable<boolean>(false);
	let pbv1_open = writable<boolean>(false);
	let pbv2_open = writable<boolean>(false);	
	let sol1_open = writable<boolean>(false);		
	let sol2_open = writable<boolean>(false);
	let padbox_continuity1 = writable<boolean>(false);
	let padbox_continuity2= writable<boolean>(false);
	let padbox_box1_on = writable<boolean>(false);
	let padbox_box2_on = writable<boolean>(false);

	let PB = new PocketBase("http://127.0.0.1:8090");
	

	onMount(async () => {
		console.log("Called");
		// Subscribe to changes in the 'RelayStatus' collection 
		PB.collection('RelayStatus').subscribe('*', function (e) {

			// Update the RelayStatus data store on startup
			ac1_open.set(e.record.ac1_open);
			ac2_open.set(e.record.ac2_open);
			pbv1_open.set(e.record.pbv1_open);
			pbv2_open.set(e.record.pbv2_open);
			sol1_open.set(e.record.sol1_open);
			sol2_open.set(e.record.sol2_open);
		});

		// Subscribe to changes in the 'CombustionControlStatus' collection 
		PB.collection('CombustionControlStatus').subscribe('*', function (e) {
		});

		// Subscribe to changes in the 'RcuTemp' collection 
		PB.collection('RcuTemp').subscribe('*', function (e) {
			// Update the RcuTemp data store on startup
		});

		// Subscribe to changes in the 'PadBoxStatus' collection
		PB.collection('PadBoxStatus').subscribe('*', function (e) {

			// Update the PadBoxStatus data store on startup
			padbox_continuity1.set(e.record.continuity_1);
			padbox_continuity2.set(e.record.continuity_2);
			padbox_box1_on.set(e.record.box1_on);
			padbox_box2_on.set(e.record.box2_on);

		});
	})

	async function handleAC1Change(e: any) {
		const checked = e.target.checked;
		ac1_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': checked,
			'ac2_open': $ac2_open,
			'pbv1_open': $pbv1_open,
			'pbv2_open': $pbv2_open,
			'sol1_open': $sol1_open,
			'sol2_open': $sol2_open
		});
	}

	async function handleAC2Change(e: any) {
		const checked = e.target.checked;
		ac2_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': $ac1_open,
			'ac2_open': checked,
			'pbv1_open': $pbv1_open,
			'pbv2_open': $pbv2_open,
			'sol1_open': $sol1_open,
			'sol2_open': $sol2_open
		});
	}

	async function handlePBV1Change(e: any) {
		const checked = e.target.checked;
		pbv1_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': $ac1_open,
			'ac2_open': $ac2_open,
			'pbv1_open': checked,
			'pbv2_open': $pbv2_open,
			'sol1_open': $sol1_open,
			'sol2_open': $sol2_open
		});
	}
	

	async function handlePBV2Change(e: any) {
		const checked = e.target.checked;
		pbv2_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': $ac1_open,
			'ac2_open': $ac2_open,
			'pbv1_open': $pbv1_open,
			'pbv2_open': checked,
			'sol1_open': $sol1_open,
			'sol2_open': $sol2_open
		});
	}

	async function handleSOL1Change(e: any) {
		const checked = e.target.checked;
		sol1_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': $ac1_open,
			'ac2_open': $ac2_open,
			'pbv1_open': $pbv1_open,
			'pbv2_open': $pbv2_open,
			'sol1_open': checked,
			'sol2_open': $sol2_open
		});
	}

	async function handleSOL2Change(e: any) {
		const checked = e.target.checked;
		sol2_open.set(checked);

		// Create a change on the 'RelayStatus' collection
		await PB.collection('RelayStatus').create ({
			// Write a new record with all current values
			'ac1_open': $ac1_open,
			'ac2_open': $ac2_open,
			'pbv1_open': $pbv1_open,
			'pbv2_open': $pbv2_open,
			'sol1_open': $sol1_open,
			'sol2_open': checked
		});
	}

	async function handleCont1Change(e: any) {
		const checked = e.target.checked;
		padbox_continuity1.set(checked);

		// Create a change on the 'PadBoxStatus' collection
		await PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'continuity_1': checked,
			'continuity_2': $padbox_continuity2,
			'box1_on': $padbox_box1_on,
			'box2_on': $padbox_box2_on
		});
	}

	async function handleCont2Change(e: any) {
		const checked = e.target.checked;
		padbox_continuity2.set(checked);

		// Create a change on the 'PadBoxStatus' collection
		await PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'continuity_1': $padbox_continuity1,
			'continuity_2': checked,
			'box1_on': $padbox_box1_on,
			'box2_on': $padbox_box2_on
		});
	}

	async function handleBox1Change(e: any) {
		const checked = e.target.checked;
		padbox_box1_on.set(checked);

		// Create a change on the 'PadBoxStatus' collection
		await PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'continuity_1': $padbox_continuity1,
			'continuity_2': $padbox_continuity2,
			'box1_on': checked,
			'box2_on': $padbox_box2_on
		});
	}

	async function handleBox2Change(e: any) {
		const checked = e.target.checked;
		padbox_box2_on.set(checked);

		// Create a change on the 'PadBoxStatus' collection
		await PB.collection('PadBoxStatus').create ({
			// Write a new record with all current values
			'continuity_1': $padbox_continuity1,
			'continuity_2': $padbox_continuity2,
			'box1_on': $padbox_box1_on,
			'box2_on': checked
		});
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


	<p>{$ac1_open}</p>
	<div>
		<input type="color" bind:value={lineColors.horizontal1} on:change={() => changeColor('horizontal1', lineColors.horizontal1)} />
		<input type="color" bind:value={lineColors.horizontal2} on:change={() => changeColor('horizontal2', lineColors.horizontal2)} />
		<input type="color" bind:value={lineColors.horizontal3} on:change={() => changeColor('horizontal3', lineColors.horizontal3)} />
		<input type="color" bind:value={lineColors.vertical1} on:change={() => changeColor('vertical1', lineColors.vertical1)} />
		<input type="color" bind:value={lineColors.vertical2} on:change={() => changeColor('vertical2', lineColors.vertical2)} />
	</div>

	<SlideToggle name="ac1_slider" bind:checked={$ac1_open} on:change={handleAC1Change}> AC1 {$ac1_open}</SlideToggle>
	<SlideToggle name="ac2_slider" bind:checked={$ac2_open} on:change={handleAC2Change}> AC2 {$ac2_open}</SlideToggle>

	<SlideToggle name="pbv1_slider" bind:checked={$pbv1_open} on:change={handlePBV1Change}> PV1 {$pbv1_open}</SlideToggle>
	<SlideToggle name="pbv2_slider" bind:checked={$pbv2_open} on:change={handlePBV2Change}> PV2 {$pbv2_open}</SlideToggle>

	<SlideToggle name="sol1_slider" bind:checked={$sol1_open} on:change={handleSOL1Change}> SOL1 {$sol1_open}</SlideToggle>
	<SlideToggle name="sol2_slider" bind:checked={$sol2_open} on:change={handleSOL2Change}> SOL2 {$sol2_open}</SlideToggle>

	<SlideToggle name="padbox_cont1_slider"  bind:checked={$padbox_continuity1} on:change={handleCont1Change}> Cont1 {$padbox_continuity1}</SlideToggle>
	<SlideToggle name="padbox_cont2_slider"  bind:checked={$padbox_continuity2} on:change={handleCont2Change}> Cont2 {$padbox_continuity2}</SlideToggle>
	<SlideToggle name="padbox_box1_slider"  bind:checked={$padbox_box1_on} on:change={handleBox1Change}> Box1 {$padbox_box1_on}</SlideToggle>
	<SlideToggle name="padbox_box2_slider"  bind:checked={$padbox_box2_on} on:change={handleBox2Change}> Box2 {$padbox_box2_on}</SlideToggle>



	<!-- Future TC Values -->
	<!-- <h1>TC1 {$rcuTemp && 'tc1_temp' in $rcuTemp ? $rcuTemp.tc1_temp: 'N/A'}</h1>
	<h1>TC2 {$rcuTemp && 'tc2_temp ' in $rcuTemp ? $rcuTemp.tc2_temp : 'N/A'}</h1> -->

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
