import { writable } from 'svelte/store';

export const currentState = writable('N/A');

export const auth = writable(false);
