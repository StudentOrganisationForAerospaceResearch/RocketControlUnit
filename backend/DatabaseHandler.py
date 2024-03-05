import threading
import time

from pocketbase import Client
from pocketbase.services.realtime_service import MessageData
from CommonLogger import CommonLogger
from SerialHandler import send_serial_message


class DatabaseHandler():

    def __init__(self):
        """
        Thread to handle the pocketbase database communication.
        The Thread is subscribed to the CommandMessage
        collection to wait for commands created in the front end. 
        The handler can also send telemetry data to the database
        to be read by the front end.
        """
        CommonLogger.logger.info("DatabaseHandler initializing")
        self.thread_stop = False
        self.pi_command_thread = threading.Thread(target=self._run_pi_command_thread)
        self.backend_command_thread = threading.Thread(target=self._run_backend_command_thread)
        self.client = Client("http://127.0.0.1:8090")

    @staticmethod
    def _handle_pi_command_callback(document: MessageData) -> None:
        """
        Whenever a new entry is created in the CommandMessage 
        collection, this function is called to handle the
        command and forward it to the serial port.

        Args:
            document (MessageData): the change notification from the database.
        """
        command: str = document.record.command
        target: str = document.record.target
        command_param: int = document.record.command_param
        source_sequence_number: int = document.record.source_sequence_number

        CommonLogger.logger.info("Received new command from the CommandMessage collection")
        CommonLogger.logger.debug(f"Record command: {document.record.command}")
        CommonLogger.logger.debug(f"Record target: {document.record.target}")
        CommonLogger.logger.debug(f"Record command_param: {document.record.command_param}")
        CommonLogger.logger.debug(f"Record source_sequence_number: {document.record.source_sequence_number}")

        send_serial_message(command, target, command_param, source_sequence_number)

    @staticmethod
    def _handle_backend_command_callback(document: MessageData) -> None:
        """
        Whenever a new entry is created in the BackendCommand 
        collection, this function is called to handle any command targeted at the backend for processing
        and forward it to the appropriate function.

        Args:
            document (MessageData): the change notification from the database.
        """
        CommonLogger.logger.info("Received new data from the BackendCommand collection")

    def _run_database_command_thread(self) -> None:
        """
        The main loop of the database handler. It subscribes to the CommandMessage collection
        """
        CommonLogger.logger.info("DatabaseHandler database thread started")
        self.client.collection("CommandMessage").subscribe(self._handle_database_command_callback)
        while not self.thread_stop:
            time.sleep(0.5)

    def _run_backend_command_thread(self) -> None:
        """
        The main loop of the backend command handler. It subscribes to the backend collection
        """
        CommonLogger.logger.info("Backend command thread started")
        self.client.collection("BackendCommand").subscribe(self._handle_backend_command_callback)
        while not self.thread_stop:
            time.sleep(0.5)
  
    def start(self) -> None:
        """
        Start the handler threads.
        """
        CommonLogger.logger.info(f"Starting pi command thread")
        self.pi_command_thread.start()
        CommonLogger.logger.info(f"Starting backend command thread")
        self.backend_command_thread.start()

    def stop(self) -> None:
        """
        Stop the handler threads.
        """
        CommonLogger.logger.info(f"Closing pi and backend command threads")
        self.thread_stop = True
        self.pi_command_thread.join()
        self.backend_command_thread.join()