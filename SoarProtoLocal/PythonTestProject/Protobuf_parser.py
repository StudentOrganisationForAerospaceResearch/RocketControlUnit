#Telemetry_parser.py

import json
import SoarLib.ControlMessage_pb2 as Proto
import SoarLib.CommandMessage_pb2 as ProtoCmd
import SoarLib.TelemetryMessage_pb2 as ProtoTele
import SoarLib.CoreProto_pb2 as ProtoCore
import Telemetry_Objects as TelO
import TelemetryLogger as TeleLog

PROTO_STATE_TO_STRING = {
ProtoCore.RS_ABORT : 'RS_ABORT',
ProtoCore.RS_ARM : 'RS_ARM',
ProtoCore.RS_BURN : 'RS_BURN',
ProtoCore.RS_COAST : 'RS_COAST',
ProtoCore.RS_DESCENT : 'RS_DESCENT',
ProtoCore.RS_FILL : 'RS_FILL',
ProtoCore.RS_IGNITION : 'RS_IGNITION',
ProtoCore.RS_LAUNCH : 'RS_LAUNCH',
ProtoCore.RS_NONE : 'RS_NONE',
ProtoCore.RS_PRELAUNCH : 'RS_PRELAUNCH',
ProtoCore.RS_RECOVERY : 'RS_RECOVERY',
ProtoCore.RS_TEST : 'RS_TEST'
}

STRING_TO_RSC_PROTO_COMMAND = {
	"RSC_ANY_TO_ABORT": ProtoCmd.DMBCommand.RSC_ANY_TO_ABORT,
	"RSC_ARM_CONFIRM_1": ProtoCmd.DMBCommand.RSC_ARM_CONFIRM_1,
	"RSC_ARM_CONFIRM_2": ProtoCmd.DMBCommand.RSC_ARM_CONFIRM_2,
	"RSC_BURN_TO_COAST": ProtoCmd.DMBCommand.RSC_BURN_TO_COAST,
	"RSC_CLOSE_DRAIN": ProtoCmd.DMBCommand.RSC_CLOSE_DRAIN,
	"RSC_CLOSE_VENT": ProtoCmd.DMBCommand.RSC_CLOSE_VENT,
	"RSC_COAST_TO_DESCENT": ProtoCmd.DMBCommand.RSC_COAST_TO_DESCENT,
	"RSC_DESCENT_TO_RECOVERY": ProtoCmd.DMBCommand.RSC_DESCENT_TO_RECOVERY,
	"RSC_FIRST_INVALID": ProtoCmd.DMBCommand.RSC_FIRST_INVALID,
	"RSC_GOTO_ARM": ProtoCmd.DMBCommand.RSC_GOTO_ARM,
	"RSC_GOTO_FILL": ProtoCmd.DMBCommand.RSC_GOTO_FILL,
	"RSC_GOTO_IGNITION": ProtoCmd.DMBCommand.RSC_GOTO_IGNITION,
	"RSC_GOTO_PRELAUNCH": ProtoCmd.DMBCommand.RSC_GOTO_PRELAUNCH,
	"RSC_IGNITION_TO_LAUNCH": ProtoCmd.DMBCommand.RSC_IGNITION_TO_LAUNCH,
	"RSC_LAUNCH_TO_BURN": ProtoCmd.DMBCommand.RSC_LAUNCH_TO_BURN,
    "RSC_TEST_MEV_OPEN": ProtoCmd.DMBCommand.RSC_TEST_MEV_OPEN, 
	"RSC_MEV_CLOSE": ProtoCmd.DMBCommand.RSC_MEV_CLOSE,
	"RSC_OPEN_DRAIN": ProtoCmd.DMBCommand.RSC_OPEN_DRAIN,
	"RSC_OPEN_VENT": ProtoCmd.DMBCommand.RSC_OPEN_VENT,
	"RSC_POWER_TRANSITION_EXTERNAL": ProtoCmd.DMBCommand.RSC_POWER_TRANSITION_EXTERNAL,
	"RSC_POWER_TRANSITION_ONBOARD": ProtoCmd.DMBCommand.RSC_POWER_TRANSITION_ONBOARD,
    "RSC_GOTO_TEST" : ProtoCmd.DMBCommand.RSC_GOTO_TEST,
    "RSC_TEST_MEV_ENABLE": ProtoCmd.DMBCommand.RSC_TEST_MEV_ENABLE,
    "RSC_TEST_MEV_DISABLE": ProtoCmd.DMBCommand.RSC_TEST_MEV_DISABLE,
	"RSC_NONE" : ProtoCmd.DMBCommand.RSC_NONE
}

