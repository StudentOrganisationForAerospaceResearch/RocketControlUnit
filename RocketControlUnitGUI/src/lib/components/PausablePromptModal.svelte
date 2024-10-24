<script lang="ts">
	import { getModalStore } from '@skeletonlabs/skeleton';

    const modalStore = getModalStore();

    export let heading: string = "";
    export let inputMethod: "text" | "number" = "text";

    const finish = (value: "submit" | "cancel" | "pause") => {
        $modalStore[0].response!(value);
    }

    const cancel = () => {
        modalStore.close();
        finish("cancel");
    }
</script>

<div class="">
    <header>{heading}</header>
    <input type={inputMethod} />
    <div class="modal-actions">
        <button on:click={() => finish("submit")}>Submit</button>
        <button on:click={() => finish("pause")}>Pause</button>
        <button on:click={cancel}>Cancel</button>
    </div>
</div>