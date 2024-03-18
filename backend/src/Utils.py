# FILE: Utils.py
# BRIEF: This file contains generic utility functions for the backend

# Project specific imports ========================================================================
import proto.Python.CoreProto_pb2 as ProtoCore

# Class Definitions ===============================================================================
class Utils:

    @staticmethod
    def get_node_from_str(target):
        """
        Get the ProtoCore.Node enum number value from the string target.
        """
        return ProtoCore.Node.DESCRIPTOR.values_by_name[target].number

    @staticmethod
    def get_command_from_str(target, command):
        """
        Get the command enum number value from the string command.
        """
        return target.DESCRIPTOR.values_by_name[command].number

    @staticmethod
    def get_node_from_enum(target):
        """
        Get the node name from the ProtoCore.Node enum number.
        """
        return ProtoCore.Node.DESCRIPTOR.values_by_number[target].name
    
    @staticmethod
    def get_message_from_enum(target):
        """
        Get the message name from the ProtoCore.Node enum number.
        """
        return ProtoCore.MessageID.DESCRIPTOR.values_by_number[target].name