STRING_TO_PBB_PROTO_COMMAND = {
	"PBB_NONE": ProtoCmd.PBBCommand.PBB_NONE,
	"PBB_OPEN_MEV": ProtoCmd.PBBCommand.PBB_OPEN_MEV,
	"PBB_CLOSE_MEV": ProtoCmd.PBBCommand.PBB_CLOSE_MEV,
    "PMB_LAST": ProtoCmd.PBBCommand.PMB_LAST,
}

STRING_TO_RCU_PROTO_COMMAND = {
	"RCU_NONE": ProtoCmd.RCUCommand.RCU_NONE,
	"RCU_OPEN_AC1": ProtoCmd.RCUCommand.RCU_OPEN_AC1,     # shed ac
    "RCU_CLOSE_AC1": ProtoCmd.RCUCommand.RCU_CLOSE_AC1,   # shed ac
	"RCU_OPEN_AC2": ProtoCmd.RCUCommand.RCU_OPEN_AC2,
    "RCU_CLOSE_AC2": ProtoCmd.RCUCommand.RCU_CLOSE_AC2,
    "RCU_OPEN_PBV1": ProtoCmd.RCUCommand.RCU_OPEN_PBV1,
	"RCU_CLOSE_PBV1": ProtoCmd.RCUCommand.RCU_CLOSE_PBV1,
    "RCU_OPEN_PBV2": ProtoCmd.RCUCommand.RCU_OPEN_PBV2,
    "RCU_CLOSE_PBV2": ProtoCmd.RCUCommand.RCU_CLOSE_PBV2,
	"RCU_OPEN_PBV3": ProtoCmd.RCUCommand.RCU_OPEN_PBV3,
    "RCU_CLOSE_PBV3": ProtoCmd.RCUCommand.RCU_CLOSE_PBV3,
    "RCU_OPEN_SOL1": ProtoCmd.RCUCommand.RCU_OPEN_SOL1,
    "RCU_CLOSE_SOL1": ProtoCmd.RCUCommand.RCU_CLOSE_SOL1,
    "RCU_OPEN_SOL2": ProtoCmd.RCUCommand.RCU_OPEN_SOL2,
    "RCU_CLOSE_SOL2": ProtoCmd.RCUCommand.RCU_CLOSE_SOL2,
    "RCU_CLOSE_SOL3": ProtoCmd.RCUCommand.RCU_CLOSE_SOL3,
    "RCU_OPEN_SOL4": ProtoCmd.RCUCommand.RCU_OPEN_SOL4,
    "RCU_CLOSE_SOL4": ProtoCmd.RCUCommand.RCU_CLOSE_SOL4,
    "RCU_OPEN_SOL5": ProtoCmd.RCUCommand.RCU_OPEN_SOL5,
    "RCU_CLOSE_SOL5": ProtoCmd.RCUCommand.RCU_CLOSE_SOL5,
    "RCU_OPEN_SOL6": ProtoCmd.RCUCommand.RCU_OPEN_SOL6,
    "RCU_CLOSE_SOL6": ProtoCmd.RCUCommand.RCU_CLOSE_SOL6,
    "RCU_OPEN_SOL7": ProtoCmd.RCUCommand.RCU_OPEN_SOL7,
    "RCU_CLOSE_SOL7": ProtoCmd.RCUCommand.RCU_CLOSE_SOL7,
    "RCU_OPEN_SOL8A": ProtoCmd.RCUCommand.RCU_OPEN_SOL8A,
    "RCU_CLOSE_SOL8A": ProtoCmd.RCUCommand.RCU_CLOSE_SOL8A,
    "RCU_OPEN_SOL8B": ProtoCmd.RCUCommand.RCU_OPEN_SOL8B,
    "RCU_CLOSE_SOL8B": ProtoCmd.RCUCommand.RCU_CLOSE_SOL8B,
    "RCU_IGNITE_PAD_BOX1": ProtoCmd.RCUCommand.RCU_IGNITE_PAD_BOX1,
    "RCU_IGNITE_PAD_BOX2": ProtoCmd.RCUCommand.RCU_IGNITE_PAD_BOX2,
    "RCU_KILL_PAD_BOX1": ProtoCmd.RCUCommand.RCU_KILL_PAD_BOX1,
    "RCU_KILL_PAD_BOX2": ProtoCmd.RCUCommand.RCU_KILL_PAD_BOX2,
    "RCU_LAST": ProtoCmd.RCUCommand.RCU_LAST
}

