<script lang='ts'>
	// Other code
	import {
		getModalStore,
		Modal
	} from '@skeletonlabs/skeleton';
	import type { ModalSettings, ModalComponent, ModalStore } from '@skeletonlabs/skeleton';

	let isActive = false;

	function toggleActive() {
		isActive = !isActive;
	}

	const modalStore = getModalStore();

	function modalConfirm(): void {
		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: 'Are you sure you wish to proceed to the next state?',
			response: (r: boolean) => console.log('response:', r)
		};
		modalStore.trigger(modal);
	}
	const states = {
    RS_PRELAUNCH: 'PreLaunch',
    RS_FILL: 'Fill',
    RS_ARM: 'Arm',
    RS_IGNITION: 'Ignition',
    RS_LAUNCH: 'Launch',
    RS_BURN: 'Burn',
    RS_COAST: 'Coast',
    RS_DESCENT: 'Descent',
    RS_RECOVERY: 'Recovery',
    RS_ABORT: 'Abort',
    RS_TEST: 'Test',
  };

  let currentState = states.RS_PRELAUNCH;

  function nextState(state:string) {
    currentState = state;
  }
</script>

<button on:click={toggleActive}>Toggle Line</button>
<div class={`line ${isActive ? 'active' : ''}`}></div>

<!-- Render different buttons based on the current state -->
<!-- Render different buttons based on the current state -->
{#if currentState === states.RS_PRELAUNCH}
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_FILL)}>Go to Fill</button>
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 130px;" on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button>
{:else if currentState === states.RS_FILL}
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_PRELAUNCH)}>Go to Pre-Launch</button>
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_ARM)}>Go to Arm</button>
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 130px;" on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button>
{:else if currentState === states.RS_ARM}
  <button class="btn variant-filled-warning next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_IGNITION)}>Go to Ignition</button>
  <button class="btn variant-filled-warning next-state-btn" style="bottom: 130px;" on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button>
{:else if currentState === states.RS_IGNITION}
  <button class="btn variant-filled-error next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_LAUNCH)}>LAUNCH</button>
  <button class="btn variant-filled-error next-state-btn" style="bottom: 130px;" on:click={() => nextState(states.RS_ABORT)}>Go to Abort</button>
{:else if currentState === states.RS_ABORT}
  <button class="btn variant-filled-surface next-state-btn" style="bottom: 80px;" on:click={() => nextState(states.RS_PRELAUNCH)}>Go to Pre-Launch</button>
{:else if currentState === states.RS_LAUNCH}
  <h1> nice rocket bro</h1>
  <!-- Add more else if blocks for other states -->
{/if}

<!-- Other page content -->

<style>
	.line {
		width: 50%; /* Adjust this value to change the length of the line */
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
		0% { box-shadow: 0 0 5px #00ff00, 0 0 10px #00ff00, 0 0 15px #00ff00, 0 0 20px #00ff00; }
		100% { box-shadow: 0 0 10px #00ff00, 0 0 20px #00ff00, 0 0 30px #00ff00, 0 0 40px #00ff00; }
	}
</style>