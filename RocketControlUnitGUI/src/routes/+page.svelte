<script lang="ts">
	import { getModalStore, SlideToggle } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';

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
</script>



<svelte:head></svelte:head>


<main> 
	<h1>HELLO</h1>
	<SlideToggle name="slider-label" checked>(label)</SlideToggle>
	
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
</style>