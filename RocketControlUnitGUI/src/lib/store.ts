import PocketBase from 'pocketbase';
import { writable } from 'svelte/store';
import type { Writable } from 'svelte/store';

export const currentState = writable("N/A");

export const PB = new PocketBase('http://127.0.0.1:8090');

export const ac1_open = writable(undefined);
export const ac2_open = writable(undefined);

export const pbv1_open = writable(undefined);
export const pbv2_open = writable(undefined);
export const pbv3_open = writable(undefined);
export const pbv4_open = writable(undefined);

export const sol5_open = writable(undefined);
export const sol6_open = writable(undefined);
export const sol7_open = writable(undefined);
export const sol8a_open = writable(undefined);
export const sol8b_open = writable(undefined);

export const continuity1 = writable(undefined);
export const continuity2 = writable(undefined);
export const box1_on = writable(undefined);
export const box2_on = writable(undefined);

export const vent_open = writable(undefined);
export const drain_open = writable(undefined);
export const mev_open = writable(undefined);

export const rcu_tc1_temperature: Writable<string | number | undefined> = writable(undefined);
export const rcu_tc2_temperature: Writable<string | number | undefined> = writable(undefined);

export const battery_voltage = writable(undefined);
export const power_source = writable(undefined);

export const upper_pv_pressure: Writable<string | number | undefined> = writable(undefined);

export const rocket_mass = writable(undefined);

export const nos1_mass = writable(undefined);
export const nos2_mass = writable(undefined);

export const ib_pressure: Writable<string | number | undefined> = writable(undefined);
export const lower_pv_pressure: Writable<string | number | undefined> = writable(undefined);

export const pv_temperature: Writable<string | number | undefined> = writable(undefined);

export const pt1_pressure: Writable<string | number | undefined> = writable(undefined);
export const pt2_pressure: Writable<string | number | undefined> = writable(undefined);
export const pt3_pressure: Writable<string | number | undefined> = writable(undefined);
export const pt4_pressure: Writable<string | number | undefined> = writable(undefined);

export const sob_tc1_temperature: Writable<string | number | undefined> = writable(undefined);
export const sob_tc2_temperature: Writable<string | number | undefined> = writable(undefined);

let subscriptions_started = false;

