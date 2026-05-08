from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor

class Node(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    NODE_INVALID: _ClassVar[Node]
    NODE_UNKNOWN: _ClassVar[Node]
    NODE_ANY: _ClassVar[Node]
    NODE_FSB: _ClassVar[Node]
    NODE_FCB: _ClassVar[Node]
    NODE_PBB: _ClassVar[Node]
    NODE_LRB: _ClassVar[Node]

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
    RS_PRELAUNCH: _ClassVar[RocketState]
    RS_FILL: _ClassVar[RocketState]
    RS_ARM: _ClassVar[RocketState]
    RS_IGNITION: _ClassVar[RocketState]
    RS_LAUNCH: _ClassVar[RocketState]
    RS_BURN: _ClassVar[RocketState]
    RS_COAST: _ClassVar[RocketState]
    RS_BRAKING: _ClassVar[RocketState]
    RS_DESCENT: _ClassVar[RocketState]
    RS_TOUCHDOWN: _ClassVar[RocketState]
    RS_ABORT: _ClassVar[RocketState]
    RS_TEST: _ClassVar[RocketState]
    RS_NONE: _ClassVar[RocketState]
NODE_INVALID: Node
NODE_UNKNOWN: Node
NODE_ANY: Node
NODE_FSB: Node
NODE_FCB: Node
NODE_PBB: Node
NODE_LRB: Node
MSG_INVALID: MessageID
MSG_UNKNOWN: MessageID
MSG_CONTROL: MessageID
MSG_COMMAND: MessageID
MSG_TELEMETRY: MessageID
MSG_MAX_INVALID: MessageID
RS_PRELAUNCH: RocketState
RS_FILL: RocketState
RS_ARM: RocketState
RS_IGNITION: RocketState
RS_LAUNCH: RocketState
RS_BURN: RocketState
RS_COAST: RocketState
RS_BRAKING: RocketState
RS_DESCENT: RocketState
RS_TOUCHDOWN: RocketState
RS_ABORT: RocketState
RS_TEST: RocketState
RS_NONE: RocketState
