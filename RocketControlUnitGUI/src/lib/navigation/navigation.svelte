<script>
	import { getDrawerStore } from '@skeletonlabs/skeleton';

	const drawerStore = getDrawerStore();

	function drawerClose() {
		drawerStore.close();
	}
</script>

<nav class="list-nav p-4">
	<ul>
		<div class="thumb1">
		</div>
		<li><img src=%sveltekit.assets%/favicon.png/></li>
		<li><a href="/" on:click={drawerClose}>Homepage</a></li>
		<li><a href="/about" on:click={drawerClose}>About</a></li>
		<li><a href="/blog" on:click={drawerClose}>Blog</a></li>
		<li><a href="/contact" on:click={drawerClose}>Contact</a></li>
	</ul>
</nav>

<style>
	.thumb1 { 
		background: url(%sveltekit.assets%/favicon.png) 50% 50% no-repeat; /* 50% 50% centers image in div */
		width: 25px;
		height: 25px;
	}
</style>