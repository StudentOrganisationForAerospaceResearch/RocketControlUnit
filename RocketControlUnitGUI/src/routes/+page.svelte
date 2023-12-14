<script lang="ts">
	import { getModalStore } from '@skeletonlabs/skeleton';
	import type { ModalSettings } from '@skeletonlabs/skeleton';
	import { currentState } from '../store';

	let isActive = false;

	function toggleActive() {
		isActive = !isActive;
	}

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

<button on:click={toggleActive}>Toggle Line</button>
<div class={`line ${isActive ? 'active' : ''}`}></div>

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

<style>
	.line {
		width: 50%;
		height: 2px;
		background: gray;
		transition: background 0.3s ease;
		margin: 0 auto; /* Center the line */
	}

	.line.active {
		background: #00ff00;
		animation: glow 1s infinite;
	}

	.next-state-btn {
		position: fixed;
		left: 300px;
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
