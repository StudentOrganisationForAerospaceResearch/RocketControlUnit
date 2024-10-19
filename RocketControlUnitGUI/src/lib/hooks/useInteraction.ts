import { getModalStore, type ModalSettings } from '@skeletonlabs/skeleton';
import type { PocketbaseHook } from './usePocketbase';

const stateToCommand: { [key: string]: string } = {
	RS_ABORT: 'RSC_ANY_TO_ABORT',
	RS_PRELAUNCH: 'RSC_GOTO_PRELAUNCH',
	RS_FILL: 'RSC_GOTO_FILL',
	RS_ARM: 'RSC_GOTO_ARM',
	RS_IGNITION: 'RSC_GOTO_IGNITION',
	RS_LAUNCH: 'RSC_IGNITION_TO_LAUNCH',
	RS_BURN: 'RSC_GOTO_BURN',
	RS_COAST: 'RSC_GOTO_COAST',
	RS_DESCENT: 'RSC_GOTO_DESCENT',
	RS_RECOVERY: 'RSC_GOTO_RECOVERY',
	RS_TEST: 'RSC_GOTO_TEST'
};

const commandToState = Object.fromEntries(
	Object.entries(stateToCommand).map(([key, value]) => [value, key])
);

Object.freeze(stateToCommand);
Object.freeze(commandToState);

export const useInteraction = (pocketbaseHook: PocketbaseHook) => {
	const modalStore = getModalStore();

	let nextStatePending: string = '';

	const confirmStateChange = (state: string) => {
		nextStatePending = state;

		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: `Are you sure you wish to proceed to ${commandToState[state]}?`,
			response: (r: boolean) => {
				if (r) {
					pocketbaseHook.writeStateChange(nextStatePending);
				}

				nextStatePending = '';
			}
		};

		modalStore.trigger(modal);
	};

	const instantStateChange = (state: string) => {
		nextStatePending = state;
		pocketbaseHook.writeStateChange(nextStatePending);
		nextStatePending = '';
	};

	const confirmRemoveWeight = (loadcell: string) => {
		const modal: ModalSettings = {
			type: 'confirm',
			title: 'Remove All Weight',
			response: (r: boolean) => {
				if (r) {
					pocketbaseHook.writeLoadCellCommand(loadcell, 'CALIBRATE', 0);
					promptEnterNumberOfWeights(loadcell);
				} else {
					pocketbaseHook.writeLoadCellCommand(loadcell, 'CANCEL', 0);
				}
			}
		};

		modalStore.trigger(modal);
	};

	let numberOfWeights = 0;

	const promptEnterNumberOfWeights = (loadcell: string) => {
		const modal: ModalSettings = {
			type: 'prompt',
			title: 'Enter number of weights',
			valueAttr: { type: 'number', required: true },
			response: async (r: any) => {
				if (r) {
					// The modal was confirmed, set the number of weights
					numberOfWeights = parseInt(r);
					if (numberOfWeights > 0) {
						promptEnterWeight(loadcell);
					}
				}
			}
		};

		modalStore.trigger(modal);
	};

	const promptEnterWeight = (loadcell: string) => {
		const modal: ModalSettings = {
			type: 'prompt',
			title: `Enter Weight (kg) (${numberOfWeights} remaining)`,
			valueAttr: { type: 'text', required: true },
			response: async (r: any) => {
				if (r) {
					// If this is the last weight, send the finish command
					if (numberOfWeights === 1) {
						pocketbaseHook.writeLoadCellCommand(loadcell, 'FINISH', parseFloat(r));
					} else {
						// The modal was confirmed, send the calibrate command
						pocketbaseHook.writeLoadCellCommand(loadcell, 'CALIBRATE', parseFloat(r));
					}

					// Decrease the number of weights and open the modal again if there are more weights to enter
					numberOfWeights--;
					if (numberOfWeights > 0) {
						promptEnterWeight(loadcell);
					}
				} else {
					// The modal was cancelled, send a cancel command
					pocketbaseHook.writeLoadCellCommand(loadcell, 'CANCEL', 0);
				}
			}
		};

		modalStore.trigger(modal);
	};

	return {
		confirmStateChange,
		instantStateChange,
		confirmRemoveWeight
	};
};