export async function start_subscriptions() {
    if (subscriptions_started) {
        return;
    }


    PB.collection('RelayStatus').subscribe('*', function (e) {
        ac1_open.set(e.record.ac1_open);
        ac2_open.set(e.record.ac2_open);

        pbv1_open.set(e.record.pbv1_open);
        pbv2_open.set(e.record.pbv2_open);
        pbv3_open.set(e.record.pbv3_open);
        pbv4_open.set(e.record.pbv4_open);

        sol5_open.set(e.record.sol5_open);
        sol6_open.set(e.record.sol6_open);
        sol7_open.set(e.record.sol7_open);
        sol8a_open.set(e.record.sol8a_open);
        sol8b_open.set(e.record.sol8b_open);
    });

    // Subscribe to changes in the 'CombustionControlStatus' collection
    PB.collection('CombustionControlStatus').subscribe('*', function (e) {
        // Update the CombustionControlStatus data store whenever a change is detected
        vent_open.set(e.record.vent_open);
        drain_open.set(e.record.drain_open);
        mev_open.set(e.record.mev_open);
    });

    // Subscribe to changes in the 'RcuTemp' collection
    PB.collection('RcuTemperature').subscribe('*', function (e) {
        // Update the RcuTemp data store whenever a change is detected
        if(e.record.tc1_temperature == 9999) {
            rcu_tc1_temperature.set('DC');
        }
        else {
            rcu_tc1_temperature.set(Math.round(e.record.tc1_temperature/100));
        }

        if(e.record.tc2_temperature == 9999) {
            rcu_tc2_temperature.set('DC');
        }
        else {
            rcu_tc2_temperature.set(Math.round(e.record.tc2_temperature/100));
        }
    });

    // Subscribe to changes in the 'PadBoxStatus' collection
    PB.collection('PadBoxStatus').subscribe('*', function (e) {
        // Update the PadBoxStatus data store whenever a change is detected
        continuity1.set(e.record.continuity_1);
        continuity2.set(e.record.continuity_2);
        box1_on.set(e.record.box1_on);
        box2_on.set(e.record.box2_on);
    });

    // Subscribe to changes in the 'Battery' collection
    PB.collection('Battery').subscribe('*', function (e) {
        // Update the Battery data store whenever a change is detected
        battery_voltage.set(e.record.voltage);
        power_source.set(e.record.power_source);
    });

    // Subscribe to changes in the 'DmbPressure' collection
    PB.collection('DmbPressure').subscribe('*', function (e) {
        // Update the DmbPressure data store whenever a change is detected
        if (e.record.upper_pv_pressure < -100000) {
            upper_pv_pressure.set('DC');
        }
        else {
            upper_pv_pressure.set(Math.round(e.record.upper_pv_pressure/1000));
        }
    });

    // Subscribe to changes in the 'LaunchRailLoadCell' collection
    PB.collection('LaunchRailLoadCell').subscribe('*', function (e) {
        // Update the LaunchRailLoadCell data store whenever a change is detected
        rocket_mass.set(e.record.rocket_mass);
    });

    // Subscribe to changes in the 'NosLoadCell' collection
    PB.collection('NosLoadCell').subscribe('*', function (e) {
        // Update the NosLoadCell data store whenever a change is detected
        nos1_mass.set(e.record.nos1_mass);
        nos2_mass.set(e.record.nos2_mass);
    });

    // Subscribe to changes in the 'PbbPressure' collection
    PB.collection('PbbPressure').subscribe('*', function (e) {
        console.log("__________________")
        console.log(e.record.ib_pressure)
        // Update the PbbPressure data store whenever a change is detected
        if (e.record.ib_pressure < -100000) {
            ib_pressure.set('DC');
        }
        else {
            ib_pressure.set(Math.round(e.record.ib_pressure/1000));
        }
        if (e.record.lower_pv_pressure < -100000) {
            lower_pv_pressure.set('DC');
        }
        else {
            lower_pv_pressure.set(Math.round(e.record.lower_pv_pressure/1000));
        }
        console.log(Math.round(e.record.lower_pv_pressure/1000));
        console.log(lower_pv_pressure)
    });

    // Subscribe to changes in the 'PbbTemperature' collection
    PB.collection('PbbTemperature').subscribe('*', function (e) {
        // Update the PbbTemperature data store whenever a change is detected
        if(e.record.ib_temperature == 9999) {
            pv_temperature.set('DC');
        }
        else {
            pv_temperature.set(Math.round(e.record.ib_temperature/100));
        }
    });

    // Subscribe to changes in the 'RcuPressure' collection
    PB.collection('RcuPressure').subscribe('*', function (e) {
        // Update the RcuPressure data store whenever a change is detected
        if(e.record.pt1_pressure <-100) {
            pt1_pressure.set('DC');
        }
        else {
            pt1_pressure.set(e.record.pt1_pressure);
        }
        if(e.record.pt2_pressure <-100) {
            pt2_pressure.set('DC');
        }
        else {
            pt2_pressure.set(e.record.pt2_pressure);
        }
        if(e.record.pt3_pressure <-100) {
            pt3_pressure.set('DC');
        }
        else {
            pt3_pressure.set(e.record.pt3_pressure);
        }
        if(e.record.pt4_pressure <-100) {
            pt4_pressure.set('DC');
        }
        else {
            pt4_pressure.set(e.record.pt4_pressure);
        }
    });

    // Subscribe to changes in the 'SobTemperature' collection
    PB.collection('SobTemperature').subscribe('*', function (e) {
        // Update the SobTemperature data store whenever a change is detected
        if(e.record.tc1_temperature == 9999) {
            sob_tc1_temperature.set('DC');
        }
        else {
            sob_tc1_temperature.set(Math.round(e.record.tc1_temperature/100));
        }

        if(e.record.tc2_temperature == 9999) {
            sob_tc2_temperature.set('DC');
        }
        else {
            sob_tc2_temperature.set(Math.round(e.record.tc2_temperature/100));
        }
    });

    // Subscribe to changes in the 'sys_state' collection
    PB.collection('sys_state').subscribe('*', function (e) {
        // Update the SystemState data store whenever a change is detected
        currentState.set(e.record.rocket_state);
    });

    subscriptions_started = true;
}