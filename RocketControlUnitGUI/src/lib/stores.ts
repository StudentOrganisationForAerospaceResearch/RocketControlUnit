import { writable, type Writable } from 'svelte/store';

export interface Stores {
	ac1_open: Writable<any>;
	pbv1_open: Writable<any>;
	pbv2_open: Writable<any>;
	pbv3_open: Writable<any>;
	pbv4_open: Writable<any>;
	sol5_open: Writable<any>;
	sol6_open: Writable<any>;
	sol7_open: Writable<any>;
	sol8a_open: Writable<any>;
	sol8b_open: Writable<any>;
	continuity1: Writable<any>;
	continuity2: Writable<any>;
	box1_on: Writable<any>;
	box2_on: Writable<any>;
	vent_open: Writable<any>;
	drain_open: Writable<any>;
	mev_open: Writable<any>;
	rcu_tc1_temperature: Writable<string | number | undefined>;
	rcu_tc2_temperature: Writable<string | number | undefined>;
	battery_voltage: Writable<any>;
	power_source: Writable<any>;
	upper_pv_pressure: Writable<string | number | undefined>;
	rocket_mass: Writable<any>;
	nos1_mass: Writable<any>;
	nos2_mass: Writable<any>;
	ib_pressure: Writable<string | number | undefined>;
	lower_pv_pressure: Writable<string | number | undefined>;
	pv_temperature: Writable<string | number | undefined>;
	pt1_pressure: Writable<string | number | undefined>;
	pt2_pressure: Writable<string | number | undefined>;
	pt3_pressure: Writable<string | number | undefined>;
	pt4_pressure: Writable<string | number | undefined>;
	sob_tc1_temperature: Writable<string | number | undefined>;
	sob_tc2_temperature: Writable<string | number | undefined>;
	system_state: Writable<string | undefined>;
	timer_state: Writable<string | undefined>;
	timer_period: Writable<number | undefined>;
	timer_remaining: Writable<number | undefined>;
}

export const initStores = () => {
	return {
		ac1_open: writable(undefined),
		pbv1_open: writable(undefined),
		pbv2_open: writable(undefined),
		pbv3_open: writable(undefined),
		pbv4_open: writable(undefined),
		sol5_open: writable(undefined),
		sol6_open: writable(undefined),
		sol7_open: writable(undefined),
		sol8a_open: writable(undefined),
		sol8b_open: writable(undefined),
		continuity1: writable(undefined),
		continuity2: writable(undefined),
		box1_on: writable(undefined),
		box2_on: writable(undefined),
		vent_open: writable(undefined),
		drain_open: writable(undefined),
		mev_open: writable(undefined),
		rcu_tc1_temperature: writable<string | number | undefined>(undefined),
		rcu_tc2_temperature: writable<string | number | undefined>(undefined),
		battery_voltage: writable(undefined),
		power_source: writable(undefined),
		upper_pv_pressure: writable<string | number | undefined>(undefined),
		rocket_mass: writable(undefined),
		nos1_mass: writable(undefined),
		nos2_mass: writable(undefined),
		ib_pressure: writable<string | number | undefined>(undefined),
		lower_pv_pressure: writable<string | number | undefined>(undefined),
		pv_temperature: writable<string | number | undefined>(undefined),
		pt1_pressure: writable<string | number | undefined>(undefined),
		pt2_pressure: writable<string | number | undefined>(undefined),
		pt3_pressure: writable<string | number | undefined>(undefined),
		pt4_pressure: writable<string | number | undefined>(undefined),
		sob_tc1_temperature: writable<string | number | undefined>(undefined),
		sob_tc2_temperature: writable<string | number | undefined>(undefined),
		system_state: writable<string | undefined>(undefined),
		timer_state: writable<string | undefined>(undefined),
		timer_period: writable<number | undefined>(undefined),
		timer_remaining: writable<number | undefined>(undefined)
	};
};
