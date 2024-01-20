import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class CommandMessage(_message.Message):
    __slots__ = ["dmb_command", "message_id", "pbb_command", "rcu_command", "sob_command", "source", "source_sequence_num", "target"]
    DMB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    MESSAGE_ID_FIELD_NUMBER: _ClassVar[int]
    PBB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    RCU_COMMAND_FIELD_NUMBER: _ClassVar[int]
    SOB_COMMAND_FIELD_NUMBER: _ClassVar[int]
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    SOURCE_SEQUENCE_NUM_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    dmb_command: DMBCommand
    message_id: _CoreProto_pb2.MessageID
    pbb_command: PBBCommand
    rcu_command: RCUCommand
    sob_command: SOBCommand
    source: _CoreProto_pb2.Node
    source_sequence_num: int
    target: _CoreProto_pb2.Node
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., message_id: _Optional[_Union[_CoreProto_pb2.MessageID, str]] = ..., source_sequence_num: _Optional[int] = ..., dmb_command: _Optional[_Union[DMBCommand, _Mapping]] = ..., pbb_command: _Optional[_Union[PBBCommand, _Mapping]] = ..., rcu_command: _Optional[_Union[RCUCommand, _Mapping]] = ..., sob_command: _Optional[_Union[SOBCommand, _Mapping]] = ...) -> None: ...

class DMBCommand(_message.Message):
    __slots__ = ["command_enum"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    RSC_ANY_TO_ABORT: DMBCommand.Command
    RSC_ARM_CONFIRM_1: DMBCommand.Command
    RSC_ARM_CONFIRM_2: DMBCommand.Command
    RSC_BURN_TO_COAST: DMBCommand.Command
    RSC_CLOSE_DRAIN: DMBCommand.Command
    RSC_CLOSE_VENT: DMBCommand.Command
    RSC_COAST_TO_DESCENT: DMBCommand.Command
    RSC_DESCENT_TO_RECOVERY: DMBCommand.Command
    RSC_FIRST_INVALID: DMBCommand.Command
    RSC_GOTO_ARM: DMBCommand.Command
    RSC_GOTO_FILL: DMBCommand.Command
    RSC_GOTO_IGNITION: DMBCommand.Command
    RSC_GOTO_PRELAUNCH: DMBCommand.Command
    RSC_GOTO_TEST: DMBCommand.Command
    RSC_IGNITION_TO_LAUNCH: DMBCommand.Command
    RSC_LAUNCH_TO_BURN: DMBCommand.Command
    RSC_MEV_CLOSE: DMBCommand.Command
    RSC_NONE: DMBCommand.Command
    RSC_OPEN_DRAIN: DMBCommand.Command
    RSC_OPEN_VENT: DMBCommand.Command
    RSC_POWER_TRANSITION_EXTERNAL: DMBCommand.Command
    RSC_POWER_TRANSITION_ONBOARD: DMBCommand.Command
    RSC_TEST_MEV_DISABLE: DMBCommand.Command
    RSC_TEST_MEV_ENABLE: DMBCommand.Command
    RSC_TEST_MEV_OPEN: DMBCommand.Command
    command_enum: DMBCommand.Command
    def __init__(self, command_enum: _Optional[_Union[DMBCommand.Command, str]] = ...) -> None: ...

class PBBCommand(_message.Message):
    __slots__ = ["command_enum"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    PBB_CLOSE_MEV: PBBCommand.Command
    PBB_NONE: PBBCommand.Command
    PBB_OPEN_MEV: PBBCommand.Command
    PMB_LAST: PBBCommand.Command
    command_enum: PBBCommand.Command
    def __init__(self, command_enum: _Optional[_Union[PBBCommand.Command, str]] = ...) -> None: ...

class RCUCommand(_message.Message):
    __slots__ = ["command_enum", "command_param"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    COMMAND_PARAM_FIELD_NUMBER: _ClassVar[int]
    RCU_CALIBRATE_NOS1_LOAD_CELL: RCUCommand.Command
    RCU_CALIBRATE_NOS2_LOAD_CELL: RCUCommand.Command
    RCU_CLOSE_AC1: RCUCommand.Command
    RCU_CLOSE_AC2: RCUCommand.Command
    RCU_CLOSE_PBV1: RCUCommand.Command
    RCU_CLOSE_PBV2: RCUCommand.Command
    RCU_CLOSE_PBV3: RCUCommand.Command
    RCU_CLOSE_SOL1: RCUCommand.Command
    RCU_CLOSE_SOL2: RCUCommand.Command
    RCU_CLOSE_SOL3: RCUCommand.Command
    RCU_CLOSE_SOL4: RCUCommand.Command
    RCU_CLOSE_SOL5: RCUCommand.Command
    RCU_CLOSE_SOL6: RCUCommand.Command
    RCU_CLOSE_SOL7: RCUCommand.Command
    RCU_CLOSE_SOL8A: RCUCommand.Command
    RCU_CLOSE_SOL8B: RCUCommand.Command
    RCU_IGNITE_PAD_BOX1: RCUCommand.Command
    RCU_IGNITE_PAD_BOX2: RCUCommand.Command
    RCU_KILL_PAD_BOX1: RCUCommand.Command
    RCU_KILL_PAD_BOX2: RCUCommand.Command
    RCU_LAST: RCUCommand.Command
    RCU_NONE: RCUCommand.Command
    RCU_OPEN_AC1: RCUCommand.Command
    RCU_OPEN_AC2: RCUCommand.Command
    RCU_OPEN_PBV1: RCUCommand.Command
    RCU_OPEN_PBV2: RCUCommand.Command
    RCU_OPEN_PBV3: RCUCommand.Command
    RCU_OPEN_SOL1: RCUCommand.Command
    RCU_OPEN_SOL2: RCUCommand.Command
    RCU_OPEN_SOL3: RCUCommand.Command
    RCU_OPEN_SOL4: RCUCommand.Command
    RCU_OPEN_SOL5: RCUCommand.Command
    RCU_OPEN_SOL6: RCUCommand.Command
    RCU_OPEN_SOL7: RCUCommand.Command
    RCU_OPEN_SOL8A: RCUCommand.Command
    RCU_OPEN_SOL8B: RCUCommand.Command
    RCU_TARE_NOS1_LOAD_CELL: RCUCommand.Command
    RCU_TARE_NOS2_LOAD_CELL: RCUCommand.Command
    command_enum: RCUCommand.Command
    command_param: int
    def __init__(self, command_enum: _Optional[_Union[RCUCommand.Command, str]] = ..., command_param: _Optional[int] = ...) -> None: ...

class SOBCommand(_message.Message):
    __slots__ = ["command_enum", "command_param"]
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    COMMAND_ENUM_FIELD_NUMBER: _ClassVar[int]
    COMMAND_PARAM_FIELD_NUMBER: _ClassVar[int]
    SOB_CALIBRATE_LOAD_CELL: SOBCommand.Command
    SOB_FAST_SAMPLE_IR: SOBCommand.Command
    SOB_LAST: SOBCommand.Command
    SOB_NONE: SOBCommand.Command
    SOB_SLOW_SAMPLE_IR: SOBCommand.Command
    SOB_TARE_LOAD_CELL: SOBCommand.Command
    command_enum: SOBCommand.Command
    command_param: int
    def __init__(self, command_enum: _Optional[_Union[SOBCommand.Command, str]] = ..., command_param: _Optional[int] = ...) -> None: ...
