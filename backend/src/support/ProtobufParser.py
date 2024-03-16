# FILE: ProtobufParser.py
# BRIEF: This file contains the protobuf parser class for converting protobuf messages to JSON
#         and pushing telemetry messages to PocketBase

# General imports =================================================================================
import os, sys, git
import json
from pocketbase import Client
from google.protobuf.json_format import MessageToJson

# Project specific imports ========================================================================
git_repo = git.Repo(__file__, search_parent_directories=True).git.rev_parse("--show-toplevel")
sys.path.insert(0, os.path.join(git_repo, "backend", 'proto/Python'))
import proto.Python.CoreProto_pb2 as ProtoCore
import proto.Python.ControlMessage_pb2 as ProtoCtrl
import proto.Python.CommandMessage_pb2 as ProtoCmd
import proto.Python.TelemetryMessage_pb2 as ProtoTele
import proto.Python.CoreProto_pb2 as Core

sys.path.insert(0, os.path.join(git_repo, "backend"))
from src.Utils import Utils as utl

# Class Definitions ===============================================================================
class ProtobufParser:
    @staticmethod
    def parse_protobuf_to_json(protobuf_message):
        # Convert the protobuf message to a JSON string
        print(protobuf_message)
        json_string = MessageToJson(protobuf_message, preserving_proto_field_name=True)
        return json_string

    @staticmethod
    def parse_serial_to_json(serialized_message, msg_id):
        '''
        Parse a serialized message to a JSON string

        Args:
            serialized_message: The serialized message
            msg_id: The message ID
        Throws:
            ValueError: If the message ID is invalid
        '''

        # Create message object based on message ID
        message = None
        if msg_id == Core.MessageID.MSG_COMMAND:
            message = ProtoCmd.CommandMessage()
        elif msg_id == Core.MessageID.MSG_TELEMETRY:
            message = ProtoTele.TelemetryMessage()
        elif msg_id == Core.MessageID.MSG_CONTROL:
            message = ProtoCtrl.ControlMessage()
        else:
            raise ValueError(f'Invalid message ID: {msg_id}')
        
        # Parse the serialized message
        message.ParseFromString(serialized_message)
        
        # Convert the message to JSON and print it
        json_string = ProtobufParser.parse_protobuf_to_json(message)
        return json_string

    @staticmethod
    def push_tele_json_to_pocketbase(client, json_data):
        '''
        Push a telemetry JSON message to PocketBase

        Note: The third key in the JSON data is assumed to be the table name
        '''
        # Extract the table name from the JSON data
        json_data = json.loads(json_data)
        table_name = list(json_data.keys())[2]

        print(json_data[table_name])

        # Push the JSON data to PocketBase using the correct schema
        client.collection(table_name).create(json_data[table_name])

    @staticmethod
    def create_command_proto(command: str, target: str, command_param: int, source_sequence_number: int):
        """
        Create the command message protobuf message.

        Args:
            command (str):
                The command to be sent.
            target (str):
                The target node for the command.
            command_param (int):
                The command parameter for calibration or other commands.
            source_sequence_number (int):
                Unused.

        Returns:
            command_message (ProtoCmd.CommandMessage): 
                returns the protobuf command message, None if the target is invalid.
        """
        target_enum = utl.get_node_from_str(target)
        command_message = ProtoCmd.CommandMessage()
        command_message.source = ProtoCore.NODE_RCU
        command_message.source_sequence_num = source_sequence_number

        if target_enum == ProtoCore.NODE_DMB:
            command_message.target = ProtoCore.NODE_DMB
            command_enum = utl.get_command_from_str(ProtoCmd.DmbCommand.Command, command)
            command_message.dmb_command.CopyFrom(ProtoCmd.DmbCommand(command_enum=command_enum))
        elif target_enum == ProtoCore.NODE_PBB:
            command_message.target = ProtoCore.NODE_PBB
            command_enum = utl.get_command_from_str(ProtoCmd.PbbCommand.Command, command)
            command_message.pbb_command.CopyFrom(ProtoCmd.PbbCommand(command_enum=command_enum))
        elif target_enum == ProtoCore.NODE_SOB:
            command_message.target = ProtoCore.NODE_SOB
            command_enum = utl.get_command_from_str(ProtoCmd.SobCommand.Command, command)
            command_message.sob_command.CopyFrom(ProtoCmd.SobCommand(command_enum=command_enum, command_param=command_param))
        elif target_enum == ProtoCore.NODE_RCU:
            command_message.target = ProtoCore.NODE_RCU
            command_enum = utl.get_command_from_str(ProtoCmd.RcuCommand.Command, command)
            command_message.rcu_command.CopyFrom(ProtoCmd.RcuCommand(command_enum=command_enum, command_param=command_param))
        else:
            return None
        
        return command_message

# Example code
import time, datetime

def generate_gps_serial():
    # Create a new GPS message
    gps_message = ProtoTele.Gps()

    # Latitude for Calgary
    gps_message.latitude.degrees = 51
    gps_message.latitude.minutes = int((0.0447 * 60))

    # Longitude for Calgary
    gps_message.longitude.degrees = -114
    gps_message.longitude.minutes = int((0.0719 * 60))

    gps_message.antenna_altitude.altitude = 123
    gps_message.antenna_altitude.unit = 1
    gps_message.geo_id_altitude.altitude = 123
    gps_message.geo_id_altitude.unit = 1
    gps_message.total_altitude.altitude = 123
    gps_message.total_altitude.unit = 1

    # Set the time to 2024-01-01T00:00:00Z
    gps_message.time = int(time.mktime(datetime.datetime(2024, 1, 1).timetuple()))

    # Wrap in TelemetryMessage
    telemetry_message = ProtoTele.TelemetryMessage()
    telemetry_message.gps.CopyFrom(gps_message)
    telemetry_message.source = Core.NODE_DMB
    telemetry_message.target = Core.NODE_RCU

    # Serialize the message
    serialized_message = telemetry_message.SerializeToString()
    return serialized_message

if __name__ == "__main__":
    # Generate a GPS message
    serialized_message = generate_gps_serial()

    # Parse the serialized message to JSON
    parsed = ProtobufParser.parse_serial_to_json(serialized_message, Core.MessageID.MSG_TELEMETRY)
    
    client = Client("http://127.0.0.1:8090")
    ProtobufParser.push_tele_json_to_pocketbase(client, parsed)

    # Output
    # print(parsed)