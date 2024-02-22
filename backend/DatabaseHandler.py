import threading

from pocketbase import Client, utils
from pocketbase.services.realtime_service import MessageData
from CommonLogger import CommonLogger



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
        self.database_thread = threading.Thread(target=self._run)
        self.client = Client("http://127.0.0.1:8090")

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
        CommonLogger.logger.debug(f"Record command: {document.record}")
        CommonLogger.logger.debug(document.record['command'])





    def _run(self):
        """
        The main loop of the database handler. It subscribes to the CommandMessage collection
        """
        while not self.thread_stop:
            try:
                # Note: this needs to be in the while loop to keep the subscription alive
                self.record_service = self.client.collection('CommandMessage').subscribe(DatabaseHandler._handle_command_callback)
            except utils.ClientResponseError as e:
                CommonLogger.logger.warning(f"Database subscription fault with status {e.status}")
  
    def start(self):
        """
        Start the database handler thread.
        """
        CommonLogger.logger.info(f"Starting database handler thread")
        self.database_thread.start()

    # def stop(self):
    #     CommonLogger.logger.info(f"Closing database handler thread")
    #     self.thread_stop = True
    #     self.database_thread.join()
