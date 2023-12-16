<script lang="ts">
	import '../app.postcss';
	import {
		AppShell,
		AppBar,
		initializeStores,
		LightSwitch,
		Modal
	} from '@skeletonlabs/skeleton';
	import type { ModalSettings, ModalComponent, ModalStore } from '@skeletonlabs/skeleton';
	import { AppRail, AppRailTile, AppRailAnchor } from '@skeletonlabs/skeleton';
	// Floating UI for Popups
	import { computePosition, autoUpdate, flip, shift, offset, arrow } from '@floating-ui/dom';
	import { storePopup } from '@skeletonlabs/skeleton';
	import HomeIcon from "$lib/assets/rocket-dark.png";
	import AboutIcon from "$lib/assets/info-dark.png";
	import CameraIcon from "$lib/assets/camera-dark.png";
	import StatsIcon from "$lib/assets/stats-dark.png";
	storePopup.set({ computePosition, autoUpdate, flip, shift, offset, arrow });

	import Navigation from '$lib/navigation/navigation.svelte';
	import type { HTMLAttributes } from 'svelte/elements';
	import { currentState } from '../store';
	initializeStores();

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

</script>

<Modal />

<!-- App Shell -->
<AppShell slotSidebarLeft="bg-surface-500/5 w-24">
	<svelte:fragment slot="header">
		<!-- App Bar -->
		<AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
			<svelte:fragment slot="lead">
				<div class="flex items-center">
					<div class="flex items-center">
						<img
							src="/Copy of Clear.png"
							alt="SOAR Logo"
							class="mr-2"
							style="width: 70px; height: 35px;"
						/>
					</div>
				</div>
			</svelte:fragment>

			<svelte:fragment>
				<h1 class="text-xl">Current Rocket State: {$currentState}</h1>
			</svelte:fragment>

			<svelte:fragment slot="trail">
				<LightSwitch class="ml-auto" />
			</svelte:fragment>
		</AppBar>
	</svelte:fragment>

<AppRail>
	<AppRailAnchor hover=bg-primary-hover-token href="/"><img src={HomeIcon} alt="background image" class="sideBar-center"/></AppRailAnchor>
	<AppRailAnchor href="/data"><img src={StatsIcon} alt="background image" class="sideBar-center"/></AppRailAnchor>
	<AppRailAnchor href="/live-feed"><img src={CameraIcon} alt="background image" class="sideBar-center"/></AppRailAnchor>
	<AppRailAnchor href="/about"><img src={AboutIcon} alt="background image" class="sideBar-center"/></AppRailAnchor>
</AppRail>


	<!-- Page Route Content -->
	<slot />
</AppShell>

<style>
.sideBar-center {
  display: block;
  margin-left: auto;
  margin-right: auto;
	width: 30%;
	height: width;
}
</style>