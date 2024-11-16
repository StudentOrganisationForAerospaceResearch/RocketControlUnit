<script lang="ts">
	import "../styles/display.postcss";
	import Diagram from '$lib/components/Diagram.svelte';
	import { initTimestamps, type Timestamps } from '$lib/timestamps';
	import { usePocketbase } from '$lib/hooks/usePocketbase';
	import { initStores, auth, currentState } from '$lib/stores';
	import { useInteraction } from '$lib/hooks/useInteraction';
	import { onMount } from 'svelte';
	import { SlideToggle } from '@skeletonlabs/skeleton';

	const timestamps = initTimestamps();
	const stores = initStores();
	const usePocketbaseHook = usePocketbase(timestamps, stores);
	const useInteractionHook = useInteraction(usePocketbaseHook);

	const {
		authenticate,
		sendHeartbeat,
		subscribeToCollections,
		writeStateChange,
		writeArbitraryCommand,
		writeLoadCellCommand
	} = usePocketbaseHook;

	const {
		confirmStateChange,
		instantStateChange,
		resumeConfirmRemoveWeight
	} = useInteractionHook;

	// Destructure stores for later use
	const {
		ac1_open,
        pbv1_open,
        pbv2_open,
        pbv3_open,
        pbv4_open,
        sol5_open,
        sol6_open,
        sol7_open,
        sol8a_open,
        sol8b_open,
        box1_on,
        box2_on,
        vent_open,
        drain_open,
        mev_open,
        rcu_tc1_temperature,
        rcu_tc2_temperature,
        battery_voltage,
		power_source,
		upper_pv_pressure,
		rocket_mass,
		nos1_mass,
		nos2_mass,
		ib_pressure,
		lower_pv_pressure,
		pv_temperature,
		pt1_pressure,
		pt2_pressure,
		pt3_pressure,
		pt4_pressure,
		sob_tc1_temperature,
		sob_tc2_temperature,
		system_state,
		timer_state,
		timer_period,
		timer_remaining
	} = stores;
	
	onMount(() => {
		let heartbeatInterval: NodeJS.Timeout;

		// Handle pocketbase authentication
		const handleAuth = async () => {
			$auth = await authenticate();

			if ($auth === true) {
				heartbeatInterval = setInterval(async () => {
					await sendHeartbeat();
				}, 5000); // 5000 milliseconds = 5 seconds
			}
		}

		handleAuth();

		// Subscribe to pocket base events
		subscribeToCollections();

		// Handle displaying outdated data
		let containerElement = document.querySelector('.container') as HTMLElement;

		let timestampInterval = setInterval(() => {
			for (let variable in timestamps) {
				let elements = document.getElementsByClassName(variable);
				if (!elements.length) continue;

				for(let i = 0; i < elements.length; i++) {
					let element = elements[i];

					if (Date.now() - timestamps[variable as keyof Timestamps] > 5000) {
						element.classList.add('outdated');
					} else {
						element.classList.remove('outdated');
					}
				}
			}
		}, 1000);

		// Define the resize handler
		const handleResize = () => {
			if (containerElement) {
				let containerWidth = containerElement.offsetWidth;
				let containerHeight = containerElement.offsetHeight;

				document.documentElement.style.setProperty('--container-width', `${containerWidth}px`);
				document.documentElement.style.setProperty('--container-height', `${containerHeight}px`);
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

		// Return a cleanup function
		return () => {
			clearInterval(heartbeatInterval); // Stop the interval when the component is destroyed
			clearInterval(timestampInterval);

			window.removeEventListener('resize', handleResize);
		};
	});

	$: ac1_display = $ac1_open === undefined ? 'N/A' : $ac1_open ? 'ON' : 'OFF';

	$: pbv1_display = $pbv1_open === undefined ? 'N/A' : $pbv1_open ? 'OPEN' : 'CLOSE';
	$: pbv2_display = $pbv2_open === undefined ? 'N/A' : $pbv2_open ? 'OPEN' : 'CLOSE';
	$: pbv3_display = $pbv3_open === undefined ? 'N/A' : $pbv3_open ? 'OPEN' : 'CLOSE';
	$: pbv4_display = $pbv4_open === undefined ? 'N/A' : $pbv4_open ? 'CLOSE' : 'OPEN';

	$: sol5_display = $sol5_open === undefined ? 'N/A' : $sol5_open ? 'OPEN' : 'CLOSE';
	$: sol6_display = $sol6_open === undefined ? 'N/A' : $sol6_open ? 'OPEN' : 'CLOSE';
	$: sol7_display = $sol7_open === undefined ? 'N/A' : $sol7_open ? 'OPEN' : 'CLOSE';
	$: sol8a_display = $sol8a_open === undefined ? 'N/A' : $sol8a_open ? 'OPEN' : 'CLOSE';
	$: sol8b_display = $sol8b_open === undefined ? 'N/A' : $sol8b_open ? 'OPEN' : 'CLOSE';

	$: box1_display = $box1_on === undefined ? 'N/A' : $box1_on ? 'LIVE' : 'DEAD';
	$: box2_display = $box2_on === undefined ? 'N/A' : $box2_on ? 'LIVE' : 'DEAD';

	$: vent_display = $vent_open === undefined ? 'N/A' : $vent_open ? 'OPEN' : 'CLOSED';
	$: drain_display = $drain_open === undefined ? 'N/A' : $drain_open ? 'OPEN' : 'CLOSED';

	$: rcu_tc1_display = $rcu_tc1_temperature === undefined ? 'N/A' : $rcu_tc1_temperature;
	$: rcu_tc2_display = $rcu_tc2_temperature === undefined ? 'N/A' : $rcu_tc2_temperature;

	$: mev_display = $mev_open === undefined ? 'N/A' : $mev_open ? 'OPEN' : 'CLOSED';

	$: battery_display = $battery_voltage === undefined ? 'N/A' : $battery_voltage;
	$: power_display = $power_source === undefined ? 'N/A' : $power_source ? 'ROCKET' : 'GROUND';

	$: upper_pv_display = $upper_pv_pressure === undefined ? 'DC' : $upper_pv_pressure;

	$: rocket_mass_display = $rocket_mass === undefined ? 'N/A' : Number($rocket_mass).toFixed(2);

	$: nos1_mass_display = $nos1_mass === undefined ? 'N/A' : Number($nos1_mass).toFixed(2);
	$: nos2_mass_display = $nos2_mass === undefined ? 'N/A' : Number($nos2_mass).toFixed(2);

	$: ib_pressure_display = $ib_pressure === undefined ? 'N/A' : $ib_pressure;
	$: lower_pv_display = $lower_pv_pressure === undefined ? 'N/A' : $lower_pv_pressure;

	$: pv_temperature_display = $pv_temperature === undefined ? 'N/A' : $pv_temperature;

	$: pt1_pressure_display = $pt1_pressure === undefined ? 'N/A' : $pt1_pressure;
	$: pt2_pressure_display = $pt2_pressure === undefined ? 'N/A' : $pt2_pressure;
	$: pt3_pressure_display = $pt3_pressure === undefined ? 'N/A' : $pt3_pressure;
	$: pt4_pressure_display = $pt4_pressure === undefined ? 'N/A' : $pt4_pressure;

	$: sob_tc1_display = $sob_tc1_temperature === undefined ? 'N/A' : $sob_tc1_temperature;
	$: sob_tc2_display = $sob_tc2_temperature === undefined ? 'N/A' : $sob_tc2_temperature;

	$: system_state_display = $system_state === undefined ? 'N/A' : $system_state.replace('SYS_', '');

	$: timer_state_display = $timer_state === undefined ? 'N/A' : $timer_state;
	$: timer_period_display = $timer_period === undefined ? 'N/A' : ($timer_period / 1000).toFixed(0); // Convert to seconds
	$: timer_remaining_display = $timer_remaining === undefined ? 'N/A' : ($timer_remaining / 1000).toFixed(0); // Convert to seconds

	$: relayStatusOutdated = Date.now() - timestamps.relay_status > 5000;
	$: combustionControlStatusOutdated = Date.now() - timestamps.combustion_control_status > 5000;
	$: rcuTempOutdated = Date.now() - timestamps.rcu_temp > 5000;
	$: batteryOutdated = Date.now() - timestamps.battery > 5000;
	$: launchRailLoadCellOutdated = Date.now() - timestamps.launch_rail_load_cell > 5000;
	$: nosLoadCellOutdated = Date.now() - timestamps.nos_load_cell > 5000;
	$: pbbPressureOutdated = Date.now() - timestamps.pbb_pressure > 5000;
	$: pbbTemperatureOutdated = Date.now() - timestamps.pbb_temperature > 5000;
	$: rcuPressureOutdated = Date.now() - timestamps.rcu_pressure > 5000;
	$: sobTemperatureOutdated = Date.now() - timestamps.sob_temperature > 5000;
	$: sysStateOutdated = Date.now() - timestamps.sys_state > 5000;
	$: heartbeatOutdated = Date.now() - timestamps.heartbeat > 5000;

	const handleSliderChange = async (e: any, target: string, openCommand: string, closeCommand: string) => {
		e.preventDefault();

		// Determine the command based on the current value of the slider
		const command = e.target.checked ? openCommand : closeCommand;

		// Create a change on the 'RelayStatus' collection
		writeArbitraryCommand(target, command);
	}

	let wasLiveAtAnyPoint = false;

	const pollIgnitors = async () => {
		if (box1_display === 'LIVE' || box2_display === 'LIVE') {
			wasLiveAtAnyPoint = true;
		}
	}

	const handleLaunchSequence = async () => {
		await writeArbitraryCommand('NODE_RC', 'RC_IGNITE_PAD_BOX1');
		await writeArbitraryCommand('NODE_RC', 'RC_IGNITE_PAD_BOX2');

		const pollInterval = setInterval(pollIgnitors, 100);
		await new Promise(resolve => setTimeout(resolve, 3500));

		clearInterval(pollInterval);

		if (wasLiveAtAnyPoint) {
			for (let i = 0; i < 3; i++) {
				await writeStateChange('RSC_IGNITION_TO_LAUNCH');
				await new Promise(resolve => setTimeout(resolve, 100));
			} 
		}

		wasLiveAtAnyPoint = false;
	}

	const performTare = (loadcell: string) => {
		writeLoadCellCommand(loadcell, "TARE", 0);
	}

	// NOTE: This seems odd but since the event will switch these MUST be swapped
	// Open to alternate ways of doing it. Everything I tried didn't work.
	const handleIgnition = async (e: MouseEvent) => {
		await handleSliderChange(e, 'NODE_RCU', 'RCU_IGNITE_PAD_BOX1', 'RCU_KILL_BOX1');
		await handleSliderChange(e, 'NODE_RCU', 'RCU_KILL_PAD_BOX2', 'RCU_IGNITE_PAD_BOX2');
	}
</script>

<div class="container">
	<Diagram />

	<div class="ac1_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="ac1_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$ac1_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_AC1', 'RCU_CLOSE_AC1')}
		>
			{ac1_display}
		</SlideToggle>
	</div>

	<div class="pbv1_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="pbv1_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv1_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV1', 'RCU_CLOSE_PBV1')}
		>
			{pbv1_display}
		</SlideToggle>
	</div>

	<div class="pbv2_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="pbv2_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv2_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV2', 'RCU_CLOSE_PBV2')}
		>
			{pbv2_display}
		</SlideToggle>
	</div>

	<div class="pbv3_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="pbv3_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv3_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV3', 'RCU_CLOSE_PBV3')}
		>
			{pbv3_display}
		</SlideToggle>
	</div>

	<div class="pbv4_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="pbv4_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$pbv4_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_PBV4', 'RCU_CLOSE_PBV4')}
		>
			{pbv4_display}
		</SlideToggle>
	</div>
	
	<div class="sol5_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="sol5_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol5_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL5', 'RCU_CLOSE_SOL5')}
		>
			{sol5_display}
		</SlideToggle>
	</div>

	<div class="sol6_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="sol6_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol6_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL6', 'RCU_CLOSE_SOL6')}
		>
			{sol6_display}
		</SlideToggle>
	</div>

	<div class="sol7_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="sol7_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol7_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL7', 'RCU_CLOSE_SOL7')}
		>
			{sol7_display}
		</SlideToggle>
	</div>

	<div class="sol8a_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="sol8a_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol8a_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL8A', 'RCU_CLOSE_SOL8A')}
		>
			{sol8a_display}
		</SlideToggle>
	</div>

	<div class="sol8b_slider relay_status {relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="sol8b_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$sol8b_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'RCU_OPEN_SOL8B', 'RCU_CLOSE_SOL8B')}
		>
			{sol8b_display}
		</SlideToggle>
	</div>

	<div class="vent_slider combustion_control_status {combustionControlStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="vent_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$vent_open}
			on:click={(e) => handleSliderChange(e, 'NODE_DMB', 'RSC_OPEN_VENT', 'RSC_CLOSE_VENT')}
		>
			{vent_display}
		</SlideToggle>
	</div>

	<div class="drain_slider combustion_control_status {combustionControlStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="drain_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$drain_open}
			on:click={(e) => handleSliderChange(e, 'NODE_DMB', 'RSC_OPEN_DRAIN', 'RSC_CLOSE_DRAIN')}
		>
			{drain_display}
		</SlideToggle>
	</div>

	<div class="power_source_slider battery {batteryOutdated  ? 'outdated' : ''}">
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
			{power_display}
		</SlideToggle>
	</div>

	{#if $currentState === "RS_IGNITION" || $currentState === "RS_TEST" || $currentState === "RS_ABORT" || $currentState === "RS_LAUNCH" || $currentState === "RS_BURN" || $currentState === "RS_COAST" || $currentState === "RS_RECOVERY"}
		<div class="box1_slider">
			<SlideToggle
				name="box1_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$box1_on}
				on:click={handleIgnition}
				disabled={$currentState === "RS_IGNITION" || $currentState === "RS_ABORT" || $currentState === "RS_LAUNCH" || $currentState === "RS_BURN" || $currentState === "RS_COAST" || $currentState === "RS_RECOVERY"}
			>
				{box1_display}
			</SlideToggle>
		</div>

		<div class="box2_slider">
			<SlideToggle
				name="box2_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$box2_on}
				on:click={handleIgnition}
				disabled={$currentState === "RS_IGNITION" || $currentState === "RS_ABORT" || $currentState === "RS_LAUNCH" || $currentState === "RS_BURN" || $currentState === "RS_COAST" || $currentState === "RS_RECOVERY"}
			>
				{box2_display}
			</SlideToggle>
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
				writeLoadCellCommand("NOS1", "CANCEL", 0);
				resumeConfirmRemoveWeight("NOS1");}}
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
				writeLoadCellCommand("NOS2", "CANCEL", 0);	
				resumeConfirmRemoveWeight("NOS2");}}
		>
			CAL
		</button>
	</div>

	<div class="rail_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("LAUNCHRAIL")}
		>
			TARE
		</button>
	</div>

	<div class="rail_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => { 
				writeLoadCellCommand("LAUNCHRAIL", "CANCEL", 0);
				resumeConfirmRemoveWeight("LAUNCHRAIL");}}
		>
			CAL
		</button>
	</div>

	<div class="rcu_tc1 rcu_temp {rcuTempOutdated ? 'outdated' : ''}">
		<p>{rcu_tc1_display}</p>
	</div>

	<div class="rcu_tc2 rcu_temp {rcuTempOutdated ? 'outdated' : ''}">
		<p>{rcu_tc2_display}</p>
	</div>

	<div class="nos1 nos_load_cell {nosLoadCellOutdated ? 'outdated' : ''}">
		<p>{nos1_mass_display}</p>
	</div>

	<div class="nos2 nos_load_cell {nosLoadCellOutdated ? 'outdated' : ''}">
		<p>{nos2_mass_display}</p>
	</div>

	<div class="pt1_pressure rcu_pressure {rcuPressureOutdated ? 'outdated' : ''}">
		<p>{pt1_pressure_display}</p>
	</div>

	<div class="pt2_pressure rcu_pressure {rcuPressureOutdated ? 'outdated' : ''}">
		<p>{pt2_pressure_display}</p>
	</div>

	<div class="pt3_pressure rcu_pressure {rcuPressureOutdated ? 'outdated' : ''}">
		<p>{pt3_pressure_display}</p>
	</div>

	<div class="pt4_pressure rcu_pressure {rcuPressureOutdated ? 'outdated' : ''}">
		<p>{pt4_pressure_display}</p>
	</div>

	<div class="box1_continuity">
	</div>

	<div class="box2_continuity">
	</div>

	<div class="mev_status combustion_control_status {combustionControlStatusOutdated ? 'outdated' : ''}">
		<p>{mev_display}</p>
	</div>

	<div class="battery_voltage  battery {batteryOutdated ? 'outdated' : ''}">
		<p>{battery_display}</p>
	</div>

	<div class="upper_pv_pressure">
		<p>{upper_pv_display}</p>
	</div>

	<div class="rocket_mass launch_rail_load_cell {launchRailLoadCellOutdated ? 'outdated' : ''}">
		<p>{rocket_mass_display}</p>
	</div>

	<div class="ib_pressure pbb_pressure {pbbPressureOutdated ? 'outdated' : ''}">
		<p>{ib_pressure_display}</p>
	</div>

	<div class="lower_pv_pressure pbb_pressure {pbbPressureOutdated ? 'outdated' : ''}">
		<p>{lower_pv_display}</p>
	</div>

	<div class="pv_temperature pbb_temperature {pbbTemperatureOutdated ? 'outdated' : ''}">
		<p>{pv_temperature_display}</p>
	</div>

	<div class="sob_tc1 sob_temperature {sobTemperatureOutdated ? 'outdated' : ''}">
		<p>{sob_tc1_display}</p>
	</div>

	<div class="sob_tc2 sob_temperature {sobTemperatureOutdated ? 'outdated' : ''}">
		<p>{sob_tc2_display}</p>
	</div>

	<div class="system_state sys_state {sysStateOutdated ? 'outdated' : ''}">
		<p>{system_state_display}</p>
	</div>

	<div class="timer_state heartbeat {heartbeatOutdated ? 'outdated' : ''}">
		<p>{timer_state_display}</p>
	</div>

	<div class="timer_period heartbeat {heartbeatOutdated ? 'outdated' : ''}">
		<p>{timer_period_display}</p>
	</div>

	<div class="timer_remaining heartbeat {heartbeatOutdated ? 'outdated' : ''}">
		<p>{timer_remaining_display}</p>
	</div>

	<!-- Render different buttons based on the current state -->
	{#if $currentState == "RS_PRELAUNCH"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("RSC_GOTO_FILL")}
		>
			Go to Fill
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "RS_FILL"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("RSC_GOTO_PRELAUNCH")}
		>
			Go to Pre-Launch
		</button>
		<button
			class="btn variant-filled-warning arm_button"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => instantStateChange("RSC_ARM_CONFIRM_1")}
		>
			ARM CONFIRM 1
		</button>
		<button
			class="btn variant-filled-warning arm_button"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => instantStateChange("RSC_ARM_CONFIRM_2")}
		>
			ARM CONFIRM 2
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => confirmStateChange("RSC_GOTO_ARM")}
		>
			Go to Arm
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "RS_ARM"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("RSC_GOTO_FILL")}
		>
			Go to Fill
		</button>
		<button
			class="btn variant-filled-warning next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => confirmStateChange("RSC_GOTO_IGNITION")}
		>
			Go to Ignition
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "RS_IGNITION"}
		<button
			class="btn variant-filled-error next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => handleLaunchSequence()}
		>
			LAUNCH
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("RSC_GOTO_ARM")}
		>
			Go to Arm
		</button>
	{:else if $currentState == "RS_ABORT"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => confirmStateChange("RSC_GOTO_PRELAUNCH")}
		>
			Go to Pre-Launch
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("RSC_GOTO_TEST")}
		>
			Go to Test
		</button>
	{:else if $currentState == "RS_RECOVERY"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "RS_TEST"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => instantStateChange("RSC_TEST_MEV_OPEN")}
		>
			Open MEV
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => instantStateChange("RSC_MEV_CLOSE")}
		>
			Close MEV
		</button>
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
</style>