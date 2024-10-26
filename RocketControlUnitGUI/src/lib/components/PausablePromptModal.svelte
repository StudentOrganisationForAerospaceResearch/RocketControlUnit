<script lang="ts" context="module">
    export type PausablePromptResponse = ["submit" | "cancel" | "pause" | undefined, string];
</script>

<script lang="ts">
	import { getModalStore } from '@skeletonlabs/skeleton';

    const modalStore = getModalStore();

    export let heading: string = "";
    let inputValue: string = "";

    const finish = (value: PausablePromptResponse) => {
        $modalStore[0]?.response!(value);
        modalStore.close();
    }

    const submit = () => {
        finish(["submit", inputValue]);
    }

    const pause = () => {
        finish(["pause", inputValue]);
    }

    const cancel = () => {
        finish(["cancel", ""]);
    }
</script>

<div class="">
    <header>{heading}</header>
    <input bind:value={inputValue} type="text" />
    <div class="modal-actions">
        <button on:click={submit}>Submit</button>
        <button on:click={pause}>Pause</button>
        <button on:click={cancel}>Cancel</button>
    </div>
</div>