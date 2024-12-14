# General imports =================================================================================
import json
import os
import enum
import multiprocessing as mp
import threading
import time, random
import serial           # You'll need to run `pip install pyserial`
from cobs import cobs   # pip install cobs
import google.protobuf.message as Message
from queue import Queue

# Project specific imports ========================================================================
import proto.Python.CoreProto_pb2 as ProtoCore
import proto.Python.TelemetryMessage_pb2 as TelemetryProto
import proto.Python.ControlMessage_pb2 as ControlProto
from proto.Python.ControlMessage_pb2 import AckNack


from src.support.Codec import Codec
from src.support.ProtobufParser import ProtobufParser
from src.support.CommonLogger import logger

from src.StateMachineManager import StateMachineManager
from src.ThreadManager import THREAD_MESSAGE_DB_WRITE, THREAD_MESSAGE_HEARTBEAT_SERIAL, THREAD_MESSAGE_KILL, THREAD_MESSAGE_LOAD_CELL_VOLTAGE, THREAD_MESSAGE_SERIAL_WRITE, WorkQ_Message
from src.Utils import Utils as utl


# Constants ========================================================================================
MIN_SERIAL_MESSAGE_LENGTH = 6

UART_SERIAL_PORT = "/dev/ttyAMA0"
RADIO_SERIAL_PORT = "/dev/ttyUSB0"

# Data Classes =====================================================================================
class SerialDevices(enum.Enum):
    UART = 1
    RADIO = 2


