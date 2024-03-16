# General imports =================================================================================
import time, os, sys, git
import multiprocessing as mp
from pocketbase import Client
from pocketbase.services.realtime_service import MessageData

# Project specific imports ========================================================================
from src.support.CommonLogger import CommonLogger

from src.Utils import THREAD_MESSAGE_KILL, THREAD_MESSAGE_SERIAL_WRITE, WorkQ_Message

# Class Definitions ===============================================================================
class DatabaseHandler():
    def __init__(self, thread_workq: mp.Queue, message_handler_workq: mp.Queue):
        """
        Thread to handle the pocketbase database communication.
        The Thread is subscribed to the CommandMessage
        collection to wait for commands created in the front end. 
        The handler can also send telemetry data to the database
        to be read by the front end.
        """
        CommonLogger.logger.info("DatabaseHandler initializing")
        DatabaseHandler.thread_workq = thread_workq
        DatabaseHandler.send_message_workq = message_handler_workq
        DatabaseHandler.client = Client("http://127.0.0.1:8090")
        DatabaseHandler.client.collection('CommandMessage').subscribe(DatabaseHandler._handle_command_callback)

    @staticmethod
    def _handle_command_callback(document: MessageData):
        """
        Whenever a new entry is created in the CommandMessage 
        collection, this function is called to handle the
        command and forward it to the serial port.

        Args:
            document (MessageData): the change notification from the database.
        """
        CommonLogger.logger.info("Received new command from the database")
        CommonLogger.logger.debug(f"Record command: {document.record.command}")
        DatabaseHandler.send_message_workq.put(WorkQ_Message('database', 'all_serial', THREAD_MESSAGE_SERIAL_WRITE, (document.record.command,)))

# Procedures ======================================================================================
def database_thread(thread_name:str, db_workq: mp.Queue, message_handler_workq: mp.Queue):
    """
    The main loop of the database handler. It subscribes to the CommandMessage collection
    """

    db_han = DatabaseHandler(db_workq, message_handler_workq)

    while 1:
        # If there is any workq messages, process them
        if not db_workq.empty():
            if not process_workq_message(db_workq.get()):
                return
        time.sleep(0.1)
        
def process_workq_message(message: WorkQ_Message) -> bool:
    """
    Process the message from the workq.

    Args:
        message (WorkQ_Message):
            The message from the workq.
    """
    CommonLogger.logger.debug(f"Processing db workq message: {message}")
    messageID = message.message_type

    if messageID == THREAD_MESSAGE_KILL:
        return False
    return True