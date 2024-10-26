import time
from pocketbase import PocketBase
import random
import concurrent.futures
import string

endpoint = "http://127.0.0.1:8090"
admin_email = "danikasvetelj@gmail.com"
admin_password = "Ilmnh&h!Ilmnh&h!"

# Initialize PocketBase
pb = PocketBase(endpoint)

# Authenticate
admin_data = pb.admins.auth_with_password(admin_email, admin_password)

if not admin_data.is_valid:
    print("Authentication failed")
    exit()

battery_data = ["INVALID", "GROUND", "ROCKET"]

random_bool = lambda: random.choice([True, False])
random_int = lambda: random.randint(0, 100)
random_string = lambda length: ''.join(random.choice(string.ascii_letters) for _ in range(length))

random_coord = lambda: {
    "degrees": random_int(),
    "minutes": random_int(),
}

random_gps = lambda: {
    "altitude": random_int(),
    "unit": random_int(),
}

# Define a function for each table
def baro_write():
    pb.collection("Baro").create(
        {
            "baro_pressure": random_int(),
            "baro_temperature": random_int(),
        }
    )


def battery_write():
    pb.collection("Battery").create(
        {
            "voltage": random_int(),
            "power_source": random.choice(battery_data),
        }
    )


def combustion_control_write():
    pb.collection("CombustionControlStatus").create(
        {
            "vent_open": random_int(),
            "drain_open": random_int(),
            "mev_open": random_bool(),
        }
    )


def dmb_pressure_write():
    pb.collection("DmbPressure").create(
        {
            "upper_pv_pressure": random_int(),
        }
    )


def gps_write():
    pb.collection("Gps").create(
        {
            "latitude": random_coord(),
            "longitude": random_coord,
            "antenna_altitude": random_gps(),
            "geo_id_altitude": random_gps(),
            "total_altitude": random_gps(),
            "time": random_int(),
        }
    )


def imu_write():
    pb.collection("Imu").create(
        {
            "accel_x": random_int(),
            "accel_y": random_int(),
            "accel_z": random_int(),
            "gyro_x": random_int(),
            "gyro_y": random_int(),
            "gyro_z": random_int(),
            "mag_x": random_int(),
            "mag_y": random_int(),
            "mag_z": random_int(),
        }
    )


def lr_loadcell_write():
    pb.collection("LaunchRailLoadCell").create(
        {
            "rocket_mass": random_int(),
        }
    )

def nos_load_write():
    pb.collection("NosLoadCell").create(
        {
            "nos1_mass": random_int(),
            "nos2_mass": random_int(),
        }
    )


def pad_box_write():
    pb.collection("PadBoxStatus").create(
        {
            "continuity_1": random_bool(),
            "continuity_2": random_bool(),
            "box1_on": random_bool(),
            "box2_on": random_bool(),
        }
    )


def pbb_pressure_write():
    pb.collection("PbbPressure").create(
        {
            "ib_pressure": random_int(),
            "lower_pv_pressure": random_int(),
        }
    )


def pbb_temperature_write():
    pb.collection("PbbTemperature").create(
        {
            "ib_temperature": random_int(),
            "pv_temperature": random_int(),
        }
    )


def rcu_pressure_write():
    pb.collection("RcuPressure").create(
        {
            "pt1_pressure": random_int(),
            "pt2_pressure": random_int(),
            "pt3_pressure": random_int(),
            "pt4_pressure": random_int(),
        }
    )


def rcu_temperature_write():
    pb.collection("RcuTemperature").create(
        {
            "tc1_temperature": random_int(),
            "tc2_temperature": random_int(),
        }
    )


def relay_status_write():
    pb.collection("RelayStatus").create(
        {
            "ac1_open": random_bool(),
            "ac2_open": random_bool(),
            "pbv1_open": random_bool(),
            "pbv2_open": random_bool(),
            "pbv3_open": random_bool(),
            "sol1_open": random_bool(),
            "sol2_open": random_bool(),
            "sol3_open": random_bool(),
            "sol4_open": random_bool(),
            "sol5_open": random_bool(),
            "sol6_open": random_bool(),
            "sol7_open": random_bool(),
            "sol8a_open": random_bool(),
            "sol8b_open": random_bool(),
        }
    )


def sob_temperature_write():
    pb.collection("SobTemperature").create(
        {
            "tc1_temperature": random_int(),
            "tc2_temperature": random_int(),
        }
    )

def board_status_write():
    pb.collection("BoardStatus").create(
        {
            "dmb_status": random_string(5),
            "pmb_status": random_string(5),
            "daq_status": random_string(5),
            "cam_status": random_string(5),
            "bms_status": random_string(5),
            "fab_status": random_string(5),
            "lrb_status": random_string(5),
        }
    )

# List of functions
functions = [
    baro_write,
    battery_write,
    combustion_control_write,
    dmb_pressure_write,
    gps_write,
    imu_write,
    lr_loadcell_write,
    nos_load_write,
    pad_box_write,
    pbb_pressure_write,
    pbb_temperature_write,
    rcu_pressure_write,
    rcu_temperature_write,
    relay_status_write,
    sob_temperature_write,
    board_status_write,
]

# Create a ThreadPool
executor = concurrent.futures.ThreadPoolExecutor(max_workers=20)

# Run all functions every 3 seconds
while True:
    print("Executing functions...")

    # Start a thread for each function
    for function in functions:
        executor.submit(function)

    # Pause for 3 seconds
    time.sleep(3)