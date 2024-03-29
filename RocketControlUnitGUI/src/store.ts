import { writable } from 'svelte/store';

const states = {
    RS_PRELAUNCH: 'Pre-Launch',
    RS_FILL: 'Fill',
    RS_ARM: 'Arm',
    RS_IGNITION: 'Ignition',
    RS_LAUNCH: 'Launch',
    RS_BURN: 'Burn',
    RS_COAST: 'Coast',
    RS_DESCENT: 'Descent',
    RS_RECOVERY: 'Recovery',
    RS_ABORT: 'Abort',
    RS_TEST: 'Test'
};

export const currentState = writable(states.RS_ABORT);