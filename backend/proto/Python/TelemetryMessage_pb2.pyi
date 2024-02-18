import CoreProto_pb2 as _CoreProto_pb2
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class TelemetryMessage(_message.Message):
    __slots__ = ("source", "target", "gps", "baro", "imu", "battery", "flash_info", "pressure_dmb", "pressure_pbb", "temperature_pbb", "combustion_control_status", "pressure_rcu", "temperature_rcu", "nos_mass", "relay_status", "padbox_status", "rocket_mass", "temperature_sob")
    SOURCE_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    GPS_FIELD_NUMBER: _ClassVar[int]
    BARO_FIELD_NUMBER: _ClassVar[int]
    IMU_FIELD_NUMBER: _ClassVar[int]
    BATTERY_FIELD_NUMBER: _ClassVar[int]
    FLASH_INFO_FIELD_NUMBER: _ClassVar[int]
    PRESSURE_DMB_FIELD_NUMBER: _ClassVar[int]
    PRESSURE_PBB_FIELD_NUMBER: _ClassVar[int]
    TEMPERATURE_PBB_FIELD_NUMBER: _ClassVar[int]
    COMBUSTION_CONTROL_STATUS_FIELD_NUMBER: _ClassVar[int]
    PRESSURE_RCU_FIELD_NUMBER: _ClassVar[int]
    TEMPERATURE_RCU_FIELD_NUMBER: _ClassVar[int]
    NOS_MASS_FIELD_NUMBER: _ClassVar[int]
    RELAY_STATUS_FIELD_NUMBER: _ClassVar[int]
    PADBOX_STATUS_FIELD_NUMBER: _ClassVar[int]
    ROCKET_MASS_FIELD_NUMBER: _ClassVar[int]
    TEMPERATURE_SOB_FIELD_NUMBER: _ClassVar[int]
    source: _CoreProto_pb2.Node
    target: _CoreProto_pb2.Node
    gps: Gps
    baro: Baro
    imu: Imu
    battery: Battery
    flash_info: Flash
    pressure_dmb: DmbPressure
    pressure_pbb: PbbPressure
    temperature_pbb: PbbTemperature
    combustion_control_status: CombustionControlStatus
    pressure_rcu: RcuPressure
    temperature_rcu: RcuTemperature
    nos_mass: NosLoadCell
    relay_status: RelayStatus
    padbox_status: PadBoxStatus
    rocket_mass: LaunchRailLoadCell
    temperature_sob: SobTemperature
    def __init__(self, source: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., target: _Optional[_Union[_CoreProto_pb2.Node, str]] = ..., gps: _Optional[_Union[Gps, _Mapping]] = ..., baro: _Optional[_Union[Baro, _Mapping]] = ..., imu: _Optional[_Union[Imu, _Mapping]] = ..., battery: _Optional[_Union[Battery, _Mapping]] = ..., flash_info: _Optional[_Union[Flash, _Mapping]] = ..., pressure_dmb: _Optional[_Union[DmbPressure, _Mapping]] = ..., pressure_pbb: _Optional[_Union[PbbPressure, _Mapping]] = ..., temperature_pbb: _Optional[_Union[PbbTemperature, _Mapping]] = ..., combustion_control_status: _Optional[_Union[CombustionControlStatus, _Mapping]] = ..., pressure_rcu: _Optional[_Union[RcuPressure, _Mapping]] = ..., temperature_rcu: _Optional[_Union[RcuTemperature, _Mapping]] = ..., nos_mass: _Optional[_Union[NosLoadCell, _Mapping]] = ..., relay_status: _Optional[_Union[RelayStatus, _Mapping]] = ..., padbox_status: _Optional[_Union[PadBoxStatus, _Mapping]] = ..., rocket_mass: _Optional[_Union[LaunchRailLoadCell, _Mapping]] = ..., temperature_sob: _Optional[_Union[SobTemperature, _Mapping]] = ...) -> None: ...

