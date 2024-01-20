import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class AltitudeType(_message.Message):
    __slots__ = ["altitude", "unit"]
    ALTITUDE_FIELD_NUMBER: _ClassVar[int]
    UNIT_FIELD_NUMBER: _ClassVar[int]
    altitude: int
    unit: int
    def __init__(self, altitude: _Optional[int] = ..., unit: _Optional[int] = ...) -> None: ...

class Baro(_message.Message):
    __slots__ = ["baro_pressure", "baro_temp"]
    BARO_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    BARO_TEMP_FIELD_NUMBER: _ClassVar[int]
    baro_pressure: int
    baro_temp: int
    def __init__(self, baro_pressure: _Optional[int] = ..., baro_temp: _Optional[int] = ...) -> None: ...

class Battery(_message.Message):
    __slots__ = ["p_source", "volt"]
    class power_source(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = []
    GROUND: Battery.power_source
    INVALID: Battery.power_source
    P_SOURCE_FIELD_NUMBER: _ClassVar[int]
    ROCKET: Battery.power_source
    VOLT_FIELD_NUMBER: _ClassVar[int]
    p_source: Battery.power_source
    volt: int
    def __init__(self, p_source: _Optional[_Union[Battery.power_source, str]] = ..., volt: _Optional[int] = ...) -> None: ...

class CombustionControlStatus(_message.Message):
    __slots__ = ["drain_open", "mev_power_enable", "vent_open"]
    DRAIN_OPEN_FIELD_NUMBER: _ClassVar[int]
    MEV_POWER_ENABLE_FIELD_NUMBER: _ClassVar[int]
    VENT_OPEN_FIELD_NUMBER: _ClassVar[int]
    drain_open: bool
    mev_power_enable: bool
    vent_open: bool
    def __init__(self, vent_open: bool = ..., drain_open: bool = ..., mev_power_enable: bool = ...) -> None: ...

class DMBPressure(_message.Message):
    __slots__ = ["upper_pv_pressure"]
    UPPER_PV_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    upper_pv_pressure: int
    def __init__(self, upper_pv_pressure: _Optional[int] = ...) -> None: ...

class Flash(_message.Message):
    __slots__ = ["logging_rate", "sector_address"]
    LOGGING_RATE_FIELD_NUMBER: _ClassVar[int]
    SECTOR_ADDRESS_FIELD_NUMBER: _ClassVar[int]
    logging_rate: int
    sector_address: int
    def __init__(self, sector_address: _Optional[int] = ..., logging_rate: _Optional[int] = ...) -> None: ...

class GPS(_message.Message):
    __slots__ = ["antenna_alt", "geoidAltitude", "latitude", "longitude", "time", "total_alt"]
    ANTENNA_ALT_FIELD_NUMBER: _ClassVar[int]
    GEOIDALTITUDE_FIELD_NUMBER: _ClassVar[int]
    LATITUDE_FIELD_NUMBER: _ClassVar[int]
    LONGITUDE_FIELD_NUMBER: _ClassVar[int]
    TIME_FIELD_NUMBER: _ClassVar[int]
    TOTAL_ALT_FIELD_NUMBER: _ClassVar[int]
    antenna_alt: AltitudeType
    geoidAltitude: AltitudeType
    latitude: LatLong
    longitude: LatLong
    time: int
    total_alt: AltitudeType
    def __init__(self, latitude: _Optional[_Union[LatLong, _Mapping]] = ..., longitude: _Optional[_Union[LatLong, _Mapping]] = ..., antenna_alt: _Optional[_Union[AltitudeType, _Mapping]] = ..., geoidAltitude: _Optional[_Union[AltitudeType, _Mapping]] = ..., total_alt: _Optional[_Union[AltitudeType, _Mapping]] = ..., time: _Optional[int] = ...) -> None: ...

class IMU(_message.Message):
    __slots__ = ["accelx", "accely", "accelz", "gyrox", "gyroy", "gyroz", "magx", "magy", "magz"]
    ACCELX_FIELD_NUMBER: _ClassVar[int]
    ACCELY_FIELD_NUMBER: _ClassVar[int]
    ACCELZ_FIELD_NUMBER: _ClassVar[int]
    GYROX_FIELD_NUMBER: _ClassVar[int]
    GYROY_FIELD_NUMBER: _ClassVar[int]
    GYROZ_FIELD_NUMBER: _ClassVar[int]
    MAGX_FIELD_NUMBER: _ClassVar[int]
    MAGY_FIELD_NUMBER: _ClassVar[int]
    MAGZ_FIELD_NUMBER: _ClassVar[int]
    accelx: int
    accely: int
    accelz: int
    gyrox: int
    gyroy: int
    gyroz: int
    magx: int
    magy: int
    magz: int
    def __init__(self, accelx: _Optional[int] = ..., accely: _Optional[int] = ..., accelz: _Optional[int] = ..., gyrox: _Optional[int] = ..., gyroy: _Optional[int] = ..., gyroz: _Optional[int] = ..., magx: _Optional[int] = ..., magy: _Optional[int] = ..., magz: _Optional[int] = ...) -> None: ...

class IRTemperature(_message.Message):
    __slots__ = ["ambient_temp", "object_temp"]
    AMBIENT_TEMP_FIELD_NUMBER: _ClassVar[int]
    OBJECT_TEMP_FIELD_NUMBER: _ClassVar[int]
    ambient_temp: int
    object_temp: int
    def __init__(self, ambient_temp: _Optional[int] = ..., object_temp: _Optional[int] = ...) -> None: ...

class LRLoadCell(_message.Message):
    __slots__ = ["rocket_mass"]
    ROCKET_MASS_FIELD_NUMBER: _ClassVar[int]
    rocket_mass: int
    def __init__(self, rocket_mass: _Optional[int] = ...) -> None: ...

class LatLong(_message.Message):
    __slots__ = ["degrees", "minutes"]
    DEGREES_FIELD_NUMBER: _ClassVar[int]
    MINUTES_FIELD_NUMBER: _ClassVar[int]
    degrees: int
    minutes: int
    def __init__(self, degrees: _Optional[int] = ..., minutes: _Optional[int] = ...) -> None: ...

class MEVState(_message.Message):
    __slots__ = ["mev_open"]
    MEV_OPEN_FIELD_NUMBER: _ClassVar[int]
    mev_open: bool
    def __init__(self, mev_open: bool = ...) -> None: ...

class NOSLoadCell(_message.Message):
    __slots__ = ["nos1_mass", "nos2_mass"]
    NOS1_MASS_FIELD_NUMBER: _ClassVar[int]
    NOS2_MASS_FIELD_NUMBER: _ClassVar[int]
    nos1_mass: int
    nos2_mass: int
    def __init__(self, nos1_mass: _Optional[int] = ..., nos2_mass: _Optional[int] = ...) -> None: ...

class PBBPressure(_message.Message):
    __slots__ = ["ib_pressure", "lower_pv_pressure"]
    IB_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    LOWER_PV_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    ib_pressure: int
    lower_pv_pressure: int
    def __init__(self, ib_pressure: _Optional[int] = ..., lower_pv_pressure: _Optional[int] = ...) -> None: ...

class PBBTemp(_message.Message):
    __slots__ = ["ib_temperature", "pv_temperature"]
    IB_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    PV_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    ib_temperature: int
    pv_temperature: int
    def __init__(self, ib_temperature: _Optional[int] = ..., pv_temperature: _Optional[int] = ...) -> None: ...

class PadBoxStatus(_message.Message):
    __slots__ = ["box1_on", "box2_on", "cont1", "cont2"]
    BOX1_ON_FIELD_NUMBER: _ClassVar[int]
    BOX2_ON_FIELD_NUMBER: _ClassVar[int]
    CONT1_FIELD_NUMBER: _ClassVar[int]
    CONT2_FIELD_NUMBER: _ClassVar[int]
    box1_on: bool
    box2_on: bool
    cont1: bool
    cont2: bool
    def __init__(self, cont1: bool = ..., cont2: bool = ..., box1_on: bool = ..., box2_on: bool = ...) -> None: ...

class RCUPressure(_message.Message):
    __slots__ = ["pt1_pressure", "pt2_pressure", "pt3_pressure", "pt4_pressure"]
    PT1_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT2_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT3_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT4_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    pt1_pressure: int
    pt2_pressure: int
    pt3_pressure: int
    pt4_pressure: int
    def __init__(self, pt1_pressure: _Optional[int] = ..., pt2_pressure: _Optional[int] = ..., pt3_pressure: _Optional[int] = ..., pt4_pressure: _Optional[int] = ...) -> None: ...

class RCUTemp(_message.Message):
    __slots__ = ["tc1_temp", "tc2_temp"]
    TC1_TEMP_FIELD_NUMBER: _ClassVar[int]
    TC2_TEMP_FIELD_NUMBER: _ClassVar[int]
    tc1_temp: int
    tc2_temp: int
    def __init__(self, tc1_temp: _Optional[int] = ..., tc2_temp: _Optional[int] = ...) -> None: ...

class RelayStatus(_message.Message):
    __slots__ = ["ac1_open", "ac2_open", "pbv1_open", "pbv2_open", "pbv3_open", "sol1_open", "sol2_open", "sol3_open", "sol4_open", "sol5_open", "sol6_open", "sol7_open", "sol8a_open", "sol8b_open"]
    AC1_OPEN_FIELD_NUMBER: _ClassVar[int]
    AC2_OPEN_FIELD_NUMBER: _ClassVar[int]
    PBV1_OPEN_FIELD_NUMBER: _ClassVar[int]
    PBV2_OPEN_FIELD_NUMBER: _ClassVar[int]
    PBV3_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL1_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL2_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL3_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL4_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL5_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL6_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL7_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL8A_OPEN_FIELD_NUMBER: _ClassVar[int]
    SOL8B_OPEN_FIELD_NUMBER: _ClassVar[int]
    ac1_open: bool
    ac2_open: bool
    pbv1_open: bool
    pbv2_open: bool
    pbv3_open: bool
    sol1_open: bool
    sol2_open: bool
    sol3_open: bool
    sol4_open: bool
    sol5_open: bool
    sol6_open: bool
    sol7_open: bool
    sol8a_open: bool
    sol8b_open: bool
    def __init__(self, ac1_open: bool = ..., ac2_open: bool = ..., pbv1_open: bool = ..., pbv2_open: bool = ..., pbv3_open: bool = ..., sol1_open: bool = ..., sol2_open: bool = ..., sol3_open: bool = ..., sol4_open: bool = ..., sol5_open: bool = ..., sol6_open: bool = ..., sol7_open: bool = ..., sol8a_open: bool = ..., sol8b_open: bool = ...) -> None: ...

class SOBTemp(_message.Message):
    __slots__ = ["tc1_temp", "tc2_temp"]
    TC1_TEMP_FIELD_NUMBER: _ClassVar[int]
    TC2_TEMP_FIELD_NUMBER: _ClassVar[int]
    tc1_temp: int
    tc2_temp: int
    def __init__(self, tc1_temp: _Optional[int] = ..., tc2_temp: _Optional[int] = ...) -> None: ...

class TelemetryMessage(_message.Message):
    __slots__ = ["baro", "bat", "coord", "flashInfo", "gpio", "imu", "irtemp", "lr", "message_id", "mevstate", "nos", "padbox", "pressdmb", "presspbb", "pressrcu", "relay", "source", "target", "temppbb", "temprcu", "tempsob"]
    BARO_FIELD_NUMBER: _ClassVar[int]
    BAT_FIELD_NUMBER: _ClassVar[int]
    COORD_FIELD_NUMBER: _ClassVar[int]
    FLASHINFO_FIELD_NUMBER: _ClassVar[int]
    GPIO_FIELD_NUMBER: _ClassVar[int]
    IMU_FIELD_NUMBER: _ClassVar[int]
    IRTEMP_FIELD_NUMBER: _ClassVar[int]
    LR_FIELD_NUMBER: _ClassVar[int]
    MESSAGE_ID_FIELD_NUMBER: _ClassVar[int]
    MEVSTATE_FIELD_NUMBER: _ClassVar[int]
    NOS_FIELD_NUMBER: _ClassVar[int]
    PADBOX_FIELD_NUMBER: _ClassVar[int]
    PRESSDMB_FIELD_NUMBER: _ClassVar[int]
    PRESSPBB_FIELD_NUMBER: _ClassVar[int]
    PRESSRCU_FIELD_NUMBER: _ClassVar[int]
    RELAY_FIELD_NUMBER: _ClassVar[int]
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    TEMPPBB_FIELD_NUMBER: _ClassVar[int]
    TEMPRCU_FIELD_NUMBER: _ClassVar[int]
    TEMPSOB_FIELD_NUMBER: _ClassVar[int]
    baro: Baro
    bat: Battery
    coord: GPS
    flashInfo: Flash
    gpio: CombustionControlStatus
    imu: IMU
    irtemp: IRTemperature
    lr: LRLoadCell
    message_id: int
    mevstate: MEVState
    nos: NOSLoadCell
    padbox: PadBoxStatus
    pressdmb: DMBPressure
    presspbb: PBBPressure
    pressrcu: RCUPressure
    relay: RelayStatus
    source: _CoreProto_pb2.Node
    target: _CoreProto_pb2.Node
    temppbb: PBBTemp
    temprcu: RCUTemp
    tempsob: SOBTemp
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., message_id: _Optional[int] = ..., coord: _Optional[_Union[GPS, _Mapping]] = ..., baro: _Optional[_Union[Baro, _Mapping]] = ..., imu: _Optional[_Union[IMU, _Mapping]] = ..., bat: _Optional[_Union[Battery, _Mapping]] = ..., flashInfo: _Optional[_Union[Flash, _Mapping]] = ..., pressdmb: _Optional[_Union[DMBPressure, _Mapping]] = ..., presspbb: _Optional[_Union[PBBPressure, _Mapping]] = ..., temppbb: _Optional[_Union[PBBTemp, _Mapping]] = ..., gpio: _Optional[_Union[CombustionControlStatus, _Mapping]] = ..., pressrcu: _Optional[_Union[RCUPressure, _Mapping]] = ..., temprcu: _Optional[_Union[RCUTemp, _Mapping]] = ..., nos: _Optional[_Union[NOSLoadCell, _Mapping]] = ..., relay: _Optional[_Union[RelayStatus, _Mapping]] = ..., padbox: _Optional[_Union[PadBoxStatus, _Mapping]] = ..., lr: _Optional[_Union[LRLoadCell, _Mapping]] = ..., tempsob: _Optional[_Union[SOBTemp, _Mapping]] = ..., irtemp: _Optional[_Union[IRTemperature, _Mapping]] = ..., mevstate: _Optional[_Union[MEVState, _Mapping]] = ...) -> None: ...
