<script lang="ts">
	import '../app.postcss';
	import {
		AppShell,
		AppRail,
		AppRailAnchor,
		AppBar,
		initializeStores,
		LightSwitch,
		Modal,
		storePopup
	} from '@skeletonlabs/skeleton';
	import { computePosition, autoUpdate, flip, shift, offset, arrow } from '@floating-ui/dom';
	import { currentState } from '../store';
	import HomeIcon from '$lib/assets/rocket-dark.png';
	import AboutIcon from '$lib/assets/info-dark.png';
	import CameraIcon from '$lib/assets/camera-dark.png';
	import StatsIcon from '$lib/assets/stats-dark.png';
	storePopup.set({ computePosition, autoUpdate, flip, shift, offset, arrow });
	import { getDrawerStore } from '@skeletonlabs/skeleton';
	import { page } from '$app/stores';

	initializeStores();
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
	
	<svelte:fragment slot="sidebarLeft">
		<AppRail>
			<AppRailAnchor hover="bg-primary-hover-token" href="/" selected={$page.url.pathname === '/'}><img src={HomeIcon} class="sideBar-center" 
			alt="Icon" /></AppRailAnchor>
			
			<AppRailAnchor href="/data" selected={$page.url.pathname === "/data"}><img src={StatsIcon} class="sideBar-center" 
			alt="Icon" /></AppRailAnchor>
			
			<AppRailAnchor href="/live-feed" selected={$page.url.pathname === "/live-feed"}><img src={CameraIcon} class="sideBar-center" 
			alt="Icon" /></AppRailAnchor>
			
			<AppRailAnchor href="/about" selected={$page.url.pathname === "/about"}><img src={AboutIcon} class="sideBar-center" 
			alt="Icon" /></AppRailAnchor>
		</AppRail>
	</svelte:fragment>
	
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
	.thumb1 { 
		background: url(%sveltekit.assets%/favicon.png) 50% 50% no-repeat; /* 50% 50% centers image in div */
		width: 25px;
		height: 25px;
	}
</style>
