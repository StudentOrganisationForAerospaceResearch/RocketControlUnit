<script lang="ts">
  export let fieldNames: string[] = [];
  export let fieldTexts: (string|number)[] = [];
</script>

<style>
  .grid-container {
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    gap: 10px;
    margin-left: 0px;
  }
  .field-text {
    font-size: 1.5em;
  }
  .field-container {
    display: flex;
    align-items: center;
  }
  .label-text {
    font-size: 0.8em;
    width: 100px;
    white-space: normal;
  }
  .text-container {
    flex-grow: 1;
    display: flex;
    justify-content: center;
    margin-left: -100px;
    margin-top: 15px;
    margin-bottom: -1px;
  }
</style>

<div class="flex-auto px-3.5 pt-0 pb-5 rounded-2xl border border-solid border-zinc-300 max-md:pr-5 max-md:max-w-full grid-container">
  {#each fieldNames as fieldName, index}
    <div class="field-container">
      <label for={'field' + (index + 1)} class="label-text">{fieldName}</label>
      <div class="text-container">
        <p id={'field' + (index + 1)} class="field-text">{fieldTexts[index]}</p>
      </div>
    </div>
  {/each}
</div>