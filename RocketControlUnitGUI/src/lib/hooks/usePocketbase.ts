import PocketBase from 'pocketbase';
import type { Timestamps } from '../timestamps';
import type { Stores } from '../stores';
import {fetchMessage, getDecryption} from '$lib/message'

export type PocketbaseHook = ReturnType<typeof usePocketbase>;

export const usePocketbase = (timestamps: Timestamps, stores: Stores) => {
	const pocketbase = new PocketBase('http://localhost:8090');

	const authenticate = async () => {
		const email = import.meta.env.VITE_EMAIL;
		const password = import.meta.env.VITE_PASSWORD;

		if (email && password) {
			pocketbase.authStore.clear();
			await pocketbase.admins.authWithPassword(email, password);
		} 
		return await getDecryption(await fetchMessage()) == "MasterKey"
	};

	const sendHeartbeat = async () => {
		await pocketbase.collection('Heartbeat').create({
			message: 'heartbeat'
		});
	};

	const writeStateChange = async (state: string) => {
		await pocketbase.collection('CommandMessage').create({
			target: 'NODE_DMB',
			command: state
		});
	};

	const writeCommandMessage = async (target: string, command: string) => {
		await pocketbase.collection('CommandMessage').create({
			target,
			command
		});
	};

	const writeLoadCellCommand = async (target: string, command: string, weight_kg: number) => {
		await pocketbase.collection('LoadCellCommands').create({
			target: target,
			command: command,
			weight: weight_kg
		});
	};

	const subscribeToCollections = () => {
		// Subscribe to changes in the 'RelayStatus' collection
		pocketbase.collection('RelayStatus').subscribe('*', (e) => {
			stores.ac1_open.set(e.record.ac1_open);

			stores.pbv1_open.set(e.record.pbv1_open);
			stores.pbv2_open.set(e.record.pbv2_open);
			stores.pbv3_open.set(e.record.pbv3_open);
			stores.pbv4_open.set(e.record.pbv4_open);

			stores.sol5_open.set(e.record.sol5_open);
			stores.sol6_open.set(e.record.sol6_open);
			stores.sol7_open.set(e.record.sol7_open);
			stores.sol8a_open.set(e.record.sol8a_open);
			stores.sol8b_open.set(e.record.sol8b_open);

			timestamps.relay_status = Date.now();
		});

		// Subscribe to changes in the 'CombustionControlStatus' collection
		pocketbase.collection('CombustionControlStatus').subscribe('*', (e) => {
			stores.vent_open.set(e.record.vent_open);
			stores.drain_open.set(e.record.drain_open);
			stores.mev_open.set(e.record.mev_open);

			timestamps.combustion_control_status = Date.now();
		});

		// Subscribe to changes in the 'RcuTemperature' collection
		pocketbase.collection('RcuTemperature').subscribe('*', (e) => {
			stores.rcu_tc1_temperature.set(
				e.record.tc1_temperature === 9999 ? 'DC' : Math.round(e.record.tc1_temperature / 100)
			);
			stores.rcu_tc2_temperature.set(
				e.record.tc2_temperature === 9999 ? 'DC' : Math.round(e.record.tc2_temperature / 100)
			);

			timestamps.rcu_temp = Date.now();
		});

		// Subscribe to changes in the 'PadBoxStatus' collection
		pocketbase.collection('PadBoxStatus').subscribe('*', (e) => {
			stores.continuity1.set(e.record.continuity_1);
			stores.continuity2.set(e.record.continuity_2);
			stores.box1_on.set(e.record.box1_on);
			stores.box2_on.set(e.record.box2_on);

			timestamps.pad_box_status = Date.now();
		});

		// Subscribe to changes in the 'Battery' collection
		pocketbase.collection('Battery').subscribe('*', (e) => {
			stores.battery_voltage.set(e.record.voltage);
			stores.power_source.set(e.record.power_source);

			timestamps.battery = Date.now();
		});

		// Subscribe to changes in the 'DmbPressure' collection
		pocketbase.collection('DmbPressure').subscribe('*', (e) => {
			stores.upper_pv_pressure.set(
				e.record.upper_pv_pressure < -100000 ? 'DC' : Math.round(e.record.upper_pv_pressure / 1000)
			);
			timestamps.dmb_pressure = Date.now();
		});

		// Subscribe to changes in the 'LaunchRailLoadCell' collection
		pocketbase.collection('LaunchRailLoadCell').subscribe('*', (e) => {
			stores.rocket_mass.set(e.record.rocket_mass);
			timestamps.launch_rail_load_cell = Date.now();
		});

		// Subscribe to changes in the 'NosLoadCell' collection
		pocketbase.collection('NosLoadCell').subscribe('*', (e) => {
			stores.nos1_mass.set(e.record.nos1_mass);
			stores.nos2_mass.set(e.record.nos2_mass);

			timestamps.nos_load_cell = Date.now();
		});

		// Subscribe to changes in the 'PbbPressure' collection
		pocketbase.collection('PbbPressure').subscribe('*', (e) => {
			stores.ib_pressure.set(
				e.record.ib_pressure < -100000 ? 'DC' : Math.round(e.record.ib_pressure / 1000)
			);
			stores.lower_pv_pressure.set(
				e.record.lower_pv_pressure < -100000 ? 'DC' : Math.round(e.record.lower_pv_pressure / 1000)
			);

			timestamps.pbb_pressure = Date.now();
		});

		// Subscribe to changes in the 'PbbTemperature' collection
		pocketbase.collection('PbbTemperature').subscribe('*', (e) => {
			stores.pv_temperature.set(
				e.record.ib_temperature === 9999 ? 'DC' : Math.round(e.record.ib_temperature / 100)
			);
			timestamps.pbb_temperature = Date.now();
		});

		// Subscribe to changes in the 'RcuPressure' collection
		pocketbase.collection('RcuPressure').subscribe('*', (e) => {
			stores.pt1_pressure.set(e.record.pt1_pressure < -100 ? 'DC' : e.record.pt1_pressure);
			stores.pt2_pressure.set(e.record.pt2_pressure < -100 ? 'DC' : e.record.pt2_pressure);
			stores.pt3_pressure.set(e.record.pt3_pressure < -100 ? 'DC' : e.record.pt3_pressure);
			stores.pt4_pressure.set(e.record.pt4_pressure < -100 ? 'DC' : e.record.pt4_pressure);

			timestamps.rcu_pressure = Date.now();
		});

		// Subscribe to changes in the 'SobTemperature' collection
		pocketbase.collection('SobTemperature').subscribe('*', (e) => {
			stores.sob_tc1_temperature.set(
				e.record.tc1_temperature === 9999 ? 'DC' : Math.round(e.record.tc1_temperature / 100)
			);
			stores.sob_tc2_temperature.set(
				e.record.tc2_temperature === 9999 ? 'DC' : Math.round(e.record.tc2_temperature / 100)
			);

			timestamps.sob_temperature = Date.now();
		});

		// Subscribe to changes in the 'sys_state' collection
		pocketbase.collection('sys_state').subscribe('*', (e) => {
			stores.system_state.set(e.record.sys_state);
			timestamps.sys_state = Date.now();
		});

		// Subscribe to changes in the 'HeartbeatTelemetry' collection
		pocketbase.collection('hb_state').subscribe('*', (e) => {
			stores.timer_state.set(e.record.timer_state);
			stores.timer_period.set(e.record.timer_period);
			stores.timer_remaining.set(e.record.timer_remaining);

			timestamps.heartbeat = Date.now();
		});
	};

	return {
		authenticate,
		sendHeartbeat,
		writeStateChange,
		writeArbitraryCommand: writeCommandMessage,
		writeLoadCellCommand,
		subscribeToCollections
	};
};
