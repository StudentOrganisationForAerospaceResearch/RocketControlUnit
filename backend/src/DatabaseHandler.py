# General imports =================================================================================
import os
import json
import multiprocessing as mp
from pocketbase import Client
from pocketbase.services.realtime_service import MessageData

# Project specific imports ========================================================================
from src.support.CommonLogger import logger
from src.ThreadManager import THREAD_MESSAGE_DB_WRITE, THREAD_MESSAGE_KILL, THREAD_MESSAGE_SERIAL_WRITE, WorkQ_Message
from src.Utils import Utils as utl

# Class Definitions ===============================================================================
class DatabaseHandler():
    def __init__(self,thread_name: str, thread_workq: mp.Queue, message_handler_workq: mp.Queue):
        """
        Thread to handle the pocketbase database communication.
        The Thread is subscribed to the CommandMessage
        collection to wait for commands created in the front end. 
        The handler can also send telemetry data to the database
        to be read by the front end.
        """
        logger.info("DatabaseHandler initializing")
        DatabaseHandler.thread_workq = thread_workq
        DatabaseHandler.send_message_workq = message_handler_workq
        DatabaseHandler.thread_name = thread_name
        DatabaseHandler.client = Client('http://127.0.0.1:8090')
        DatabaseHandler.client.collection('CommandMessage').subscribe(DatabaseHandler._handle_command_callback)
        logger.success(f"Successfully started {thread_name} thread")

    @staticmethod
    def _handle_command_callback(document: MessageData):
        """
        Whenever a new entry is created in the CommandMessage 
        collection, this function is called to handle the
        command and forward it to the serial port.

        Args:
            document (MessageData): the change notification from the database.
        """

        logger.info("Received new command from the database")
        logger.debug(f"Record command: {document.record.command}")
        DatabaseHandler.send_message_workq.put(
            WorkQ_Message(
                DatabaseHandler.thread_name,
                'all_serial', 
                THREAD_MESSAGE_SERIAL_WRITE, 
                (document.record.command,
                 document.record.target,
                 document.record.command_param,
                 document.record.source_sequence_num
                )
            )
        )

    @staticmethod
    def send_message_to_database(json_data: str):
        """
        Send a preserialized JSON message to the database.

        Note: The third key in the JSON data is assumed to be the table name
        """
        # Extract the table name from the JSON data
        json_data = json.loads(json_data)
        if len(list(json_data.keys())) < 3:
            logger.warning(f"Received, poorly formed json: {json_data}")
            return

        table_name = list(json_data.keys())[2]

        logger.info(f"Adding an entry to the {table_name} table")
        logger.info(f"Entry: {json_data[table_name]}")

        # Push the JSON data to PocketBase using the correct schema
        try:
            DatabaseHandler.client.collection(table_name).create(json_data[table_name])
        except Exception:
            logger.error(f"Failed to create entry in {table_name}: {json_data}")

# Procedures ======================================================================================
def database_thread(thread_name: str, db_workq: mp.Queue, message_handler_workq: mp.Queue):
    """
    The main loop of the database handler. It subscribes to the CommandMessage collection
    """
    # This log line should be removed once the pi core issue is solved
    logger.info(f"Database process: {os.getpid()}")

    DatabaseHandler(thread_name, db_workq, message_handler_workq)

    while 1:
        # If there is any workq messages, process them
        if not process_workq_message(db_workq.get(block=True)):
            return
        
def process_workq_message(message: WorkQ_Message) -> bool:
    """
    Process the message from the workq.

    Args:
        message (WorkQ_Message):
            The message from the workq.
    """
    logger.debug(f"Processing db workq message: {message.message_type}")
    messageID = message.message_type

    if messageID == THREAD_MESSAGE_KILL:
        logger.debug(f"Killing database thread")
        return False
    elif messageID == THREAD_MESSAGE_DB_WRITE:   
        logger.debug(f"Writing {utl.get_message_from_enum(message.message[0])}")
        DatabaseHandler.send_message_to_database(message.message[1])
        return True
    return True

# EXPECTED DATA FORMAT
#
# json = """
# {
#   "source": "NODE_DMB",
#   "target": "NODE_RCU",
#   "RcuPressure": {
#     "pt1_pressure": 100,
#     "pt2_pressure": 200,
#     "pt3_pressure": 300,
#     "pt4_pressure": 400
#   }
# }
# """