# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ControlMessage.proto
# Protobuf Python Version: 4.25.3
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import CoreProto_pb2 as CoreProto__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x14\x43ontrolMessage.proto\x12\x05Proto\x1a\x0f\x43oreProto.proto\"\xec\x02\n\x0e\x43ontrolMessage\x12\x1b\n\x06source\x18\x01 \x01(\x0e\x32\x0b.Proto.Node\x12\x1b\n\x06target\x18\x02 \x01(\x0e\x32\x0b.Proto.Node\x12\x1b\n\x13source_sequence_num\x18\x04 \x01(\r\x12\x1d\n\x03\x61\x63k\x18\x05 \x01(\x0b\x32\x0e.Proto.AckNackH\x00\x12\x1e\n\x04nack\x18\x06 \x01(\x0b\x32\x0e.Proto.AckNackH\x00\x12\x1b\n\x04ping\x18\x07 \x01(\x0b\x32\x0b.Proto.PingH\x00\x12\x1e\n\x02hb\x18\x08 \x01(\x0b\x32\x10.Proto.HeartbeatH\x00\x12\'\n\tsys_state\x18\t \x01(\x0b\x32\x12.Proto.SystemStateH\x00\x12(\n\x08sys_ctrl\x18\n \x01(\x0b\x32\x14.Proto.SystemControlH\x00\x12)\n\x08hb_state\x18\x0b \x01(\x0b\x32\x15.Proto.HeartbeatStateH\x00\x42\t\n\x07message\"w\n\x07\x41\x63kNack\x12&\n\x11\x61\x63king_msg_source\x18\x01 \x01(\x0e\x32\x0b.Proto.Node\x12\'\n\racking_msg_id\x18\x02 \x01(\x0e\x32\x10.Proto.MessageID\x12\x1b\n\x13\x61\x63king_sequence_num\x18\x03 \x01(\r\"d\n\x04Ping\x12\x13\n\x0bping_ack_id\x18\x01 \x01(\r\x12\"\n\x1aping_response_sequence_num\x18\x02 \x01(\r\x12#\n\x1bsys_state_response_required\x18\x03 \x01(\x08\"-\n\tHeartbeat\x12 \n\x18hb_response_sequence_num\x18\x01 \x01(\r\"\xc4\x02\n\x0bSystemState\x12+\n\tsys_state\x18\x01 \x01(\x0e\x32\x18.Proto.SystemState.State\x12-\n\x0crocket_state\x18\x02 \x01(\x0e\x32\x12.Proto.RocketStateH\x00\x88\x01\x01\"\xc7\x01\n\x05State\x12\x0f\n\x0bSYS_INVALID\x10\x00\x12\x17\n\x13SYS_BOOTUP_COMPLETE\x10\x01\x12\x1c\n\x18SYS_ASSERT_FAILURE_RESET\x10\x02\x12\x16\n\x12SYS_UNCAUGHT_RESET\x10\x03\x12\x18\n\x14SYS_NORMAL_OPERATION\x10\x04\x12#\n\x1fSYS_HEARTBEAT_LOSS_HALF_WARNING\x10\x05\x12\x1f\n\x1bSYS_HEARTBEAT_LOST_ABORTING\x10\x06\x42\x0f\n\r_rocket_state\"\xb2\x02\n\rSystemControl\x12-\n\x07sys_cmd\x18\x01 \x01(\x0e\x32\x1c.Proto.SystemControl.Command\x12\x11\n\tcmd_param\x18\x02 \x01(\r\"\xde\x01\n\x07\x43ommand\x12\x0f\n\x0bSYS_INVALID\x10\x00\x12\r\n\tSYS_RESET\x10\x01\x12\x13\n\x0fSYS_FLASH_ERASE\x10\x02\x12\x19\n\x15SYS_LOG_PERIOD_CHANGE\x10\x03\x12\x14\n\x10HEARTBEAT_ENABLE\x10\x04\x12\x15\n\x11HEARTBEAT_DISABLE\x10\x05\x12\x18\n\x14SYS_FLASH_LOG_ENABLE\x10\x06\x12\x19\n\x15SYS_FLASH_LOG_DISABLE\x10\x07\x12!\n\x1dSYS_CRITICAL_FLASH_FULL_ERASE\x10\x08\"\xbf\x01\n\x0eHeartbeatState\x12\x35\n\x0btimer_state\x18\x01 \x01(\x0e\x32 .Proto.HeartbeatState.TimerState\x12\x14\n\x0ctimer_period\x18\x02 \x01(\r\x12\x17\n\x0ftimer_remaining\x18\x03 \x01(\r\"G\n\nTimerState\x12\x11\n\rUNINITIALIZED\x10\x00\x12\x0c\n\x08\x43OUNTING\x10\x01\x12\n\n\x06PAUSED\x10\x02\x12\x0c\n\x08\x43OMPLETE\x10\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ControlMessage_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_CONTROLMESSAGE']._serialized_start=49
  _globals['_CONTROLMESSAGE']._serialized_end=413
  _globals['_ACKNACK']._serialized_start=415
  _globals['_ACKNACK']._serialized_end=534
  _globals['_PING']._serialized_start=536
  _globals['_PING']._serialized_end=636
  _globals['_HEARTBEAT']._serialized_start=638
  _globals['_HEARTBEAT']._serialized_end=683
  _globals['_SYSTEMSTATE']._serialized_start=686
  _globals['_SYSTEMSTATE']._serialized_end=1010
  _globals['_SYSTEMSTATE_STATE']._serialized_start=794
  _globals['_SYSTEMSTATE_STATE']._serialized_end=993
  _globals['_SYSTEMCONTROL']._serialized_start=1013
  _globals['_SYSTEMCONTROL']._serialized_end=1319
  _globals['_SYSTEMCONTROL_COMMAND']._serialized_start=1097
  _globals['_SYSTEMCONTROL_COMMAND']._serialized_end=1319
  _globals['_HEARTBEATSTATE']._serialized_start=1322
  _globals['_HEARTBEATSTATE']._serialized_end=1513
  _globals['_HEARTBEATSTATE_TIMERSTATE']._serialized_start=1442
  _globals['_HEARTBEATSTATE_TIMERSTATE']._serialized_end=1513
# @@protoc_insertion_point(module_scope)
