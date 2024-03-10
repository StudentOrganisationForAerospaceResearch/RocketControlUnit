from concurrent.futures import ThreadPoolExecutor
import enum
import os
import sys
import serial           # You'll need to run `pip install pyserial`
from cobs import cobs   # pip install cobs
from Codec import Codec

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'proto/Python'))

from Utils import get_node_from_enum
import proto.Python.CoreProto_pb2 as ProtoCore
import proto.Python.TelemetryMessage_pb2 as TelemetryProto
import proto.Python.ControlMessage_pb2 as ControlProto
from ProtobufParser import ProtobufParser
import google.protobuf.message as Message
import json

from CommonLogger import CommonLogger

MIN_SERIAL_MESSAGE_LENGTH = 6

UART_SERIAL_PORT = "/dev/ttyS0"
RADIO_SERIAL_PORT = "/dev/ttyUSB0"

UART_BAUDRATE = 115200
RADIO_BAUDRATE = 115200 #NOTE: might need to change this (57600 ???)

class SerialDevices(enum.Enum):
    UART = 1
    RADIO = 2

class SerialHandler():
    def __init__(self):
        """
        This thread class creates threads to handle 
        incoming and outgoing serial messages over 
        the radio to the DMB and the uart to RCU.
        """
        CommonLogger.logger.info("SerialHandler initializing")
        self.serial_executor = ThreadPoolExecutor(max_workers=2)
        self.serial_stop = False
        
    def _radio_rx_thread(self):
        """
        Thread function for the radio serial incoming data listening.
        """
        # Open radio serial port
        self.radio_serial = serial.Serial(port=RADIO_SERIAL_PORT, baudrate=UART_BAUDRATE, bytesize=8, parity=serial.PARITY_NONE, timeout=None, stopbits=serial.STOPBITS_ONE)
        while not self.serial_stop:
            message = self.radio_serial.read_until(expected = b'\x00', size = None)
            self._handle_serial_message(SerialDevices.RADIO, message)

    def _uart_rx_thread(self):
        """
        Thread function for the uart serial incoming data listening.
        """
        # Open UART serial port
        self.uart_serial = serial.Serial(port=UART_SERIAL_PORT, baudrate=UART_BAUDRATE, bytesize=8, parity=serial.PARITY_NONE, timeout=None, stopbits=serial.STOPBITS_ONE)
        while not self.serial_stop:
            message = self.radio_serial.read_until(expected = b'\x00', size = None)
            self._handle_serial_message(SerialDevices.RADIO, message)

    def start(self):
        """
        Start both the UART and radio listening threads
        """
        self.uart_thread_task = self.serial_executor.submit(self._uart_rx_thread)
        self.radio_thread_task = self.serial_executor.submit(self._radio_rx_thread)

    def stop(self):
        """
        Close the serial ports opened for UART and radio and kill the threads.
        """
        self.serial_stop = True
        self.uart_thread_task.result()
        self.radio_thread_task.result()

    def _handle_serial_message(self, source: SerialDevices, message: bytes):
        """
        Handle incoming serial messages.

        Args:
            source (SerialDevices): 
                which serial connection received the message.
            message (bytes):
                the data that was received.
        """
        # Check message length
        if len(message) < MIN_SERIAL_MESSAGE_LENGTH:
            CommonLogger.logger.warning(f"Message from {source.name} too short: {message}")
            return
        
        # Decode, remove 0x00 byte
        try:
            msgId, data = Codec.Decode(message[:-1], len(message) - 1)
        except cobs.DecodeError:
            CommonLogger.logger.warning("Invalid cobs message")
            return
        
        # Process message according to ID
        if msgId == ProtoCore.MessageID.MSG_TELEMETRY:
            self.process_telemetry_message(data)
        elif msgId == ProtoCore.MessageID.MSG_CONTROL:
            self.process_control_message(data)
        else:
            CommonLogger.logger.warning("Received invalid MessageID")

    def process_telemetry_message(self, data):
        received_message = TelemetryProto.TelemetryMessage()
        # Ensure we received a valid message
        try:
            received_message.ParseFromString(data)
        except Message.DecodeError:
            CommonLogger.logger.warning("Unable to decode telemetry message: {data}")
            return
        # Ensure the message is intended for us
        if received_message.target == ProtoCore.NODE_RCU or received_message.target == ProtoCore.NODE_ANY:
            telemetry_message_type = received_message.WhichOneof('message')
            CommonLogger.logger.debug(f"Received {telemetry_message_type} from {get_node_from_enum(received_message.source)}")
        else:
            CommonLogger.logger.debug(f"Received message intended for {get_node_from_enum(received_message.target)}")
            return
        
        ProtobufParser.parse_serial_to_json(data, ProtoCore.MessageID.MSG_TELEMETRY)
        

    def process_control_message(self, data):
        received_message = ControlProto.ControlMessage()
        # Ensure we received a valid message
        try:
            received_message.ParseFromString(data)
        except Message.DecodeError:
            CommonLogger.logger.warning("Unable to decode control message: {data}")
            return
        # Ensure the message is intended for us
        if received_message.target == ProtoCore.NODE_RCU or received_message.target == ProtoCore.NODE_ANY:
            control_message_type = received_message.WhichOneof('message')
            CommonLogger.logger.debug(f"Received {control_message_type} from {get_node_from_enum(received_message.source)}")
        else:
            CommonLogger.logger.debug(f"Received message intended for {get_node_from_enum(received_message.target)}")
            return
        
        ProtobufParser.parse_serial_to_json(data, ProtoCore.MessageID.MSG_CONTROL)

        

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
            CommonLogger.logger.warning(f"Cannot send command {command} to {target}")
            return False

        buf = command_message.SerializeToString()

        CommonLogger.logger.debug(f"Sending command message {command} to {target}")

        encBuf = Codec.Encode(buf, len(buf), ProtoCore.MessageID.MSG_COMMAND)

        if target ==  ProtoCore.NODE_DMB or target ==  ProtoCore.Node.NODE_PBB:
            self.radio_serial.write(encBuf)
        if target ==  ProtoCore.NODE_RCU or target ==  ProtoCore.Node.NODE_SOB:
            self.uart_serial.write(encBuf)

        return True






# sh = SerialHandler()

# sh.send_serial_command_message("RSC_ANY_TO_ABORT", "NODE_DMB", 0, 23)

# sh._handle_serial_message(SerialDevices.RADIO, bytes(Codec.Encode([8, 3, 16, 4, 24, 23, 34, 2, 8, 1], len([8, 3, 16, 4, 24, 23, 34, 2, 8, 1]),4)))


