
# General imports =================================================================================
import time
import os, sys, git
import multiprocessing as mp

# Project specific imports ========================================================================
git_repo = git.Repo(__file__, search_parent_directories=True).git.rev_parse("--show-toplevel")
sys.path.insert(0, os.path.join(git_repo, "backend", 'proto/Python'))
sys.path.insert(0, os.path.join(git_repo, "backend"))

from src.support.CommonLogger import CommonLogger
from src.DatabaseHandler import database_thread
from src.SerialHandler import SerialDevices as sd, serial_thread
from src.Utils import RADIO_BAUDRATE, UART_BAUDRATE, Utils as utl

# Constants =======================================================================================
LOG_TO_TERMINAL = True

# Local Procedures ================================================================================
def initialize_threads():
        '''
        Create threads for the backend
        '''
        CommonLogger.logger.info('Initializing threads')
        pass
        thread_pool = {}
        uart_workq = mp.Queue()
        radio_workq = mp.Queue()
        db_workq = mp.Queue()
        message_handler_workq = mp.Queue()

        # Create a main thread for handling thread messages
        thread_pool['message_handler'] = {'thread': None, 'workq': message_handler_workq}

        # Initialize the serial handler threads
        uart_thread = mp.Process(target=serial_thread, args=('uart', sd.UART, UART_BAUDRATE, uart_workq, message_handler_workq))
        radio_thread = mp.Process(target=serial_thread, args=('radio', sd.RADIO, RADIO_BAUDRATE, radio_workq, message_handler_workq))

        # Add the threads to the thread pool
        thread_pool['uart'] = {'thread': uart_thread, 'workq': uart_workq}
        thread_pool['radio'] = {'thread': radio_thread, 'workq': radio_workq}
        
        # Initialize the database handler thread
        db_thread = mp.Process(target=database_thread, args=('database', db_workq, message_handler_workq))
        # Add the database thread to the thread pool
        thread_pool['database'] = {'thread': db_thread, 'workq': db_workq}
        
        utl.thread_pool = thread_pool
        return

if __name__ == "__main__":
  CommonLogger(LOG_TO_TERMINAL)
  utl()
  initialize_threads()
  utl.start_threads()

  while 1:
    utl.handle_thread_messages()
    time.sleep(0.1)