STRING_TO_SOB_PROTO_COMMAND = {
	"SOB_NONE": ProtoCmd.SOBCommand.SOB_NONE,
	"SOB_SLOW_SAMPLE_IR": ProtoCmd.SOBCommand.SOB_SLOW_SAMPLE_IR,
	"SOB_FAST_SAMPLE_IR": ProtoCmd.SOBCommand.SOB_FAST_SAMPLE_IR,
	"SOB_LAST": ProtoCmd.SOBCommand.SOB_LAST
}

STRING_TO_PI_COMMAND = {
    "RCU_TARE_NOS1_LOAD_CELL": "TARE_NOS1",
    "RCU_TARE_NOS2_LOAD_CELL": "TARE_NOS2",
    "RCU_CAL_NOS1_LOAD_CELL": "CAL_NOS1",
    "RCU_CAL_NOS2_LOAD_CELL": "CAL_NOS2",
    "SOB_TARE_LOAD_CELL": "TARE_NOS3",
    "SOB_CALIBRATE_LOAD_CELL": "CAL_NOS3"
}

def tare_nos1(value):
    TelO.tele_rcu_obj.nos1_tare = True

def tare_nos2(value):
    TelO.tele_rcu_obj.nos2_tare = True

def cal_nos1(value):
    TelO.tele_rcu_obj.nos1_calibrate = True
    TelO.tele_rcu_obj.nos1_calibration_value = value

def cal_nos2(value):
    TelO.tele_rcu_obj.nos2_calibrate = True
    TelO.tele_rcu_obj.nos2_calibration_value = value

def tare_nos3(value):
    TelO.tele_sob_obj.nos3_tare = True

def cal_nos3(value):
    TelO.tele_sob_obj.nos3_calibrate = True
    TelO.tele_sob_obj.nos3_calibration_value = value

STRING_TO_PI_COMMAND_FUNCTION = {
    "TARE_NOS1": tare_nos1,
    "TARE_NOS2": tare_nos2,
    "CAL_NOS1": cal_nos1,
    "CAL_NOS2": cal_nos2,
    "TARE_NOS3": tare_nos3,
    "CAL_NOS3": cal_nos3,
}

