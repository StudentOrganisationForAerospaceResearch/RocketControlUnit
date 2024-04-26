
# General imports =================================================================================
from enum import Enum
import json
import os
from typing import Dict, Tuple
import multiprocessing as mp
import time

# Project specific imports ========================================================================
dirname, _ = os.path.split(os.path.abspath(__file__))
import sys
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend', 'proto/Python'))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend'))

from src.ThreadManager import THREAD_MESSAGE_DB_WRITE, THREAD_MESSAGE_KILL, THREAD_MESSAGE_LOAD_CELL_COMMAND, THREAD_MESSAGE_LOAD_CELL_VOLTAGE, WorkQ_Message
from src.support.CommonLogger import logger
import proto.Python.CoreProto_pb2 as ProtoCore


# Class Definitions ===============================================================================
class LoadCellHandler():
    
    class State(Enum):
        CONVERT_MASS = 0
        WAIT_FOR_CALI_VOLTAGE = 1
        WAIT_FOR_TARE_MASS = 2

    def __init__(self, load_cell_name: str, message_handler_workq: mp.Queue):
        self.load_cell_name = load_cell_name
        self.message_handler_workq = message_handler_workq
        self.reset()

    def reset(self):
        """
        Reset the load cell handler
        """
        self.tare_offset = 0
        self.cali_slope = 1
        self.state = self.State.CONVERT_MASS
        self.voltage_offset = 0
        self.calibration_points = []
        self._request_stored_calibration()

    def cancel_new_calibration(self):
        """
        If a cancel calibration command is received from the DB
        discard the current calibration points
        """
        self.calibration_points = []
        self.state = self.State.CONVERT_MASS

    def _request_stored_calibration(self):
        """
        Request the last calibration values from the database.
        """
        pass
        # TODO: Send the new calibration slope to the DB
        # self.message_handler_workq.put(
        # )

    def set_calibration_slope(self, slope: float):
        """
        Set the calibration slope to the given value
        """
        self.cali_slope = slope

    def _convert_voltage_to_mass(self, raw_voltage: float) -> float:
        """
        Convert the raw voltage from the serial handler
        to a mass value to send to the database.

        Parameters:
            voltage (float):
                The voltage reading to be calibrated.

        Returns:
            float: 
                The calibrated weight corresponding to the voltage reading.
        """
        return (raw_voltage - self.voltage_offset) * self.cali_slope - self.tare_offset
    
    def add_calibration_mass(self, mass: float):
        """
        Add a calibration point to the local slope
        and puts the load cell handler into a wait state
        to wait for a voltage that matches the mass
        """
        self.current_cali_mass = mass
        self.state = self.State.WAIT_FOR_CALI_VOLTAGE

    def _add_calibration_voltage(self, voltage: float):
        """
        Add a calibration point to for the voltage received
        to match the last calibration mass,
        and puts the load cell handler into the convert mass state
        without updating the slope
        """
        self.calibration_points.append((self.current_cali_mass, voltage))
        self.current_cali_mass = 0
        self.state = self.State.CONVERT_MASS

    def consume_incoming_voltage(self, raw_voltage: float) -> float:
        """
        Convert the raw voltage to a mass value or add a calibration
        point based on the current state
        """
        if self.state == self.State.CONVERT_MASS:
            pass
        elif self.state == self.State.WAIT_FOR_CALI_VOLTAGE:
            self._add_calibration_voltage(raw_voltage)
        elif self.state == self.State.WAIT_FOR_TARE_MASS:
            self.tare_mass(self._convert_voltage_to_mass(raw_voltage))
        
        # This function will always return mass, even while calibrating
        # if calibrating the mass will use the previous/current slope instead
        # of the one being calculated.
        return self._convert_voltage_to_mass(raw_voltage)
        
    def finalize(self):
        """
        Perform final calculations for calibration and update the slope
        used to calculate the slope used by the load cell to get corrected mass.
        """
        if not self.calibration_points:
            return
        masses = [x[0] for x in self.calibration_points]
        voltages = [x[1] for x in self.calibration_points]
        mass_mean = sum(masses) / len(masses)
        voltage_mean = sum(voltages) / len(voltages)
        numerator = sum((mass - mass_mean) * ((voltage) - voltage_mean) for mass, voltage in zip(masses, voltages))
        denominator = sum((mass - mass_mean) ** 2 for mass in masses)
        slope = numerator/ denominator
        self.set_calibration_slope(slope)
        self.calibration_points = []
        self.current_state = self.State.CONVERT_MASS
        # TODO: Send the new calibration slope to the DB
        # self.message_handler_workq.put(
        # )

    def tare_mass(self, tare_mass: float):
        """
        Set the tare offset value to the current mass

        Parameters:
            tare_mass (float): 
                The mass to set as the tare offset.
        """
        self.tare_offset = tare_mass

# Procedures ======================================================================================

