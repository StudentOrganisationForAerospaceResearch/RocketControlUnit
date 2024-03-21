# General imports =================================================================================
import enum
import multiprocessing as mp
import time
import serial           # You'll need to run `pip install pyserial`
from cobs import cobs   # pip install cobs
import google.protobuf.message as Message

# Project specific imports ========================================================================
import proto.Python.CoreProto_pb2 as ProtoCore
import proto.Python.TelemetryMessage_pb2 as TelemetryProto
import proto.Python.ControlMessage_pb2 as ControlProto

from src.support.Codec import Codec
from src.support.ProtobufParser import ProtobufParser
from src.support.CommonLogger import logger

from src.ThreadManager import THREAD_MESSAGE_DB_WRITE, THREAD_MESSAGE_KILL, THREAD_MESSAGE_SERIAL_WRITE, WorkQ_Message
from src.Utils import Utils as utl

# Constants ========================================================================================
MIN_SERIAL_MESSAGE_LENGTH = 6

UART_SERIAL_PORT = "/dev/ttyS0"
RADIO_SERIAL_PORT = "/dev/ttyUSB0"

# Data Classes =====================================================================================
class SerialDevices(enum.Enum):
    UART = 1
    RADIO = 2


# Class Definitions ===============================================================================
class SerialHandler():
    def __init__(self, thread_name: str, port: str, baudrate: int, message_handler_workq: mp.Queue):
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
        return self.serial_port.read_until(expected = b'\x00', size = None)

    def handle_serial_message(self):
        """
        Handle incoming serial messages.

        Args:
            message (bytes):
                the data that was received.
        """
        # Read the serial port
        message = self._get_serial_message()

        # Check message length
        if len(message) < MIN_SERIAL_MESSAGE_LENGTH:
            logger.warning(f"Message from {self.port} too short: {message}")
            return
        
        # Decode, remove 0x00 byte
        try:
            msgId, data = Codec.Decode(message[:-1], len(message) - 1)
        except cobs.DecodeError:
            logger.warning("Invalid cobs message")
            return
        
        # Process message according to ID
        if msgId == ProtoCore.MessageID.MSG_TELEMETRY:
            self.process_telemetry_message(data)
        elif msgId == ProtoCore.MessageID.MSG_CONTROL:
            self.process_control_message(data)
        else:
            logger.warning("Received invalid MessageID")

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

        self.send_message_workq.put(WorkQ_Message(self.thread_name, 'database', THREAD_MESSAGE_DB_WRITE, (ProtoCore.MessageID.MSG_TELEMETRY, json_str)))
        
    def process_control_message(self, data):
        """
        Process the incoming control message.

        Args:
            data (bytes):
                The data that was received.
        """
        received_message = ControlProto.ControlMessage()
        # Ensure we received a valid message
        try:
            received_message.ParseFromString(data)
        except Message.DecodeError:
            logger.warning(f"Unable to decode control message: {data}")
            return
        # Ensure the message is intended for us
        if received_message.target == ProtoCore.NODE_RCU or received_message.target == ProtoCore.NODE_ANY:
            control_message_type = received_message.WhichOneof('message')
            logger.debug(f"Received {control_message_type} from {utl.get_node_from_enum(received_message.source)}")
        else:
            logger.debug(f"Received message intended for {utl.get_node_from_enum(received_message.target)}")
            return
        
        json_str = ProtobufParser.parse_serial_to_json(data, ProtoCore.MessageID.MSG_CONTROL)

        self.send_message_workq.put(WorkQ_Message(self.thread_name, 'database', THREAD_MESSAGE_DB_WRITE, (ProtoCore.MessageID.MSG_CONTROL, json_str)))\

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

        command_message = ProtobufParser.create_command_proto(command, target, command_param, source_sequence_number)

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

# Procedures =======================================================================================

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
            command = message.message[0]
            target = message.message[1]
            command_param = message.message[2]
            source_sequence_number = message.message[3]
            ser_han.send_serial_command_message(command, target, command_param, source_sequence_number)
        return True

def serial_thread(thread_name: str, device: SerialDevices, baudrate: int, thread_workq: mp.Queue, message_handler_workq: mp.Queue):
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
    
    serial_workq = thread_workq
    ser_han = SerialHandler(thread_name, port, baudrate, message_handler_workq)
    if ser_han.serial_port == None:
        return

    while (1):
        # If there is any workq messages, process them first
        # then once the queue is empty read the serial port
        if not serial_workq.empty():
            if not process_serial_workq_message(serial_workq.get(), ser_han):
                return
        else:
            ser_han.handle_serial_message()

        time.sleep(0.1)