class Gps(_message.Message):
    __slots__ = ("latitude", "longitude", "antenna_altitude", "geo_id_altitude", "total_altitude", "time")
    LATITUDE_FIELD_NUMBER: _ClassVar[int]
    LONGITUDE_FIELD_NUMBER: _ClassVar[int]
    ANTENNA_ALTITUDE_FIELD_NUMBER: _ClassVar[int]
    GEO_ID_ALTITUDE_FIELD_NUMBER: _ClassVar[int]
    TOTAL_ALTITUDE_FIELD_NUMBER: _ClassVar[int]
    TIME_FIELD_NUMBER: _ClassVar[int]
    latitude: CoordinateType
    longitude: CoordinateType
    antenna_altitude: AltitudeType
    geo_id_altitude: AltitudeType
    total_altitude: AltitudeType
    time: int
    def __init__(self, latitude: _Optional[_Union[CoordinateType, _Mapping]] = ..., longitude: _Optional[_Union[CoordinateType, _Mapping]] = ..., antenna_altitude: _Optional[_Union[AltitudeType, _Mapping]] = ..., geo_id_altitude: _Optional[_Union[AltitudeType, _Mapping]] = ..., total_altitude: _Optional[_Union[AltitudeType, _Mapping]] = ..., time: _Optional[int] = ...) -> None: ...

class CoordinateType(_message.Message):
    __slots__ = ("degrees", "minutes")
    DEGREES_FIELD_NUMBER: _ClassVar[int]
    MINUTES_FIELD_NUMBER: _ClassVar[int]
    degrees: int
    minutes: int
    def __init__(self, degrees: _Optional[int] = ..., minutes: _Optional[int] = ...) -> None: ...

class AltitudeType(_message.Message):
    __slots__ = ("altitude", "unit")
    ALTITUDE_FIELD_NUMBER: _ClassVar[int]
    UNIT_FIELD_NUMBER: _ClassVar[int]
    altitude: int
    unit: int
    def __init__(self, altitude: _Optional[int] = ..., unit: _Optional[int] = ...) -> None: ...

class Baro(_message.Message):
    __slots__ = ("baro_pressure", "baro_temperature")
    BARO_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    BARO_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    baro_pressure: int
    baro_temperature: int
    def __init__(self, baro_pressure: _Optional[int] = ..., baro_temperature: _Optional[int] = ...) -> None: ...

class Imu(_message.Message):
    __slots__ = ("accel_x", "accel_y", "accel_z", "gyro_x", "gyro_y", "gyro_z", "mag_x", "mag_y", "mag_z")
    ACCEL_X_FIELD_NUMBER: _ClassVar[int]
    ACCEL_Y_FIELD_NUMBER: _ClassVar[int]
    ACCEL_Z_FIELD_NUMBER: _ClassVar[int]
    GYRO_X_FIELD_NUMBER: _ClassVar[int]
    GYRO_Y_FIELD_NUMBER: _ClassVar[int]
    GYRO_Z_FIELD_NUMBER: _ClassVar[int]
    MAG_X_FIELD_NUMBER: _ClassVar[int]
    MAG_Y_FIELD_NUMBER: _ClassVar[int]
    MAG_Z_FIELD_NUMBER: _ClassVar[int]
    accel_x: int
    accel_y: int
    accel_z: int
    gyro_x: int
    gyro_y: int
    gyro_z: int
    mag_x: int
    mag_y: int
    mag_z: int
    def __init__(self, accel_x: _Optional[int] = ..., accel_y: _Optional[int] = ..., accel_z: _Optional[int] = ..., gyro_x: _Optional[int] = ..., gyro_y: _Optional[int] = ..., gyro_z: _Optional[int] = ..., mag_x: _Optional[int] = ..., mag_y: _Optional[int] = ..., mag_z: _Optional[int] = ...) -> None: ...

