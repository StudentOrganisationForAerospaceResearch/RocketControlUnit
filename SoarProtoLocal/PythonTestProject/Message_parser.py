import SoarLib.ControlMessage_pb2 as ProtoCtr
import SoarLib.CommandMessage_pb2 as ProtoCmd
import SoarLib.TelemetryMessage_pb2 as ProtoTele
import SoarLib.CoreProto_pb2 as ProtoCore
import Protobuf_parser as ProtoParse
import Telemetry_Objects as TelO
import Serial_handler as SeHan
import Ethernet_handler as EtHan
import json

# Constants
PASSPHRASE = '1'
DMB_SEQ_NUM = 10
PBB_SEQ_NUM = 20
SOB_SEQ_NUM = 30
RCU_SEQ_NUM = 40

# Globals
sequence_number = 1

def send_command_msg(data_dictionary):
    global sequence_number

    command = data_dictionary["command"]

    #create message
    msg = ProtoCmd.CommandMessage()
    msg.source = ProtoCore.NODE_RCU
    msg.source_sequence_num = sequence_number
    sequence_number = sequence_number + 1

    dmb_command = ProtoParse.STRING_TO_RSC_PROTO_COMMAND.get(command)

    if dmb_command != None:
        if(SeHan.PORT == "/dev/ttyS0"):
            return False
        
        if data_dictionary["passphrase"] != PASSPHRASE:
            EtHan.soar_publish("TELE_PI_ERROR", json.dumps({"error": "Invalid Passphrase"}))
            return False

        if command not in ProtoParse.ALLOWED_COMMANDS_FROM_STATE[TelO.tele_dmb_obj.current_state]:
            EtHan.soar_publish("TELE_PI_ERROR", json.dumps({"error": "Invalid RSC Command"}))
            return False

        msg.dmb_command.command_enum = dmb_command
        msg.target = ProtoCore.NODE_DMB
        SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_COMMAND, ProtoCore.NODE_DMB)
        print(command)
        return True

    pbb_command = ProtoParse.STRING_TO_PBB_PROTO_COMMAND.get(command)

    if pbb_command != None:
        if(SeHan.PORT == "/dev/ttyS0"):
            return False

        msg.pbb_command.command_enum = pbb_command
        msg.target = ProtoCore.NODE_PBB
        SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_COMMAND, ProtoCore.NODE_PBB)
        return True

    rcu_command = ProtoParse.STRING_TO_RCU_PROTO_COMMAND.get(command)

    if rcu_command != None:
        if(SeHan.PORT == "/dev/ttyUSB0"):
            return False
        msg.rcu_command.command_enum = rcu_command
        msg.target = ProtoCore.NODE_RCU
        SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_COMMAND, ProtoCore.NODE_RCU)
        return True

	# if rcu command is sol8a, then send also send the opposite command for the sol8b & vice versa

    sob_command = ProtoParse.STRING_TO_SOB_PROTO_COMMAND.get(command)

    if sob_command != None:
        #no
        #if(SeHan.PORT == "/dev/ttyS0"):
        #    return False
        #msg.sob_command.command_enum = sob_command
        #msg.target = ProtoCore.NODE_SOB
        #SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_COMMAND, ProtoCore.NODE_SOB)
        return True

    pi_command = ProtoParse.STRING_TO_PI_COMMAND.get(command)

    if pi_command != None:
        ProtoParse.STRING_TO_PI_COMMAND_FUNCTION.get(pi_command)(float(data_dictionary["passphrase"]))
        return False

    EtHan.soar_publish("TELE_PI_ERROR", json.dumps({"error": "Invalid Command"}))
    return False

def send_ack_message(msg):
    ack_msg = ProtoCmd.ControlMessage()
    ack_msg.source = ProtoCore.NODE_RCU
    ack_msg.target = msg.source
    ack_msg.message_id = ProtoCore.MSG_CONTROL
    ack_msg.source_sequence_number = 0
    ack_msg.ack.acking_msg_id = msg.message_id
    ack_msg.ack.acking_msg_source = ProtoCore.NODE_RCU
    ack_msg.ack.acking_sequence_num = msg.source_sequence_number
    
    SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_CONTROL, msg.source)

def send_ping_message(target):
    global sequence_number

    #create message  
    msg = ProtoCtr.ControlMessage()
    msg.source = ProtoCore.NODE_RCU
    msg.source_sequence_num = sequence_number
    sequence_number = sequence_number + 1
    ping = ProtoCtr.Ping()

    if target == "DMB":
        msg.target == ProtoCore.NODE_DMB
        ping.ping_ack_id = ProtoCore.MSG_CONTROL
        ping.ping_response_sequence_num = DMB_SEQ_NUM
        ping.sys_state_response_required = True
    elif target == "PBB":
        msg.target == ProtoCore.NODE_PBB
        ping.ping_ack_id = ProtoCore.MSG_CONTROL
        ping.ping_response_sequence_num = PBB_SEQ_NUM
        ping.sys_state_response_required = False
    elif target == "SOB":
        msg.target == ProtoCore.NODE_SOB
        ping.ping_ack_id = ProtoCore.MSG_CONTROL
        ping.ping_response_sequence_num = SOB_SEQ_NUM
        ping.sys_state_response_required = False
    elif target == "RCU":
        msg.target == ProtoCore.NODE_RCU
        ping.ping_ack_id = ProtoCore.MSG_CONTROL
        ping.ping_response_sequence_num = RCU_SEQ_NUM
        ping.sys_state_response_required = False

    msg.ping.CopyFrom(ping)

    SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_CONTROL, msg.target)

def send_heartbeat_msg(target):
    msg = ProtoCtr.ControlMessage()
    msg.source = ProtoCore.NODE_RCU
    msg.target = target
    foo = ProtoCtr.Heartbeat()
    msg.hb.CopyFrom(foo)

    SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_CONTROL, target)

def send_reset_message(target):
    global sequence_number

    #create message  
    msg = ProtoCtr.ControlMessage()
    msg.source = ProtoCore.NODE_RCU
    msg.source_sequence_num = sequence_number
    sequence_number = sequence_number + 1
    sys_ctr = ProtoCtr.SystemControl()

    if target == "DMB":
        msg.target == ProtoCore.NODE_DMB
        sys_ctr.sys_cmd = ProtoCtr.SystemControl.SYS_RESET
    elif target == "PBB":
        msg.target == ProtoCore.NODE_PBB
        sys_ctr.sys_cmd = ProtoCtr.SystemControl.SYS_RESET
    elif target == "SOB":
        msg.target == ProtoCore.NODE_SOB
        sys_ctr.sys_cmd = ProtoCtr.SystemControl.SYS_RESET
    elif target == "RCU":
        msg.target == ProtoCore.NODE_RCU
        sys_ctr.sys_cmd = ProtoCtr.SystemControl.SYS_RESET

    msg.sys_ctrl.CopyFrom(sys_ctr)
    print(msg)
    SeHan.send_serial_message(msg, ProtoCore.MessageID.MSG_CONTROL, msg.target)