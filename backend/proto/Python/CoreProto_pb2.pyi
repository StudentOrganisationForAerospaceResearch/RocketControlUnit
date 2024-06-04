from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor
DMB_INVALID: RocketState
MSG_COMMAND: MessageID
MSG_CONTROL: MessageID
MSG_INVALID: MessageID
MSG_MAX_INVALID: MessageID
MSG_TELEMETRY: MessageID
MSG_UNKNOWN: MessageID
NODE_ANY: Node
NODE_DMB: Node
NODE_INVALID: Node
NODE_PBB: Node
NODE_RCU: Node
NODE_SOB: Node
NODE_UNKNOWN: Node
RS_ABORT: RocketState
RS_ARM: RocketState
RS_BURN: RocketState
RS_COAST: RocketState
RS_DESCENT: RocketState
RS_FILL: RocketState
RS_IGNITION: RocketState
RS_LAUNCH: RocketState
RS_NONE: RocketState
RS_PRELAUNCH: RocketState
RS_RECOVERY: RocketState
RS_TEST: RocketState

class Node(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = []

class MessageID(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = []

class RocketState(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = []
