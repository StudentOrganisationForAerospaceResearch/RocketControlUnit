<script lang="ts">
	import HybridStaticFire2x from "./Hybrid Static Fire@2x.svelte";
</script>

<div class="container">
	<svelte:component this={HybridStaticFire2x} />
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