# Class Definitions ===============================================================================
class SerialHandler():
    def __init__(self, thread_name: str, port: str, baudrate: int, message_handler_workq: mp.Queue, serial_event_queue : mp.Queue, state_change_event_queue: mp.Queue, serial_event: mp.Event, state_change_event: mp.Event):
        """
        This thread class creates threads to handle 
        incoming and outgoing serial messages over 
        the radio to the DMB and the uart to RCU.

        Args:
            thread_name (str):
                The name of the thread.
            port (str):
                The port of the serial connection.
            baudrate (int):
                The baudrate of the serial connection.
            message_handler_workq (mp.Queue):
                The workq to send messages to the database handler.
        """
        logger.info(f"{thread_name} SerialHandler initializing")
        self.port = port
        self.baudrate = baudrate
        self.thread_name = thread_name
        self.send_message_workq = message_handler_workq    
        self.kill_rx = False
        self.serial_event_queue = serial_event_queue
        self.state_change_event_queue = state_change_event_queue
        self.serial_event = serial_event
        self.state_change_event = state_change_event
        self.current_ser_workq_msg = None
        # Open serial serial port
        try:
            self.serial_port = serial.Serial(port=port, baudrate=baudrate, bytesize=8, parity=serial.PARITY_NONE, timeout=None, stopbits=serial.STOPBITS_ONE)
        except Exception:
            self.serial_port = None
            logger.error(f"Failed to open {thread_name} serial port {port}")
            return
        logger.success(f"Successfully opened {thread_name} serial port {port}")

    def _get_serial_message(self):
        """
        Get the serial message from the serial port.
        """
        try:
            return self.serial_port.read_until(expected = b'\x00', size = None)
        except Exception:
            return None

    def handle_serial_message(self):
        """
        Handle incoming serial messages.

        Args:
            message (bytes):
                the data that was received.
        """
        # Read the serial port
        message = self._get_serial_message()
        
        if message == None:
            return

        # Check message length
        if len(message) < MIN_SERIAL_MESSAGE_LENGTH:
            logger.warning(f"Message from {self.port} too short: {message}")
            return
        
        # Decode, remove 0x00 byte
        try:
            msgId, data = Codec.Decode(message[:-1], len(message) - 1)
        except cobs.DecodeError:
            logger.warning(f"Invalid cobs message from {self.port}")
            return
        
        # Process message according to ID
        if msgId == ProtoCore.MessageID.MSG_TELEMETRY:
            self.process_telemetry_message(data)
        elif msgId == ProtoCore.MessageID.MSG_CONTROL:
            self.process_control_message(data)
        else:
            logger.warning(f"Received invalid MessageID from {self.port}")

    def process_telemetry_message(self, data):
        """
        Process the incoming telemetry message.

        Args:
            data (bytes):
                The data that was received.
        """
        received_message = TelemetryProto.TelemetryMessage()
        # Ensure we received a valid message
        try:
            received_message.ParseFromString(data)
        except Message.DecodeError:
            logger.warning(f"Unable to decode telemetry message: {data}")
            return
        # Ensure the message is intended for us
        if received_message.target == ProtoCore.NODE_RCU or received_message.target == ProtoCore.NODE_ANY:
            telemetry_message_type = received_message.WhichOneof('message')
            logger.debug(f"Received {telemetry_message_type} from {utl.get_node_from_enum(received_message.source)}")
        else:
            logger.debug(f"Received message intended for {utl.get_node_from_enum(received_message.target)}")
            return
        
        json_str = ProtobufParser.parse_serial_to_json(data, ProtoCore.MessageID.MSG_TELEMETRY)

        # Try to check if the received message is load_cell_information
        try:
            json_data = json.loads(json_str)
            if len(list(json_data.keys())) < 3:
                logger.warning(f"Json is poorly formed: {json_data}")
                return
            # Check if the json data is load cell information
            # if it does send it to the load cell thread instead of the database
            if ("launchRailLoadCell" in json_data.keys()) or ("nosLoadCell" in json_data.keys()):
                self.send_message_workq.put(WorkQ_Message(self.thread_name,
                                            'loadcell',
                                            THREAD_MESSAGE_LOAD_CELL_VOLTAGE, 
                                            (
                                             list(json_data.keys())[2],
                                             json_str
                                             )
                                           ))
                return
        except Exception:
            pass


        self.send_message_workq.put(WorkQ_Message(self.thread_name, 'database', THREAD_MESSAGE_DB_WRITE, (ProtoCore.MessageID.MSG_TELEMETRY, json_str)))
        
    def mock_received_message(self):
        """
        Mock receiving message from the DMB. 
        """
        msg = ControlProto.ControlMessage()
        mock_msg = [0, 1 ]
        choice = random.choice(mock_msg)
        if choice == 0:
            msg.nack = AckNack()
            msg.nack.acking_msg_id = 0
        else:
            msg.ack = AckNack()
            msg.ack.acking_msg_id = 1

        return msg
   
    def process_control_message(self, data):
        """
        Process the incoming control message.

        Args:
            data (bytes):
                The data that was received.
        """
        received_message = self.mock_received_message()
        #-------------UNCOMMENT THE TWO LINES BELOW ONCE THE BOARD IS OBTAINED--------------
        # received_message = ControlProto.ControlMessage()
        # Ensure we received a valid message
        # try:
        #     received_message.ParseFromString(data)
        # except Message.DecodeError:
        #     logger.warning(f"Unable to decode control message: {data}")
        #     return
        # # Ensure the message is intended for us
        # if received_message.target == ProtoCore.NODE_RCU or received_message.target == ProtoCore.NODE_ANY:
        #     control_message_type = received_message.WhichOneof('message')
        #     logger.debug(f"Received {control_message_type} from {utl.get_node_from_enum(received_message.source)}")
        # else:
        #     logger.debug(f"Received message intended for {utl.get_node_from_enum(received_message.target)}")
        #     return
        
        #Check to see if it's nak or ack - Might be a better way to check for ACK vs NAK
        if received_message.ack:
            self.serial_event_queue.put("ACK")
        elif received_message.nack:
            self.serial_event_queue.put("NAK")
        self.serial_event.set()

        logger.info(f"Mock sending to database thread")
        #-------------UNCOMMENT THE TWO LINES BELOW ONCE THE BOARD IS OBTAINED--------------

        # json_str = ProtobufParser.parse_serial_to_json(data, ProtoCore.MessageID.MSG_CONTROL)

        # self.send_message_workq.put(WorkQ_Message(self.thread_name, 'database', THREAD_MESSAGE_DB_WRITE, (ProtoCore.MessageID.MSG_CONTROL, json_str)))\

    def send_serial_command_message(self, command: str, target: str, command_param: int, source_sequence_number: int) -> bool:
        """
        Send the out going command message to the correct
        serial port based on the target node.

        Args:
            command (str):
                The command to be sent.
            target (str):
                The target node for the command.
            command_param (int):
                The command parameter for calibration or other commands.
            source_sequence_number (int):
                Unused.

        Returns:
            bool: 
                True if the message was successfully sent, False otherwise.
        """

        try:
            command_message = ProtobufParser.create_command_proto(command, target, command_param, source_sequence_number)
        except KeyError:
            logger.error(f"Attempting to send invalid command {command}")
            return False


        if command_message == None:
            logger.warning(f"Cannot send command {command} to {target}")
            return False

        buf = command_message.SerializeToString()

        logger.debug(f"Sending command message {command} to {target}")

        encBuf = Codec.Encode(buf, len(buf), ProtoCore.MessageID.MSG_COMMAND)
        target_enum = utl.get_node_from_str(target)
        if (target_enum == ProtoCore.NODE_DMB or target_enum == ProtoCore.Node.NODE_PBB) and self.port == RADIO_SERIAL_PORT:
            self.serial_port.write(encBuf)
        if (target_enum ==  ProtoCore.NODE_RCU or target_enum ==  ProtoCore.Node.NODE_SOB) and self.port == UART_SERIAL_PORT:
            self.serial_port.write(encBuf)

        return True
    
    def send_serial_control_message(self, message: bytes):
        """
        Sends a control message over the serial port.

        Args:
            message (bytes):
                The message to be sent. TODO Generalize this function. 

        Returns:
            bool: 
                True if the message was successfully sent, False otherwise.
        """

        buf = message
        encBuf = Codec.Encode(buf, len(buf), ProtoCore.MessageID.MSG_CONTROL)
        self.serial_port.write(encBuf)
        return True

