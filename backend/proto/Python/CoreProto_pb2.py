# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: CoreProto.proto
# Protobuf Python Version: 4.25.3
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0f\x43oreProto.proto\x12\x05Proto*p\n\x04Node\x12\x10\n\x0cNODE_INVALID\x10\x00\x12\x10\n\x0cNODE_UNKNOWN\x10\x01\x12\x0c\n\x08NODE_ANY\x10\x02\x12\x0c\n\x08NODE_RCU\x10\x03\x12\x0c\n\x08NODE_DMB\x10\x04\x12\x0c\n\x08NODE_PBB\x10\x05\x12\x0c\n\x08NODE_SOB\x10\x06*w\n\tMessageID\x12\x0f\n\x0bMSG_INVALID\x10\x00\x12\x0f\n\x0bMSG_UNKNOWN\x10\x01\x12\x0f\n\x0bMSG_CONTROL\x10\x02\x12\x0f\n\x0bMSG_COMMAND\x10\x03\x12\x11\n\rMSG_TELEMETRY\x10\x04\x12\x13\n\x0fMSG_MAX_INVALID\x10\x05*\xcd\x01\n\x0bRocketState\x12\x0f\n\x0b\x44MB_INVALID\x10\x00\x12\x10\n\x0cRS_PRELAUNCH\x10\x01\x12\x0b\n\x07RS_FILL\x10\x02\x12\n\n\x06RS_ARM\x10\x03\x12\x0f\n\x0bRS_IGNITION\x10\x04\x12\r\n\tRS_LAUNCH\x10\x05\x12\x0b\n\x07RS_BURN\x10\x06\x12\x0c\n\x08RS_COAST\x10\x07\x12\x0e\n\nRS_DESCENT\x10\x08\x12\x0f\n\x0bRS_RECOVERY\x10\t\x12\x0c\n\x08RS_ABORT\x10\n\x12\x0b\n\x07RS_TEST\x10\x0b\x12\x0b\n\x07RS_NONE\x10\x0c\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'CoreProto_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_NODE']._serialized_start=26
  _globals['_NODE']._serialized_end=138
  _globals['_MESSAGEID']._serialized_start=140
  _globals['_MESSAGEID']._serialized_end=259
  _globals['_ROCKETSTATE']._serialized_start=262
  _globals['_ROCKETSTATE']._serialized_end=467
# @@protoc_insertion_point(module_scope)