ALLOWED_COMMANDS_FROM_STATE = {
    'RS_ABORT': ["RSC_ANY_TO_ABORT", "RSC_GOTO_PRELAUNCH", "RSC_CLOSE_DRAIN", "RSC_OPEN_DRAIN", "RSC_CLOSE_VENT", "RSC_OPEN_VENT", "RSC_POWER_TRANSITION_ONBOARD", "RSC_POWER_TRANSITION_EXTERNAL", "RSC_GOTO_TEST"],
    'RS_ARM': ["RSC_ANY_TO_ABORT", "RSC_POWER_TRANSITION_ONBOARD", "RSC_POWER_TRANSITION_EXTERNAL", "RSC_GOTO_FILL", "RSC_GOTO_IGNITION", "RSC_OPEN_VENT", "RSC_CLOSE_VENT", "RSC_OPEN_DRAIN", "RSC_CLOSE_DRAIN", "RSC_MEV_CLOSE"],
    'RS_BURN': ["RSC_GOTO_PRELAUNCH"],
    'RS_COAST': ["RSC_GOTO_PRELAUNCH"],
    'RS_DESCENT': ["RSC_GOTO_PRELAUNCH"],
    'RS_FILL': ["RSC_ANY_TO_ABORT", "RSC_ARM_CONFIRM_1", "RSC_ARM_CONFIRM_2", "RSC_GOTO_ARM", "RSC_GOTO_PRELAUNCH", "RSC_OPEN_VENT", "RSC_CLOSE_VENT", "RSC_OPEN_DRAIN", "RSC_CLOSE_DRAIN", "RSC_MEV_CLOSE", "RSC_POWER_TRANSITION_ONBOARD", "RSC_POWER_TRANSITION_EXTERNAL"],
    'RS_IGNITION': ["RSC_IGNITION_TO_LAUNCH", "RSC_GOTO_ARM", "RSC_GOTO_PRELAUNCH"],
    'RS_LAUNCH': ["RSC_GOTO_PRELAUNCH"],
    'RS_NONE': ["RSC_ANY_TO_ABORT"],
    'RS_PRELAUNCH': ["RSC_ANY_TO_ABORT", "RSC_GOTO_FILL", "RSC_OPEN_VENT", "RSC_CLOSE_VENT", "RSC_OPEN_DRAIN", "RSC_CLOSE_DRAIN", "RSC_MEV_CLOSE", "RSC_CLOSE_DRAIN", "RSC_OPEN_DRAIN", "RSC_CLOSE_VENT", "RSC_OPEN_VENT", "RSC_POWER_TRANSITION_ONBOARD", "RSC_POWER_TRANSITION_EXTERNAL", "RSC_GOTO_TEST"],
    'RS_RECOVERY': ["RSC_ANY_TO_ABORT", "RSC_OPEN_VENT", "RSC_CLOSE_VENT", "RSC_OPEN_DRAIN", "RSC_CLOSE_DRAIN", "RSC_MEV_CLOSE", "RSC_POWER_TRANSITION_ONBOARD", "RSC_POWER_TRANSITION_EXTERNAL"],
    'RS_TEST': ["RSC_ANY_TO_ABORT","RSC_OPEN_VENT", "RSC_CLOSE_VENT", "RSC_OPEN_DRAIN", "RSC_CLOSE_DRAIN", "RSC_POWER_TRANSITION_EXTERNAL", "RSC_POWER_TRANSITION_ONBOARD", "RSC_GOTO_PRELAUNCH", "RSC_TEST_MEV_OPEN", "RSC_MEV_CLOSE", "RSC_TEST_MEV_ENABLE", "RSC_TEST_MEV_DISABLE"]
}

PROTOBUF_TO_POWER_SOURCE = {
    ProtoTele.Battery.GROUND: "GROUND",
    ProtoTele.Battery.ROCKET: "ROCKET",
    ProtoTele.Battery.INVALID: "INVALID"
}

def coord_parse_json_send(msg):
    dmb_jsonStr_gps = json.dumps(TelO.tele_dmb_obj.tele_gps(msg.coord.latitude.minutes, msg.coord.latitude.degrees,
                                                            msg.coord.longitude.minutes, msg.coord.longitude.degrees,
                                                            msg.coord.antenna_alt.altitude, msg.coord.antenna_alt.unit,
                                                            msg.coord.geoidAltitude.altitude, msg.coord.geoidAltitude.unit,
                                                            msg.coord.total_alt.altitude, msg.coord.total_alt.unit,
                                                            msg.coord.time))
    return "TELE_DMB_GPS", dmb_jsonStr_gps

def baro_parse_json_send(msg):
    dmb_jsonStr_baro = json.dumps(TelO.tele_dmb_obj.tele_baro(msg.baro.baro_pressure, msg.baro.baro_temp))
    TeleLog.TelemetryLogger("DmbBaroValues.txt", dmb_jsonStr_baro)
    return "TELE_DMB_BARO", dmb_jsonStr_baro

