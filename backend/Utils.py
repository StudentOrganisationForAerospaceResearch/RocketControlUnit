# FILE: Utils.py
# BRIEF: This file contains generic utility functions for the backend

import proto.Python.CoreProto_pb2 as ProtoCore

def get_node_from_str(target):
    return ProtoCore.Node.DESCRIPTOR.values_by_name[target].number

def get_command_from_str(target, command):
    return target.DESCRIPTOR.values_by_name[command].number

def get_node_from_enum(target):
    return ProtoCore.Node.DESCRIPTOR.values_by_number[target].name