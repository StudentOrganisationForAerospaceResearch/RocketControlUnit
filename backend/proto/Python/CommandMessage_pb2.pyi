import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class CommandMessage(_message.Message):
    __slots__ = ["dmb_command", "pbb_command", "rcu_command", "sob_command", "source", "source_sequence_num", "target"]
    DMB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    PBB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    RCU_COMMAND_FIELD_NUMBER: _ClassVar[int]
    SOB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    SOURCE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    dmb_command: DmbCommand
    pbb_command: PbbCommand
    rcu_command: RcuCommand
    sob_command: SobCommand
    source: _CoreProto_pb2.Node
    source_sequence_num: int
    target: _CoreProto_pb2.Node
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., source_sequence_num: _Optional[int] = ..., dmb_command: _Optional[_Union[DmbCommand, _Mapping]] = ..., pbb_command: _Optional[_Union[PbbCommand, _Mapping]] = ..., rcu_command: _Optional[_Union[RcuCommand, _Mapping]] = ..., sob_command: _Optional[_Union[SobCommand, _Mapping]] = ...) -> None: ...

class DmbCommand(_message.Message):
    __slots__ = ["command_enum"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    RSC_ANY_TO_ABORT: DmbCommand.Command
    RSC_ARM_CONFIRM_1: DmbCommand.Command
    RSC_ARM_CONFIRM_2: DmbCommand.Command
    RSC_BURN_TO_COAST: DmbCommand.Command
    RSC_CLOSE_DRAIN: DmbCommand.Command
    RSC_CLOSE_VENT: DmbCommand.Command
    RSC_COAST_TO_DESCENT: DmbCommand.Command
    RSC_DESCENT_TO_RECOVERY: DmbCommand.Command
    RSC_FIRST_INVALID: DmbCommand.Command
    RSC_GOTO_ARM: DmbCommand.Command
    RSC_GOTO_FILL: DmbCommand.Command
    RSC_GOTO_IGNITION: DmbCommand.Command
    RSC_GOTO_PRELAUNCH: DmbCommand.Command
    RSC_GOTO_TEST: DmbCommand.Command
    RSC_IGNITION_TO_LAUNCH: DmbCommand.Command
    RSC_LAUNCH_TO_BURN: DmbCommand.Command
    RSC_MEV_CLOSE: DmbCommand.Command
    RSC_NONE: DmbCommand.Command
    RSC_OPEN_DRAIN: DmbCommand.Command
    RSC_OPEN_VENT: DmbCommand.Command
    RSC_POWER_TRANSITION_EXTERNAL: DmbCommand.Command
    RSC_POWER_TRANSITION_ONBOARD: DmbCommand.Command
    RSC_TEST_MEV_DISABLE: DmbCommand.Command
    RSC_TEST_MEV_ENABLE: DmbCommand.Command
    RSC_TEST_MEV_OPEN: DmbCommand.Command
    command_enum: DmbCommand.Command
    def __init__(self, command_enum: _Optional[_Union[DmbCommand.Command, str]] = ...) -> None: ...

class PbbCommand(_message.Message):
    __slots__ = ["command_enum"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    PBB_CLOSE_MEV: PbbCommand.Command
    PBB_NONE: PbbCommand.Command
    PBB_OPEN_MEV: PbbCommand.Command
    PMB_LAST: PbbCommand.Command
    command_enum: PbbCommand.Command
    def __init__(self, command_enum: _Optional[_Union[PbbCommand.Command, str]] = ...) -> None: ...

class RcuCommand(_message.Message):
    __slots__ = ["command_enum", "command_param"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    COMMAND_PARAM_FIELD_NUMBER: _ClassVar[int]
    RCU_CALIBRATE_NOS1_LOAD_CELL: RcuCommand.Command
    RCU_CALIBRATE_NOS2_LOAD_CELL: RcuCommand.Command
    RCU_CLOSE_AC1: RcuCommand.Command
    RCU_CLOSE_AC2: RcuCommand.Command
    RCU_CLOSE_PBV1: RcuCommand.Command
    RCU_CLOSE_PBV2: RcuCommand.Command
    RCU_CLOSE_PBV3: RcuCommand.Command
    RCU_CLOSE_SOL1: RcuCommand.Command
    RCU_CLOSE_SOL2: RcuCommand.Command
    RCU_CLOSE_SOL3: RcuCommand.Command
    RCU_CLOSE_SOL4: RcuCommand.Command
    RCU_CLOSE_SOL5: RcuCommand.Command
    RCU_CLOSE_SOL6: RcuCommand.Command
    RCU_CLOSE_SOL7: RcuCommand.Command
    RCU_CLOSE_SOL8A: RcuCommand.Command
    RCU_CLOSE_SOL8B: RcuCommand.Command
    RCU_IGNITE_PAD_BOX1: RcuCommand.Command
    RCU_IGNITE_PAD_BOX2: RcuCommand.Command
    RCU_KILL_PAD_BOX1: RcuCommand.Command
    RCU_KILL_PAD_BOX2: RcuCommand.Command
    RCU_LAST: RcuCommand.Command
    RCU_NONE: RcuCommand.Command
    RCU_OPEN_AC1: RcuCommand.Command
    RCU_OPEN_AC2: RcuCommand.Command
    RCU_OPEN_PBV1: RcuCommand.Command
    RCU_OPEN_PBV2: RcuCommand.Command
    RCU_OPEN_PBV3: RcuCommand.Command
    RCU_OPEN_SOL1: RcuCommand.Command
    RCU_OPEN_SOL2: RcuCommand.Command
    RCU_OPEN_SOL3: RcuCommand.Command
    RCU_OPEN_SOL4: RcuCommand.Command
    RCU_OPEN_SOL5: RcuCommand.Command
    RCU_OPEN_SOL6: RcuCommand.Command
    RCU_OPEN_SOL7: RcuCommand.Command
    RCU_OPEN_SOL8A: RcuCommand.Command
    RCU_OPEN_SOL8B: RcuCommand.Command
    RCU_TARE_NOS1_LOAD_CELL: RcuCommand.Command
    RCU_TARE_NOS2_LOAD_CELL: RcuCommand.Command
    command_enum: RcuCommand.Command
    command_param: int
    def __init__(self, command_enum: _Optional[_Union[RcuCommand.Command, str]] = ..., command_param: _Optional[int] = ...) -> None: ...

class SobCommand(_message.Message):
    __slots__ = ["command_enum", "command_param"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    COMMAND_PARAM_FIELD_NUMBER: _ClassVar[int]
    SOB_CALIBRATE_LOAD_CELL: SobCommand.Command
    SOB_FAST_SAMPLE_IR: SobCommand.Command
    SOB_LAST: SobCommand.Command
    SOB_NONE: SobCommand.Command
    SOB_SLOW_SAMPLE_IR: SobCommand.Command
    SOB_TARE_LOAD_CELL: SobCommand.Command
    command_enum: SobCommand.Command
    command_param: int
    def __init__(self, command_enum: _Optional[_Union[SobCommand.Command, str]] = ..., command_param: _Optional[int] = ...) -> None: ...
