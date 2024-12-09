<script lang="ts">
	import '../styles/app.postcss';
	import ReadOnlySvg from '$lib/components/ReadOnlySvg.svelte';
	import { ThemeData, ThemeType } from '$lib/theme';
	import { auth, currentState } from "$lib/stores";
	import { computePosition, autoUpdate, flip, shift, offset, arrow } from '@floating-ui/dom';
	import { page } from '$app/stores';
	import {
		AppShell,
		AppRail,
		AppRailAnchor,
		AppBar,
		initializeStores,
		LightSwitch,
		Modal,
		storePopup,
		modeCurrent
	} from '@skeletonlabs/skeleton';

	storePopup.set({ computePosition, autoUpdate, flip, shift, offset, arrow });
	initializeStores();

	$: themeData = new ThemeData($modeCurrent ? ThemeType.LIGHT : ThemeType.DARK);
</script>

<Modal />

<!-- App Shell -->
<AppShell slotSidebarLeft="bg-surface-500/5">
	<svelte:fragment slot="header">
		<!-- App Bar -->
		<AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
			<svelte:fragment slot="lead">
				<div class="flex items-center">
					<div class="flex items-center">
						<img
							src={themeData.logoSrc}
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
				{#if $auth === false}
					<ReadOnlySvg />
				{/if}
			</svelte:fragment>
		</AppBar>
	</svelte:fragment>
	
	<svelte:fragment slot="sidebarLeft">
		<AppRail>
			<AppRailAnchor hover="bg-primary-hover-token" href="/" selected={$page.url.pathname === '/'}>
				<img src="/icons/rocket.png" class="sideBar-center" alt="Icon" />
			</AppRailAnchor>
			
			<AppRailAnchor href="/data" selected={$page.url.pathname === "/data"}>
				<img src="/icons/stats.png" class="sideBar-center" alt="Icon" />
			</AppRailAnchor>
			
			<AppRailAnchor href="/live-feed" selected={$page.url.pathname === "/live-feed"}>
				<img src="/icons/camera.png" class="sideBar-center" alt="Icon" />
			</AppRailAnchor>
			
			<AppRailAnchor href="/about" selected={$page.url.pathname === "/about"}>
				<img src="/icons/info.png" class="sideBar-center" alt="Icon" />
			</AppRailAnchor>
		</AppRail>
	</svelte:fragment>
	
	<slot>Some Slot</slot>
</AppShell>

<style>
	.sideBar-center {
		filter: var(--icon-filter);
		transition: filter 0.15s ease;
		display: block;
		margin-left: auto;
		margin-right: auto;
		width: 30%;
		height: width;
	}
</style>