<script lang="ts">
	import '../app.postcss';
	import {
		AppShell,
		AppBar,
		initializeStores,
		Drawer,
		getDrawerStore,
		LightSwitch,
		Modal
	} from '@skeletonlabs/skeleton';
	// Floating UI for Popups
	import { computePosition, autoUpdate, flip, shift, offset, arrow } from '@floating-ui/dom';
	import { storePopup } from '@skeletonlabs/skeleton';

	storePopup.set({ computePosition, autoUpdate, flip, shift, offset, arrow });

	import Navigation from '$lib/navigation/navigation.svelte';
	import { currentState } from '../store';
	initializeStores();

	const drawerStore = getDrawerStore();

	function drawerOpen(): void {
		drawerStore.open({});
	}
</script>

<Drawer>
	<Navigation />
</Drawer>

<Modal />

<!-- App Shell -->
<AppShell slotSidebarLeft="bg-surface-500/5 w-0 lg:w-64">
	<svelte:fragment slot="header">
		<!-- App Bar -->
		<AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
			<svelte:fragment slot="lead">
				<div class="flex items-center">
					<button class="lg:hidden btn btn-sm mr-4" on:click={drawerOpen}>
						<span>
							<svg viewBox="0 0 100 80" class="fill-token w-4 h-4">
								<rect width="100" height="20" />
								<rect y="30" width="100" height="20" />
								<rect y="60" width="100" height="20" />
							</svg>
						</span>
					</button>

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
		<Navigation />
	</svelte:fragment>
	<!-- Page Route Content -->
	<slot />
</AppShell>