class Battery(_message.Message):
    __slots__ = ("power_source", "voltage")
    class PowerSource(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        INVALID: _ClassVar[Battery.PowerSource]
        GROUND: _ClassVar[Battery.PowerSource]
        ROCKET: _ClassVar[Battery.PowerSource]
    INVALID: Battery.PowerSource
    GROUND: Battery.PowerSource
    ROCKET: Battery.PowerSource
    POWER_SOURCE_FIELD_NUMBER: _ClassVar[int]
    VOLTAGE_FIELD_NUMBER: _ClassVar[int]
    power_source: Battery.PowerSource
    voltage: int
    def __init__(self, power_source: _Optional[_Union[Battery.PowerSource, str]] = ..., voltage: _Optional[int] = ...) -> None: ...

class Flash(_message.Message):
    __slots__ = ("sector_address", "logging_rate")
    SECTOR_ADDRESS_FIELD_NUMBER: _ClassVar[int]
    LOGGING_RATE_FIELD_NUMBER: _ClassVar[int]
    sector_address: int
    logging_rate: int
    def __init__(self, sector_address: _Optional[int] = ..., logging_rate: _Optional[int] = ...) -> None: ...

class DmbPressure(_message.Message):
    __slots__ = ("upper_pv_pressure",)
    UPPER_PV_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    upper_pv_pressure: int
    def __init__(self, upper_pv_pressure: _Optional[int] = ...) -> None: ...

class PbbPressure(_message.Message):
    __slots__ = ("ib_pressure", "lower_pv_pressure")
    IB_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    LOWER_PV_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    ib_pressure: int
    lower_pv_pressure: int
    def __init__(self, ib_pressure: _Optional[int] = ..., lower_pv_pressure: _Optional[int] = ...) -> None: ...

class PbbTemperature(_message.Message):
    __slots__ = ("ib_temperature", "pv_temperature")
    IB_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    PV_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    ib_temperature: int
    pv_temperature: int
    def __init__(self, ib_temperature: _Optional[int] = ..., pv_temperature: _Optional[int] = ...) -> None: ...

class CombustionControlStatus(_message.Message):
    __slots__ = ("vent_open", "drain_open", "mev_open")
    VENT_OPEN_FIELD_NUMBER: _ClassVar[int]
    DRAIN_OPEN_FIELD_NUMBER: _ClassVar[int]
    MEV_OPEN_FIELD_NUMBER: _ClassVar[int]
    vent_open: bool
    drain_open: bool
    mev_open: bool
    def __init__(self, vent_open: bool = ..., drain_open: bool = ..., mev_open: bool = ...) -> None: ...

class RcuPressure(_message.Message):
    __slots__ = ("pt1_pressure", "pt2_pressure", "pt3_pressure", "pt4_pressure")
    PT1_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT2_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT3_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    PT4_PRESSURE_FIELD_NUMBER: _ClassVar[int]
    pt1_pressure: int
    pt2_pressure: int
    pt3_pressure: int
    pt4_pressure: int
    def __init__(self, pt1_pressure: _Optional[int] = ..., pt2_pressure: _Optional[int] = ..., pt3_pressure: _Optional[int] = ..., pt4_pressure: _Optional[int] = ...) -> None: ...

class RcuTemperature(_message.Message):
    __slots__ = ("tc1_temperature", "tc2_temperature")
    TC1_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    TC2_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    tc1_temperature: int
    tc2_temperature: int
    def __init__(self, tc1_temperature: _Optional[int] = ..., tc2_temperature: _Optional[int] = ...) -> None: ...

class NosLoadCell(_message.Message):
    __slots__ = ("nos1_mass", "nos2_mass")
    NOS1_MASS_FIELD_NUMBER: _ClassVar[int]
    NOS2_MASS_FIELD_NUMBER: _ClassVar[int]
    nos1_mass: int
    nos2_mass: int
    def __init__(self, nos1_mass: _Optional[int] = ..., nos2_mass: _Optional[int] = ...) -> None: ...

class RelayStatus(_message.Message):
    __slots__ = ("ac1_open", "ac2_open", "pbv1_open", "pbv2_open", "pbv3_open", "sol1_open", "sol2_open", "sol3_open", "sol4_open", "sol5_open", "sol6_open", "sol7_open", "sol8a_open", "sol8b_open")
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

class PadBoxStatus(_message.Message):
    __slots__ = ("continuity_1", "continuity_2", "box1_on", "box2_on")
    CONTINUITY_1_FIELD_NUMBER: _ClassVar[int]
    CONTINUITY_2_FIELD_NUMBER: _ClassVar[int]
    BOX1_ON_FIELD_NUMBER: _ClassVar[int]
    BOX2_ON_FIELD_NUMBER: _ClassVar[int]
    continuity_1: bool
    continuity_2: bool
    box1_on: bool
    box2_on: bool
    def __init__(self, continuity_1: bool = ..., continuity_2: bool = ..., box1_on: bool = ..., box2_on: bool = ...) -> None: ...

class LaunchRailLoadCell(_message.Message):
    __slots__ = ("rocket_mass",)
    ROCKET_MASS_FIELD_NUMBER: _ClassVar[int]
    rocket_mass: int
    def __init__(self, rocket_mass: _Optional[int] = ...) -> None: ...

class SobTemperature(_message.Message):
    __slots__ = ("tc1_temperature", "tc2_temperature")
    TC1_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    TC2_TEMPERATURE_FIELD_NUMBER: _ClassVar[int]
    tc1_temperature: int
    tc2_temperature: int
    def __init__(self, tc1_temperature: _Optional[int] = ..., tc2_temperature: _Optional[int] = ...) -> None: ...