def imu_parse_json_send(msg):
    accel = [msg.imu.accelx, msg.imu.accely, msg.imu.accelz]
    gyro = [msg.imu.gyrox, msg.imu.gyroy, msg.imu.gyroz]
    magn = [msg.imu.magx, msg.imu.magy, msg.imu.magz]
    dmb_jsonStr_imu = json.dumps(TelO.tele_dmb_obj.tele_imu(accel, gyro, magn))
    return "TELE_DMB_IMU", dmb_jsonStr_imu

def bat_parse_json_send(msg):
    dmb_jsonStr_battery = json.dumps(TelO.tele_dmb_obj.tele_battery(msg.bat.p_source, msg.bat.volt))
    return "TELE_DMB_BATTERY", dmb_jsonStr_battery

def flash_parse_json_send(msg):
    dmb_jsonStr_flash = json.dumps(TelO.tele_dmb_obj.tele_flash(msg.flash.sector_address, msg.flash.logging_rate))
    return "TELE_DMB_FLASH", dmb_jsonStr_flash

def pressdmb_parse_json_send(msg):
    adj_upper_pv_press = 1.0152 * msg.pressdmb.upper_pv_pressure + 4.935
    #dmb_jsonStr_pressure = json.dumps(TelO.tele_dmb_obj.tele_pressure(msg.pressdmb.upper_pv_pressure))
    
    dmb_jsonStr_pressure = json.dumps(TelO.tele_dmb_obj.tele_pressure(adj_upper_pv_press))
    TeleLog.TelemetryLogger("DmbUpperPvPressure.txt", dmb_jsonStr_pressure)
    return "TELE_DMB_PRESSURE", dmb_jsonStr_pressure

def presspbb_parse_json_send(msg):
    adj_ib_press = 1.0152 * msg.presspbb.ib_pressure + 4.935
    adj_lower_press = 1.0152 * msg.presspbb.lower_pv_pressure + 4.935
    #pbb_jsonStr_pressure = json.dumps(TelO.tele_pbb_obj.tele_pressure(msg.presspbb.ib_pressure, msg.presspbb.lower_pv_pressure))
    
    pbb_jsonStr_pressure = json.dumps(TelO.tele_pbb_obj.tele_pressure(adj_ib_press, adj_lower_press))
    TeleLog.TelemetryLogger("PbbPressure.txt", pbb_jsonStr_pressure)
    return "TELE_PBB_PRESSURE", pbb_jsonStr_pressure

def temppbb_parse_json_send(msg):
    pbb_jsonStr_temperature = json.dumps(TelO.tele_pbb_obj.tele_temp(msg.temppbb.ib_temperature, msg.temppbb.pv_temperature))
    TeleLog.TelemetryLogger("PbbTemperature.txt", pbb_jsonStr_temperature)
    return "TELE_PBB_TEMP", pbb_jsonStr_temperature

def gpio_parse_json_send(msg):
    pbb_jsonStr_gpio_status = json.dumps(TelO.tele_pbb_obj.tele_gpio_status(msg.gpio.vent_open, msg.gpio.drain_open,msg.gpio.mev_power_enable))
    return "TELE_PBB_GPIO", pbb_jsonStr_gpio_status

def mevstate_parse_json_send(msg):
    pbb_jsonStr_mevstate = json.dumps(TelO.tele_pbb_obj.tele_mevstate(msg.mevstate.mev_open))
    return "TELE_PBB_MEVSTATE", pbb_jsonStr_mevstate

def pressrcu_parse_json_send(msg):
    rcu_jsonStr_pressure = json.dumps(TelO.tele_rcu_obj.tele_pressure(msg.pressrcu.pt1_pressure, msg.pressrcu.pt2_pressure, msg.pressrcu.pt3_pressure, msg.pressrcu.pt4_pressure))
    TeleLog.TelemetryLogger("RcuPressure.txt", rcu_jsonStr_pressure)
    return "TELE_RCU_PRESSURE", rcu_jsonStr_pressure

