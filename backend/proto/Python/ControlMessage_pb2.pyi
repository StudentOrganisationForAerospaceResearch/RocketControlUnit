import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class ControlMessage(_message.Message):
    __slots__ = ("source", "target", "source_sequence_num", "ack", "nack", "ping", "hb", "sys_state", "sys_ctrl", "hb_state")
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    SOURCE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    ACK_FIELD_NUMBER: _ClassVar[int]
    NACK_FIELD_NUMBER: _ClassVar[int]
    PING_FIELD_NUMBER: _ClassVar[int]
    HB_FIELD_NUMBER: _ClassVar[int]
    SYS_STATE_FIELD_NUMBER: _ClassVar[int]
    SYS_CTRL_FIELD_NUMBER: _ClassVar[int]
    HB_STATE_FIELD_NUMBER: _ClassVar[int]
    source: _CoreProto_pb2.Node
    target: _CoreProto_pb2.Node
    source_sequence_num: int
    ack: AckNack
    nack: AckNack
    ping: Ping
    hb: Heartbeat
    sys_state: SystemState
    sys_ctrl: SystemControl
    hb_state: HeartbeatState
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., source_sequence_num: _Optional[int] = ..., ack: _Optional[_Union[AckNack, _Mapping]] = ..., nack: _Optional[_Union[AckNack, _Mapping]] = ..., ping: _Optional[_Union[Ping, _Mapping]] = ..., hb: _Optional[_Union[Heartbeat, _Mapping]] = ..., sys_state: _Optional[_Union[SystemState, _Mapping]] = ..., sys_ctrl: _Optional[_Union[SystemControl, _Mapping]] = ..., hb_state: _Optional[_Union[HeartbeatState, _Mapping]] = ...) -> None: ...

class AckNack(_message.Message):
    __slots__ = ("acking_msg_source", "acking_msg_id", "acking_sequence_num")
    ACKING_MSG_SOURCE_FIELD_NUMBER: _ClassVar[int]
    ACKING_MSG_ID_FIELD_NUMBER: _ClassVar[int]
    ACKING_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    acking_msg_source: _CoreProto_pb2.Node
    acking_msg_id: _CoreProto_pb2.MessageID
    acking_sequence_num: int
    def __init__(self, acking_msg_source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., acking_msg_id: _Optional[_Union[_CoreProto_pb2.MessageID, str]] = ..., acking_sequence_num: _Optional[int] = ...) -> None: ...

class Ping(_message.Message):
    __slots__ = ("ping_ack_id", "ping_response_sequence_num", "sys_state_response_required")
    PING_ACK_ID_FIELD_NUMBER: _ClassVar[int]
    PING_RESPONSE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    SYS_STATE_RESPONSE_REQUIRED_FIELD_NUMBER: _ClassVar[int]
    ping_ack_id: int
    ping_response_sequence_num: int
    sys_state_response_required: bool
    def __init__(self, ping_ack_id: _Optional[int] = ..., ping_response_sequence_num: _Optional[int] = ..., sys_state_response_required: bool = ...) -> None: ...

class Heartbeat(_message.Message):
    __slots__ = ("hb_response_sequence_num",)
    HB_RESPONSE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    hb_response_sequence_num: int
    def __init__(self, hb_response_sequence_num: _Optional[int] = ...) -> None: ...