def get_voltage_and_load_cell_json(json_str: str) -> Tuple[float, str]:
    """
    Extract the voltage and load cell name from the json string

    Args:
        json_str (str):
            The json string to extract the voltage and load cell name from.

    Returns:
        Tuple[float, str]:
            The voltage and load cell name extracted from the json string.
    """

    json_data = json.loads(json_str)
    if len(list(json_data.keys())) < 3:
        logger.warning(f"Received, poorly formed json: {json_data}")
        return None, None

    load_cell = list(json_data.keys())[2]
    voltages = []
    load_cell_names = []

    if load_cell == "nosLoadCell":
        load_cell_names.append("NOS1")
        voltages.append(json_data[load_cell]["nos1Mass"]) # These keys get converted to a weird value
        load_cell_names.append("NOS2")
        voltages.append(json_data[load_cell]["nos2Mass"])
    elif load_cell == "launchRailLoadCell":
        load_cell_names.append("ROCKET")
        voltages.append(json_data[load_cell]["rocketMass"])

    return voltages, load_cell_names

def load_cell_thread(thread_name: str, db_workq: mp.Queue, message_handler_workq: mp.Queue):
    """
    The main loop of the database handler. It subscribes to the CommandMessage collection
    """
    # This log line should be removed once the pi core issue is solved
    logger.info(f"Loadcell process: {os.getpid()}")
    # Sleep to allow time to connect to the database as
    # loadcell needs a connection in order to get its initial values.
    time.sleep(2)
    load_cells = {}
    load_cells["ROCKET"] = LoadCellHandler("ROCKET", message_handler_workq)
    load_cells["NOS1"] = LoadCellHandler("NOS1", message_handler_workq)
    load_cells["NOS2"] = LoadCellHandler("NOS2", message_handler_workq)
    logger.success(f"Successfully initialized load cell thread")

    while 1:
        # If there is any workq messages, process them
        if not process_workq_message(db_workq.get(block=True), load_cells, message_handler_workq):
            return
        
def process_workq_message(message: WorkQ_Message, load_cells: Dict[str, LoadCellHandler], message_handler_workq: mp.Queue) -> bool:
    """
    Process the message from the workq.

    Args:
        message (WorkQ_Message):
            The message from the workq.
    """
    logger.debug(f"Processing load cell workq message: {message.message_type}")
    messageID = message.message_type

    if messageID == THREAD_MESSAGE_KILL:
        logger.debug(f"Killing database thread")
        return False
    elif messageID == THREAD_MESSAGE_LOAD_CELL_VOLTAGE:   
        logger.debug(f"Received load cell information for {message.message[0]}")
        voltages, load_cell_names = get_voltage_and_load_cell_json(message.message[1])

        db_load_cell_package = {}
        db_load_cell_package["source"] = "LOADCELL"
        db_load_cell_package["target"] = "RCU"
        if "ROCKET" in load_cell_names:
            rocket_mass = load_cells["ROCKET"].consume_incoming_voltage(voltages[0])
            db_load_cell_package["launchRailLoadCell"] = {}
            db_load_cell_package["launchRailLoadCell"]["rocketMass"] = rocket_mass

        elif "NOS1" in load_cell_names:
            nos1_mass = load_cells["NOS1"].consume_incoming_voltage(voltages[0])
            nos2_mass = load_cells["NOS2"].consume_incoming_voltage(voltages[1])
            db_load_cell_package["nosLoadCell"] = {}
            db_load_cell_package["nosLoadCell"]["nos1Mass"] = nos1_mass
            db_load_cell_package["nosLoadCell"]["nos2Mass"] = nos2_mass

        # Send the loadcell data to the database
        message_handler_workq.put(
            WorkQ_Message("loadcell", "database", THREAD_MESSAGE_DB_WRITE, (ProtoCore.MessageID.MSG_TELEMETRY, json.dumps(db_load_cell_package)))
        )
        return True
    elif messageID == THREAD_MESSAGE_LOAD_CELL_COMMAND:
        logger.debug(f"Received load cell command: {message.message[0]}")
        if message.message[0] == "CALIBRATE":
            load_cells[message.message[1]].cancel_new_calibration()
        elif message.message[0] == "TARE":
            load_cells[message.message[1]].tare_mass(message.message[2])
        elif message.message[0] == "CANCEL":
            load_cells[message.message[1]].add_calibration_mass(message.message[2])
        elif message.message[0] == "FINISH":
            load_cells[message.message[1]].finalize()
        return True
    return True

# if __name__ == "__main__":
#     # Instantiate a calibration load cell
#     load_cell = LoadCellHandler("test", None)


#     print(f"initial mass (3v): {load_cell.consume_incoming_voltage(3)}")
#     print(f"initial slope: {load_cell.cali_slope}")


#     # Test collecting calibration points
#     print(f"points: {load_cell.calibration_points}")
#     load_cell.add_calibration_mass(0.0)
#     load_cell.consume_incoming_voltage(3)
#     print(f"points: {load_cell.calibration_points}")
#     load_cell.add_calibration_mass(1)
#     load_cell.consume_incoming_voltage(5)
#     print(f"points: {load_cell.calibration_points}")
#     load_cell.add_calibration_mass(2)
#     load_cell.consume_incoming_voltage(6)
#     print(f"points: {load_cell.calibration_points}")

#     # load_cell.cancel_new_calibration()
#     # load_cell.tare_mass(3)

#     # Finalize calibration
#     load_cell.finalize()
#     print(f"points: {load_cell.calibration_points}")

#     print(f"final mass (3v): {load_cell.consume_incoming_voltage(3)}")
#     print(f"final slope: {load_cell.cali_slope}")
