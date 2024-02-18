from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor

class Node(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    NODE_INVALID: _ClassVar[Node]
    NODE_UNKNOWN: _ClassVar[Node]
    NODE_ANY: _ClassVar[Node]
    NODE_RCU: _ClassVar[Node]
    NODE_DMB: _ClassVar[Node]
    NODE_PBB: _ClassVar[Node]
    NODE_SOB: _ClassVar[Node]

class MessageID(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    MSG_INVALID: _ClassVar[MessageID]
    MSG_UNKNOWN: _ClassVar[MessageID]
    MSG_CONTROL: _ClassVar[MessageID]
    MSG_COMMAND: _ClassVar[MessageID]
    MSG_TELEMETRY: _ClassVar[MessageID]
    MSG_MAX_INVALID: _ClassVar[MessageID]

class RocketState(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    DMB_INVALID: _ClassVar[RocketState]
    RS_PRELAUNCH: _ClassVar[RocketState]
    RS_FILL: _ClassVar[RocketState]
    RS_ARM: _ClassVar[RocketState]
    RS_IGNITION: _ClassVar[RocketState]
    RS_LAUNCH: _ClassVar[RocketState]
    RS_BURN: _ClassVar[RocketState]
    RS_COAST: _ClassVar[RocketState]
    RS_DESCENT: _ClassVar[RocketState]
    RS_RECOVERY: _ClassVar[RocketState]
    RS_ABORT: _ClassVar[RocketState]
    RS_TEST: _ClassVar[RocketState]
    RS_NONE: _ClassVar[RocketState]
NODE_INVALID: Node
NODE_UNKNOWN: Node
NODE_ANY: Node
NODE_RCU: Node
NODE_DMB: Node
NODE_PBB: Node
NODE_SOB: Node
MSG_INVALID: MessageID
MSG_UNKNOWN: MessageID
MSG_CONTROL: MessageID
MSG_COMMAND: MessageID
MSG_TELEMETRY: MessageID
MSG_MAX_INVALID: MessageID
DMB_INVALID: RocketState
RS_PRELAUNCH: RocketState
RS_FILL: RocketState
RS_ARM: RocketState
RS_IGNITION: RocketState
RS_LAUNCH: RocketState
RS_BURN: RocketState
RS_COAST: RocketState
RS_DESCENT: RocketState
RS_RECOVERY: RocketState
RS_ABORT: RocketState
RS_TEST: RocketState
RS_NONE: RocketState