class SystemState(_message.Message):
    __slots__ = ("sys_state", "rocket_state")
    class State(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        SYS_INVALID: _ClassVar[SystemState.State]
        SYS_BOOTUP_COMPLETE: _ClassVar[SystemState.State]
        SYS_ASSERT_FAILURE_RESET: _ClassVar[SystemState.State]
        SYS_UNCAUGHT_RESET: _ClassVar[SystemState.State]
        SYS_NORMAL_OPERATION: _ClassVar[SystemState.State]
        SYS_HEARTBEAT_LOSS_HALF_WARNING: _ClassVar[SystemState.State]
        SYS_HEARTBEAT_LOST_ABORTING: _ClassVar[SystemState.State]
        SYS_WAIT: _ClassVar[SystemState.State]
        SYS_RETRANSMIT: _ClassVar[SystemState.State]
        SYS_TIMEOUT: _ClassVar[SystemState.State]
        SYS_SEND_NEXT_CMD: _ClassVar[SystemState.State]
    SYS_INVALID: SystemState.State
    SYS_BOOTUP_COMPLETE: SystemState.State
    SYS_ASSERT_FAILURE_RESET: SystemState.State
    SYS_UNCAUGHT_RESET: SystemState.State
    SYS_NORMAL_OPERATION: SystemState.State
    SYS_HEARTBEAT_LOSS_HALF_WARNING: SystemState.State
    SYS_HEARTBEAT_LOST_ABORTING: SystemState.State
    SYS_WAIT: SystemState.State
    SYS_RETRANSMIT: SystemState.State
    SYS_TIMEOUT: SystemState.State
    SYS_SEND_NEXT_CMD: SystemState.State
    SYS_STATE_FIELD_NUMBER: _ClassVar[int]
    ROCKET_STATE_FIELD_NUMBER: _ClassVar[int]
    sys_state: SystemState.State
    rocket_state: _CoreProto_pb2.RocketState
    def __init__(self, sys_state: _Optional[_Union[SystemState.State, str]] = ..., rocket_state: _Optional[_Union[_CoreProto_pb2.RocketState, str]] = ...) -> None: ...

class SystemControl(_message.Message):
    __slots__ = ("sys_cmd", "cmd_param")
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        SYS_INVALID: _ClassVar[SystemControl.Command]
        SYS_RESET: _ClassVar[SystemControl.Command]
        SYS_FLASH_ERASE: _ClassVar[SystemControl.Command]
        SYS_LOG_PERIOD_CHANGE: _ClassVar[SystemControl.Command]
        HEARTBEAT_ENABLE: _ClassVar[SystemControl.Command]
        HEARTBEAT_DISABLE: _ClassVar[SystemControl.Command]
        SYS_FLASH_LOG_ENABLE: _ClassVar[SystemControl.Command]
        SYS_FLASH_LOG_DISABLE: _ClassVar[SystemControl.Command]
        SYS_CRITICAL_FLASH_FULL_ERASE: _ClassVar[SystemControl.Command]
    SYS_INVALID: SystemControl.Command
    SYS_RESET: SystemControl.Command
    SYS_FLASH_ERASE: SystemControl.Command
    SYS_LOG_PERIOD_CHANGE: SystemControl.Command
    HEARTBEAT_ENABLE: SystemControl.Command
    HEARTBEAT_DISABLE: SystemControl.Command
    SYS_FLASH_LOG_ENABLE: SystemControl.Command
    SYS_FLASH_LOG_DISABLE: SystemControl.Command
    SYS_CRITICAL_FLASH_FULL_ERASE: SystemControl.Command
    SYS_CMD_FIELD_NUMBER: _ClassVar[int]
    CMD_PARAM_FIELD_NUMBER: _ClassVar[int]
    sys_cmd: SystemControl.Command
    cmd_param: int
    def __init__(self, sys_cmd: _Optional[_Union[SystemControl.Command, str]] = ..., cmd_param: _Optional[int] = ...) -> None: ...

class HeartbeatState(_message.Message):
    __slots__ = ("timer_state", "timer_period", "timer_remaining")
    class TimerState(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        UNINITIALIZED: _ClassVar[HeartbeatState.TimerState]
        COUNTING: _ClassVar[HeartbeatState.TimerState]
        PAUSED: _ClassVar[HeartbeatState.TimerState]
        COMPLETE: _ClassVar[HeartbeatState.TimerState]
    UNINITIALIZED: HeartbeatState.TimerState
    COUNTING: HeartbeatState.TimerState
    PAUSED: HeartbeatState.TimerState
    COMPLETE: HeartbeatState.TimerState
    TIMER_STATE_FIELD_NUMBER: _ClassVar[int]
    TIMER_PERIOD_FIELD_NUMBER: _ClassVar[int]
    TIMER_REMAINING_FIELD_NUMBER: _ClassVar[int]
    timer_state: HeartbeatState.TimerState
    timer_period: int
    timer_remaining: int
    def __init__(self, timer_state: _Optional[_Union[HeartbeatState.TimerState, str]] = ..., timer_period: _Optional[int] = ..., timer_remaining: _Optional[int] = ...) -> None: ...