def temprcu_parse_json_send(msg):
    rcu_jsonStr_temp = json.dumps(TelO.tele_rcu_obj.tele_temp(msg.temprcu.tc1_temp, msg.temprcu.tc2_temp))
    TeleLog.TelemetryLogger("RcuTemperature.txt", rcu_jsonStr_temp)
    return "TELE_RCU_TEMP", rcu_jsonStr_temp

def nos_parse_json_send(msg):
    rcu_jsonStr_nos_load_cell = json.dumps(TelO.tele_rcu_obj.tele_nos_load_cell(msg.nos.nos1_mass, msg.nos.nos2_mass))
    TeleLog.TelemetryLogger("RcuNosMass.txt", rcu_jsonStr_nos_load_cell)
    return "TELE_RCU_NOS", rcu_jsonStr_nos_load_cell

def relay_parse_json_send(msg):
    rcu_jsonStr_relay_status = json.dumps(TelO.tele_rcu_obj.tele_relay_status(msg.relay.ac1_open, msg.relay.ac2_open, 
                                                                              msg.relay.pbv1_open, msg.relay.pbv2_open, msg.relay.pbv3_open,
                                                                              msg.relay.sol1_open, msg.relay.sol2_open, msg.relay.sol3_open, msg.relay.sol4_open, msg.relay.sol5_open, msg.relay.sol6_open, msg.relay.sol7_open, msg.relay.sol8a_open, msg.relay.sol8b_open))
    print(rcu_jsonStr_relay_status)
    return "TELE_RCU_RELAY", rcu_jsonStr_relay_status

def padbox_parse_json_send(msg):
    rcu_jsonStr_padbox_status = json.dumps(TelO.tele_rcu_obj.tele_padbox_status(msg.padbox.cont1, msg.padbox.cont2, msg.padbox.box1_on, msg.padbox.box2_on))
    return "TELE_RCU_PADBOX", rcu_jsonStr_padbox_status

def lr_parse_json_send(msg):
    sob_jsonStr_lr_load_cell = json.dumps(TelO.tele_sob_obj.tele_lr_load_cell(msg.lr.rocket_mass))
    TeleLog.TelemetryLogger("RcuRocketMass.txt", sob_jsonStr_lr_load_cell)
    return "TELE_SOB_LOAD_CELL", sob_jsonStr_lr_load_cell

def tempsob_parse_json_send(msg):
    sob_jsonStr_temp = json.dumps(TelO.tele_sob_obj.tele_temp(msg.tempsob.tc1_temp, msg.tempsob.tc2_temp))
    TeleLog.TelemetryLogger("SobTemperature.txt", sob_jsonStr_temp)
    return "TELE_SOB_TEMP", sob_jsonStr_temp

def irtemp_parse_json_send(msg):
    sob_jsonStr_irtemp = json.dumps(TelO.tele_sob_obj.tele_temp(msg.irtemp.ambient_temp, msg.irtemp.object_temp))
    return "TELE_SOB_IRTEMP", sob_jsonStr_irtemp

TELE_FUNCTION_DICTIONARY = {
	"coord": coord_parse_json_send,
	"baro": baro_parse_json_send,
	"imu": imu_parse_json_send,
	"bat": bat_parse_json_send,
	"flash": flash_parse_json_send,
	"pressdmb": pressdmb_parse_json_send,
    "presspbb": presspbb_parse_json_send,
	"temppbb": temppbb_parse_json_send,
	"gpio": gpio_parse_json_send,
    "mevstate": mevstate_parse_json_send,
	"pressrcu": pressrcu_parse_json_send,
	"temprcu": temprcu_parse_json_send,
	"nos": nos_parse_json_send,
	"relay": relay_parse_json_send,
	"padbox": padbox_parse_json_send,
	"lr": lr_parse_json_send,
	"tempsob": tempsob_parse_json_send,
    "irtemp": irtemp_parse_json_send
}