# Procedures =======================================================================================

def serial_rx_thread(ser_han: SerialHandler):
    """
    Thread function for the incoming serial data listening.
    """
    while not (ser_han.kill_rx):
        ser_han.handle_serial_message()
        pass

def process_serial_workq_message(message: WorkQ_Message, ser_han: SerialHandler) -> bool:
        """
        Process the message from the workq.

        Args:
            message (str):
                The message from the workq.
        """
        logger.debug(f"Processing serial workq message: {message.message_type}")
        messageID = message.message_type

        if messageID == THREAD_MESSAGE_KILL:
            logger.debug(f"Killing {ser_han.thread_name} thread")
            return False
        elif messageID == THREAD_MESSAGE_SERIAL_WRITE:
            #-------------UNCOMMENT THE TWO LINES BELOW ONCE THE BOARD IS OBTAINED--------------
            # command = message.message[0]
            # target = message.message[1]
            # command_param = message.message[2]
            # source_sequence_number = message.message[3]
            print(f"Mock sending serial command message")
            # ser_han.send_serial_command_message(command, target, command_param, source_sequence_number)
        elif messageID == THREAD_MESSAGE_HEARTBEAT_SERIAL:
            print(f"Mock sending serial control message")
            #-------------UNCOMMENT THE TWO LINES BELOW ONCE THE BOARD IS OBTAINED--------------
            # ser_han.send_serial_control_message(message.message[0])
        ser_han.current_ser_workq_msg = message
        ser_han.serial_event_queue.put("WAIT")
        ser_han.serial_event.set()
        return True

def serial_thread(thread_name: str, device: SerialDevices, baudrate: int, thread_workq: mp.Queue, message_handler_workq: mp.Queue, serial_event_queue: mp.Queue, state_change_event_queue: mp.Queue, serial_event: mp.Event, state_change_event: mp.Event):
    """
    Thread function for the incoming serial data listening.

    Args:
        thread_name (str):
            The name of the thread.
        device (SerialDevices):
            The device to listen to.
        baudrate (int):
            The baudrate of the serial connection.
        thread_workq (mp.Queue):
            The workq to send messages to the thread.
        message_handler_workq (mp.Queue):
            The workq to send messages to the database handler. 
    """
    if device == SerialDevices.UART:
        port = UART_SERIAL_PORT
    elif device == SerialDevices.RADIO:
        port = RADIO_SERIAL_PORT
    
    # This log line should be removed once the pi core issue is solved
    logger.info(f"{device.name} process: {os.getpid()}")
    serial_workq = thread_workq

    #--------TO BE REMOVED-----------
    #Add below to test the workflow from receiving msg from the serial workq -> send msg -> wait 
    #Need to test if the flags and the corresponding queues are updated appropriately
    test_msg = WorkQ_Message('test1', 'test2', THREAD_MESSAGE_SERIAL_WRITE, ("Hello", "There"))
    serial_workq.put(test_msg)
    #---------END COMMENTS TO BE REMOVED-----------

    ser_han = SerialHandler(thread_name, port, baudrate, message_handler_workq, serial_event_queue, state_change_event_queue, serial_event, state_change_event)
    #-------------UNCOMMENT THE TWO LINES BELOW ONCE THE BOARD IS OBTAINED--------------
    # if ser_han.serial_port == None:
    #     return
    
    rx_thread = threading.Thread(target=serial_rx_thread, args=(ser_han,))
    rx_thread.start()

    #Using the counter to control how many time the workflow will loop through
    #Making sure workflow is setting/resetting the flags and update the appropriate queues accordingly.
    #Would need to replace while counter for testing < 3: with while True
    # counter_for_testing = 0
    # while counter_for_testing < 3:
    while True: 
        # then once the queue is empty read the serial port
        ser_han.state_change_event.wait()
        while not ser_han.state_change_event_queue.empty():
            state_event = ser_han.state_change_event_queue.get()
            if state_event == ControlProto.SystemState.SYS_SEND_NEXT_CMD:
                print("System in SYS_SEND_NEXT_CMD state")
                if not process_serial_workq_message(serial_workq.get(), ser_han):
                    ser_han.kill_rx = True   
                    rx_thread.join(10)
                    return
            elif state_event == ControlProto.SystemState.SYS_RETRANSMIT:
                print("System in SYS_RETRANSMIT state")
                process_serial_workq_message(ser_han.current_ser_workq_msg, ser_han)
            elif state_event == ControlProto.SystemState.SYS_WAIT:
                print("System in SYS_WAIT state. Sending the same msg (testing the workflow. Skipping timeout for now. )")
                process_serial_workq_message(ser_han.current_ser_workq_msg, ser_han)
            ser_han.state_change_event.clear()
        # counter_for_testing += 1
