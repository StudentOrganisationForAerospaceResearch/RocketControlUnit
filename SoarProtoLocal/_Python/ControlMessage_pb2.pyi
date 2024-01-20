import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class AckNack(_message.Message):
    __slots__ = ["acking_msg_id", "acking_msg_source", "acking_sequence_num"]
    ACKING_MSG_ID_FIELD_NUMBER: _ClassVar[int]
    ACKING_MSG_SOURCE_FIELD_NUMBER: _ClassVar[int]
    ACKING_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    acking_msg_id: _CoreProto_pb2.MessageID
    acking_msg_source: _CoreProto_pb2.Node
    acking_sequence_num: int
    def __init__(self, acking_msg_source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., acking_msg_id: _Optional[_Union[_CoreProto_pb2.MessageID, str]] = ..., acking_sequence_num: _Optional[int] = ...) -> None: ...

class ControlMessage(_message.Message):
    __slots__ = ["ack", "hb", "message_id", "nack", "ping", "source", "source_sequence_num", "sys_ctrl", "sys_state", "target"]
    ACK_FIELD_NUMBER: _ClassVar[int]
    HB_FIELD_NUMBER: _ClassVar[int]
    MESSAGE_ID_FIELD_NUMBER: _ClassVar[int]
    NACK_FIELD_NUMBER: _ClassVar[int]
    PING_FIELD_NUMBER: _ClassVar[int]
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    SOURCE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    SYS_CTRL_FIELD_NUMBER: _ClassVar[int]
    SYS_STATE_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    ack: AckNack
    hb: Heartbeat
    message_id: _CoreProto_pb2.MessageID
    nack: AckNack
    ping: Ping
    source: _CoreProto_pb2.Node
    source_sequence_num: int
    sys_ctrl: SystemControl
    sys_state: SystemState
    target: _CoreProto_pb2.Node
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., message_id: _Optional[_Union[_CoreProto_pb2.MessageID, str]] = ..., source_sequence_num: _Optional[int] = ..., ack: _Optional[_Union[AckNack, _Mapping]] = ..., nack: _Optional[_Union[AckNack, _Mapping]] = ..., ping: _Optional[_Union[Ping, _Mapping]] = ..., hb: _Optional[_Union[Heartbeat, _Mapping]] = ..., sys_state: _Optional[_Union[SystemState, _Mapping]] = ..., sys_ctrl: _Optional[_Union[SystemControl, _Mapping]] = ...) -> None: ...

class Heartbeat(_message.Message):
    __slots__ = ["hb_response_sequence_num"]
    HB_RESPONSE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    hb_response_sequence_num: int
    def __init__(self, hb_response_sequence_num: _Optional[int] = ...) -> None: ...

class Ping(_message.Message):
    __slots__ = ["ping_ack_id", "ping_response_sequence_num", "sys_state_response_required"]
    PING_ACK_ID_FIELD_NUMBER: _ClassVar[int]
    PING_RESPONSE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    SYS_STATE_RESPONSE_REQUIRED_FIELD_NUMBER: _ClassVar[int]
    ping_ack_id: int
    ping_response_sequence_num: int
    sys_state_response_required: bool
    def __init__(self, ping_ack_id: _Optional[int] = ..., ping_response_sequence_num: _Optional[int] = ..., sys_state_response_required: bool = ...) -> None: ...

class SystemControl(_message.Message):
    __slots__ = ["cmd_param", "sys_cmd"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    CMD_PARAM_FIELD_NUMBER: _ClassVar[int]
    HEARTBEAT_DISABLE: SystemControl.Command
    HEARTBEAT_ENABLE: SystemControl.Command
    SYS_CMD_FIELD_NUMBER: _ClassVar[int]
    SYS_CRITICAL_FLASH_FULL_ERASE: SystemControl.Command
    SYS_FLASH_ERASE: SystemControl.Command
    SYS_FLASH_LOG_DISABLE: SystemControl.Command
    SYS_FLASH_LOG_ENABLE: SystemControl.Command
    SYS_INVALID: SystemControl.Command
    SYS_LOG_PERIOD_CHANGE: SystemControl.Command
    SYS_RESET: SystemControl.Command
    cmd_param: int
    sys_cmd: SystemControl.Command
    def __init__(self, sys_cmd: _Optional[_Union[SystemControl.Command, str]] = ..., cmd_param: _Optional[int] = ...) -> None: ...

class SystemState(_message.Message):
    __slots__ = ["rocket_state", "sys_state"]
    class State(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    ROCKET_STATE_FIELD_NUMBER: _ClassVar[int]
    SYS_ASSERT_FAILURE_RESET: SystemState.State
    SYS_BOOTUP_COMPLETE: SystemState.State
    SYS_HEARTBEAT_LOSS_HALF_WARNING: SystemState.State
    SYS_HEARTBEAT_LOST_ABORTING: SystemState.State
    SYS_INVALID: SystemState.State
    SYS_NORMAL_OPERATION: SystemState.State
    SYS_STATE_FIELD_NUMBER: _ClassVar[int]
    SYS_UNCAUGHT_RESET: SystemState.State
    rocket_state: _CoreProto_pb2.RocketState
    sys_state: SystemState.State
    def __init__(self, sys_state: _Optional[_Union[SystemState.State, str]] = ..., rocket_state: _Optional[_Union[_CoreProto_pb2.RocketState, str]] = ...) -> None: ...
