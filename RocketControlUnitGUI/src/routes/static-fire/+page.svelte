<script lang="ts">
    import StaticFire from "../../lib/components/StaticFire.svelte";
	import "../../styles/static-fire.postcss"
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
        static_fire_pbv1_open,
        static_fire_pbv2_open,
        static_fire_pbv3_open,
        static_fire_pbv4_open,
        static_fire_sol5_open,
        static_fire_sol6_open,
        static_fire_sol7_open,
        static_fire_sol8a_open,
        static_fire_sol8b_open,
        static_fire_box1_on,
        static_fire_box2_on,
        static_fire_vent_open,
        static_fire_drain_open,
        static_fire_mev_open,
        static_fire_rcu_tc1_temperature,
        static_fire_rcu_tc2_temperature,
		static_fire_power_source,
		static_fire_upper_pv_pressure,
		static_fire_rocket_mass,
		static_fire_nos1_mass,
		static_fire_nos2_mass,
		static_fire_lower_pv_pressure,
		static_fire_pv_temperature,
		static_fire_pt1_pressure,
		static_fire_pt2_pressure,
		static_fire_pt3_pressure,
		static_fire_pt4_pressure,
		static_fire_sob_tc1_temperature,
		static_fire_sob_tc2_temperature,
		static_fire_system_state,
		static_fire_timer_period,
		static_fire_timer_remaining,
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

	$: static_fire_pbv1_display = $static_fire_pbv1_open === undefined ? 'N/A' : $static_fire_pbv1_open ? 'OPEN' : 'CLOSE';
	$: static_fire_pbv2_display = $static_fire_pbv2_open === undefined ? 'N/A' : $static_fire_pbv2_open ? 'OPEN' : 'CLOSE';
	$: static_fire_pbv3_display = $static_fire_pbv3_open === undefined ? 'N/A' : $static_fire_pbv3_open ? 'OPEN' : 'CLOSE';
	$: static_fire_pbv4_display = $static_fire_pbv4_open === undefined ? 'N/A' : $static_fire_pbv4_open ? 'CLOSE' : 'OPEN';

	$: static_fire_sol5_display = $static_fire_sol5_open === undefined ? 'N/A' : $static_fire_sol5_open ? 'OPEN' : 'CLOSE';
	$: static_fire_sol6_display = $static_fire_sol6_open === undefined ? 'N/A' : $static_fire_sol6_open ? 'OPEN' : 'CLOSE';
	$: static_fire_sol7_display = $static_fire_sol7_open === undefined ? 'N/A' : $static_fire_sol7_open ? 'OPEN' : 'CLOSE';
	$: static_fire_sol8a_display = $static_fire_sol8a_open === undefined ? 'N/A' : $static_fire_sol8a_open ? 'OPEN' : 'CLOSE';
	$: static_fire_sol8b_display = $static_fire_sol8b_open === undefined ? 'N/A' : $static_fire_sol8b_open ? 'OPEN' : 'CLOSE';

	$: static_fire_box1_display = $static_fire_box1_on === undefined ? 'N/A' : $static_fire_box1_on ? 'LIVE' : 'DEAD';
	$: static_fire_box2_display = $static_fire_box2_on === undefined ? 'N/A' : $static_fire_box2_on ? 'LIVE' : 'DEAD';

	$: static_fire_vent_display = $static_fire_vent_open === undefined ? 'N/A' : $static_fire_vent_open ? 'OPEN' : 'CLOSED';
	$: static_fire_drain_display = $static_fire_drain_open === undefined ? 'N/A' : $static_fire_drain_open ? 'OPEN' : 'CLOSED';

	$: static_fire_rcu_tc1_display = $static_fire_rcu_tc1_temperature === undefined ? 'N/A' : $static_fire_rcu_tc1_temperature;
	$: static_fire_rcu_tc2_display = $static_fire_rcu_tc2_temperature === undefined ? 'N/A' : $static_fire_rcu_tc2_temperature;

	$: static_fire_mev_display = $static_fire_mev_open === undefined ? 'N/A' : $static_fire_mev_open ? 'OPEN' : 'CLOSED';


	$: static_fire_power_display = $static_fire_power_source === undefined ? 'N/A' : $static_fire_power_source ? 'ROCKET' : 'GROUND';

	$: static_fire_upper_pv_display = $static_fire_upper_pv_pressure === undefined ? 'DC' : $static_fire_upper_pv_pressure;

	$: static_fire_rocket_mass_display = $static_fire_rocket_mass === undefined ? 'N/A' : Number($static_fire_rocket_mass).toFixed(2);

	$: static_fire_nos1_mass_display = $static_fire_nos1_mass === undefined ? 'N/A' : Number($static_fire_nos1_mass).toFixed(2);
	$: static_fire_nos2_mass_display = $static_fire_nos2_mass === undefined ? 'N/A' : Number($static_fire_nos2_mass).toFixed(2);

	$: static_fire_lower_pv_display = $static_fire_lower_pv_pressure === undefined ? 'N/A' : $static_fire_lower_pv_pressure;

	$: static_fire_pv_temperature_display = $static_fire_pv_temperature === undefined ? 'N/A' : $static_fire_pv_temperature;

	$: static_fire_pt1_pressure_display = $static_fire_pt1_pressure === undefined ? 'N/A' : $static_fire_pt1_pressure;
	$: static_fire_pt2_pressure_display = $static_fire_pt2_pressure === undefined ? 'N/A' : $static_fire_pt2_pressure;
	$: static_fire_pt3_pressure_display = $static_fire_pt3_pressure === undefined ? 'N/A' : $static_fire_pt3_pressure;
	$: static_fire_pt4_pressure_display = $static_fire_pt4_pressure === undefined ? 'N/A' : $static_fire_pt4_pressure;

	$: static_fire_sob_tc1_display = $static_fire_sob_tc1_temperature === undefined ? 'N/A' : $static_fire_sob_tc1_temperature;
	$: static_fire_sob_tc2_display = $static_fire_sob_tc2_temperature === undefined ? 'N/A' : $static_fire_sob_tc2_temperature;

	$: static_fire_system_state_display = $static_fire_system_state === undefined ? 'N/A' : $static_fire_system_state.replace('SYS_', '');

	$: static_fire_timer_period_display = $static_fire_timer_period === undefined ? 'N/A' : ($static_fire_timer_period / 1000).toFixed(0); // Convert to seconds
	$: static_fire_timer_remaining_display = $static_fire_timer_remaining === undefined ? 'N/A' : ($static_fire_timer_remaining / 1000).toFixed(0); // Convert to seconds

	$: static_fire_relayStatusOutdated = Date.now() - timestamps.relay_status > 5000;
	$: static_fire_combustionControlStatusOutdated = Date.now() - timestamps.static_fire_combustion_control_status > 5000;
	$: static_fire_rcuTempOutdated = Date.now() - timestamps.static_fire_rcu_temp > 5000;
	$: static_fire_batteryOutdated = Date.now() - timestamps.static_fire_battery > 5000;
	$: static_fire_launchRailLoadCellOutdated = Date.now() - timestamps.static_fire_launch_rail_load_cell > 5000;
	$: static_fire_nosLoadCellOutdated = Date.now() - timestamps.static_fire_nos_load_cell > 5000;
	$: static_fire_pbbPressureOutdated = Date.now() - timestamps.static_fire_pbb_pressure > 5000;
	$: static_fire_pbbTemperatureOutdated = Date.now() - timestamps.static_fire_pbb_temperature > 5000;
	$: static_fire_rcuPressureOutdated = Date.now() - timestamps.static_fire_rcu_pressure > 5000;
	$: static_fire_sobTemperatureOutdated = Date.now() - timestamps.static_fire_sob_temperature > 5000;
	$: static_fire_sysStateOutdated = Date.now() - timestamps.static_fire_sys_state > 5000;
	$: static_fire_heartbeatOutdated = Date.now() - timestamps.static_fire_heartbeat > 5000;

	const handleSliderChange = async (e: any, target: string, openCommand: string, closeCommand: string) => {
		e.preventDefault();

		// Determine the command based on the current value of the slider
		const command = e.target.checked ? openCommand : closeCommand;

		// Create a change on the 'RelayStatus' collection
		writeArbitraryCommand(target, command);
	}

	let wasLiveAtAnyPoint = false;

	const pollIgnitors = async () => {
		if (static_fire_box1_display === 'LIVE' || static_fire_box2_display === 'LIVE') {
			wasLiveAtAnyPoint = true;
		}
	}

	const handleLaunchSequence = async () => {
		await writeArbitraryCommand('NODE_RC', 'static_fire_RC_IGNITE_PAD_BOX1');
		await writeArbitraryCommand('NODE_RC', 'static_fire_RC_IGNITE_PAD_BOX2');

		const pollInterval = setInterval(pollIgnitors, 100);
		await new Promise(resolve => setTimeout(resolve, 3500));

		clearInterval(pollInterval);

		if (wasLiveAtAnyPoint) {
			for (let i = 0; i < 3; i++) {
				await writeStateChange('static_fire_RSC_IGNITION_TO_LAUNCH');
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
		await handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_IGNITE_PAD_BOX1', 'static_fire_RCU_KILL_BOX1');
		await handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_KILL_PAD_BOX2', 'static_fire_RCU_IGNITE_PAD_BOX2');
	}
</script>

<div class="container">
	<StaticFire/>

	<div class="static_fire_pbv1_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_pbv1_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_pbv1_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_PBV1', 'static_fire_RCU_CLOSE_PBV1')}
		>
			{static_fire_pbv1_display}
		</SlideToggle>
	</div>

	<div class="static_fire_pbv2_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_pbv2_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_pbv2_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_PBV2', 'static_fire_RCU_CLOSE_PBV2')}
		>
			{static_fire_pbv2_display}
		</SlideToggle>
	</div>

	<div class="static_fire_pbv3_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_pbv3_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_pbv3_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_PBV3', 'static_fire_RCU_CLOSE_PBV3')}
		>
			{static_fire_pbv3_display}
		</SlideToggle>
	</div>

	<div class="static_fire_pbv4_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_pbv4_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_pbv4_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_PBV4', 'static_fire_RCU_CLOSE_PBV4')}
		>
			{static_fire_pbv4_display}
		</SlideToggle>
	</div>
	
	<div class="static_fire_sol5_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_sol5_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_sol5_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_SOL5', 'static_fire_RCU_CLOSE_SOL5')}
		>
			{static_fire_sol5_display}
		</SlideToggle>
	</div>

	<div class="static_fire_sol6_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_sol6_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_sol6_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_SOL6', 'static_fire_RCU_CLOSE_SOL6')}
		>
			{static_fire_sol6_display}
		</SlideToggle>
	</div>

	<div class="static_fire_sol7_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_sol7_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_sol7_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_SOL7', 'static_fire_RCU_CLOSE_SOL7')}
		>
			{static_fire_sol7_display}
		</SlideToggle>
	</div>

	<div class="static_fire_sol8a_slider relay_status {static_fire_relayStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_sol8a_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_sol8a_open}
			on:click={(e) => handleSliderChange(e, 'NODE_RCU', 'static_fire_RCU_OPEN_SOL8A', 'static_fire_RCU_CLOSE_SOL8A')}
		>
			{static_fire_sol8a_display}
		</SlideToggle>
	</div>

	<div class="static_fire_drain_slider combustion_control_status {static_fire_combustionControlStatusOutdated ? 'outdated' : ''}">
		<SlideToggle
			name="static_fire_drain_slider"
			active="bg-primary-500 dark:bg-primary-500"
			size="sm"
			bind:checked={$static_fire_drain_open}
			on:click={(e) => handleSliderChange(e, 'NODE_DMB', 'static_fire_RSC_OPEN_DRAIN', 'static_fire_RSC_CLOSE_DRAIN')}
		>
			{static_fire_drain_display}
		</SlideToggle>
	</div>


	{#if $currentState === "static_fire_RS_IGNITION" || $currentState === "static_fire_RS_TEST" || $currentState === "static_fire_RS_ABORT" || $currentState === "static_fire_RS_LAUNCH" || $currentState === "static_fire_RS_BURN" || $currentState === "static_fire_RS_COAST" || $currentState === "static_fire_RS_RECOVERY"}
		<div class="static_fire_box1_slider">
			<SlideToggle
				name="static_fire_box1_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$static_fire_box1_on}
				on:click={handleIgnition}
				disabled={$currentState === "static_fire_RS_IGNITION" || $currentState === "static_fire_RS_ABORT" || $currentState === "static_fire_RS_LAUNCH" || $currentState === "static_fire_RS_BURN" || $currentState === "static_fire_RS_COAST" || $currentState === "static_fire_RS_RECOVERY"}
			>
				{static_fire_box1_display}
			</SlideToggle>
		</div>

		<div class="static_fire_box2_slider">
			<SlideToggle
				name="static_fire_box2_slider"
				active="bg-primary-500 dark:bg-primary-500"
				size="sm"
				bind:checked={$static_fire_box2_on}
				on:click={handleIgnition}
				disabled={$currentState === "static_fire_RS_IGNITION" || $currentState === "static_fire_RS_ABORT" || $currentState === "static_fire_RS_LAUNCH" || $currentState === "static_fire_RS_BURN" || $currentState === "static_fire_RS_COAST" || $currentState === "static_fire_RS_RECOVERY"}
			>
				{static_fire_box2_display}
			</SlideToggle>
		</div>
	{/if}

	<div class="static_fire_nos1_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("static_fire_NOS1")}
		>
			TARE
		</button>
	</div>

	<div class="static_fire_nos1_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => {
				writeLoadCellCommand("static_fire_NOS1", "CANCEL", 0);
				resumeConfirmRemoveWeight("static_fire_NOS1");}}
		>
			CAL
		</button>
	</div>

	<div class="static_fire_nos2_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("static_fire_NOS2")}
		>
			TARE
		</button>
	</div>

	<div class="static_fire_nos2_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => {
				writeLoadCellCommand("static_fire_NOS2", "CANCEL", 0);	
				resumeConfirmRemoveWeight("static_fire_NOS2");}}
		>
			CAL
		</button>
	</div>

	<div class="static_fire_rail_tare_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-secondary" 
			on:click={() => performTare("static_fire_LAUNCHRAIL")}
		>
			TARE
		</button>
	</div>

	<div class="static_fire_rail_cal_button">
		<button 
			type="button" 
			class="btn btn-sm variant-filled-error" 
			on:click={() => { 
				writeLoadCellCommand("static_fire_LAUNCHRAIL", "CANCEL", 0);
				resumeConfirmRemoveWeight("static_fire_LAUNCHRAIL");}}
		>
			CAL
		</button>
	</div>

	<div class="static_fire_rcu_tc1 rcu_temp {static_fire_rcuTempOutdated ? 'outdated' : ''}">
		<p>{static_fire_rcu_tc1_display}</p>
	</div>

	<div class="static_fire_rcu_tc2 rcu_temp {static_fire_rcuTempOutdated ? 'outdated' : ''}">
		<p>{static_fire_rcu_tc2_display}</p>
	</div>

	<div class="static_fire_nos1 nos_load_cell {static_fire_nosLoadCellOutdated ? 'outdated' : ''}">
		<p>{static_fire_nos1_mass_display}</p>
	</div>

	<div class="static_fire_nos2 nos_load_cell {static_fire_nosLoadCellOutdated ? 'outdated' : ''}">
		<p>{static_fire_nos2_mass_display}</p>
	</div>

	<div class="static_fire_pt1_pressure rcu_pressure {static_fire_rcuPressureOutdated ? 'outdated' : ''}">
		<p>{static_fire_pt1_pressure_display}</p>
	</div>

	<div class="static_fire_pt2_pressure rcu_pressure {static_fire_rcuPressureOutdated ? 'outdated' : ''}">
		<p>{static_fire_pt2_pressure_display}</p>
	</div>

	<div class="static_fire_pt3_pressure rcu_pressure {static_fire_rcuPressureOutdated ? 'outdated' : ''}">
		<p>{static_fire_pt3_pressure_display}</p>
	</div>

	<div class="static_fire_pt4_pressure rcu_pressure {static_fire_rcuPressureOutdated ? 'outdated' : ''}">
		<p>{static_fire_pt4_pressure_display}</p>
	</div>

	<div class="static_fire_mev_status combustion_control_status {static_fire_combustionControlStatusOutdated ? 'outdated' : ''}">
		<p>{static_fire_mev_display}</p>
	</div>

	<div class="static_fire_upper_pv_pressure">
		<p>{static_fire_upper_pv_display}</p>
	</div>

	<div class="static_fire_rocket_mass static_fire_launch_rail_load_cell {static_fire_launchRailLoadCellOutdated ? 'outdated' : ''}">
		<p>{static_fire_rocket_mass_display}</p>
	</div>

	<div class="static_fire_lower_pv_pressure static_fire_pbb_pressure {static_fire_pbbPressureOutdated ? 'outdated' : ''}">
		<p>{static_fire_lower_pv_display}</p>
	</div>

	<div class="static_fire_pv_temperature static_fire_pbb_temperature {static_fire_pbbTemperatureOutdated ? 'outdated' : ''}">
		<p>{static_fire_pv_temperature_display}</p>
	</div>

	<div class="static_fire_sob_tc1 static_fire_sob_temperature {static_fire_sobTemperatureOutdated ? 'outdated' : ''}">
		<p>{static_fire_sob_tc1_display}</p>
	</div>

	<div class="static_fire_sob_tc2 static_fire_sob_temperature {static_fire_sobTemperatureOutdated ? 'outdated' : ''}">
		<p>{static_fire_sob_tc2_display}</p>
	</div>

	<div class="static_fire_system_state static_fire_sys_state {static_fire_sysStateOutdated ? 'outdated' : ''}">
		<p>{static_fire_system_state_display}</p>
	</div>

	<div class="static_fire_timer_period static_fire_heartbeat {static_fire_heartbeatOutdated ? 'outdated' : ''}">
		<p>{static_fire_timer_period_display}</p>
	</div>

	<div class="static_fire_timer_remaining static_fire_heartbeat {static_fire_heartbeatOutdated ? 'outdated' : ''}">
		<p>{static_fire_timer_remaining_display}</p>
	</div>

	<!-- Render different buttons based on the current state -->
	{#if $currentState == "static_fire_RS_PRELAUNCH"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_FILL")}
		>
			Go to Fill
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("static_fire_RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "static_fire_RS_FILL"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_PRELAUNCH")}
		>
			Go to Pre-Launch
		</button>
		<button
			class="btn variant-filled-warning arm_button"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => instantStateChange("static_fire_RSC_ARM_CONFIRM_1")}
		>
			ARM CONFIRM 1
		</button>
		<button
			class="btn variant-filled-warning arm_button"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => instantStateChange("static_fire_RSC_ARM_CONFIRM_2")}
		>
			ARM CONFIRM 2
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_ARM")}
		>
			Go to Arm
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("static_fire_RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "static_fire_RS_ARM"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_FILL")}
		>
			Go to Fill
		</button>
		<button
			class="btn variant-filled-warning next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_IGNITION")}
		>
			Go to Ignition
		</button>
		<button
			class="btn variant-ghost-error next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("static_fire_RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "static_fire_RS_IGNITION"}
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
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_ARM")}
		>
			Go to Arm
		</button>
	{:else if $currentState == "static_fire_RS_ABORT"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_PRELAUNCH")}
		>
			Go to Pre-Launch
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => confirmStateChange("static_fire_RSC_GOTO_TEST")}
		>
			Go to Test
		</button>
	{:else if $currentState == "static_fire_RS_RECOVERY"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("static_fire_RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
	{:else if $currentState == "static_fire_RS_TEST"}
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.53);"
			on:click={() => instantStateChange("static_fire_RSC_ANY_TO_ABORT")}
		>
			Go to Abort
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.5);"
			on:click={() => instantStateChange("static_fire_RSC_TEST_MEV_OPEN")}
		>
			Open MEV
		</button>
		<button
			class="btn variant-filled-secondary next-state-btn"
			style="top: calc(var(--container-width) * 0.47);"
			on:click={() => instantStateChange("static_fire_RSC_MEV_CLOSE")}
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