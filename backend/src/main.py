
# General imports =================================================================================
import os, sys
import multiprocessing as mp

# Project specific imports ========================================================================
dirname, _ = os.path.split(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend', 'proto/Python'))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend'))

from src.support.CommonLogger import logger
from src.DatabaseHandler import database_thread
from src.HeartbeatHandler import heartbeat_thread
from src.SerialHandler import SerialDevices as sd, serial_thread
from src.ThreadManager import ThreadManager as tm
from src.LoadCellHandler import load_cell_thread

# Constants ========================================================================================
UART_BAUDRATE = 115200
RADIO_BAUDRATE = 57600 

# Local Procedures ================================================================================
def initialize_threads():
        '''
        Create threads for the backend
        '''
        logger.info('Initializing threads')
        thread_pool = {}
        uart_workq = mp.Queue()
        radio_workq = mp.Queue()
        db_workq = mp.Queue()
        loadcell_workq = mp.Queue()
        message_handler_workq = mp.Queue()
        heartbeat_workq = mp.Queue()

        # Create a main thread for handling thread messages
        thread_pool['message_handler'] = {'thread': None, 'workq': message_handler_workq}

        # Initialize the threads
        uart_thread = mp.Process(target=serial_thread, args=('uart', sd.UART, UART_BAUDRATE, uart_workq, message_handler_workq))
        radio_thread = mp.Process(target=serial_thread, args=('radio', sd.RADIO, RADIO_BAUDRATE, radio_workq, message_handler_workq))
        db_thread = mp.Process(target=database_thread, args=('database', db_workq, message_handler_workq))
        lc_thread = mp.Process(target=load_cell_thread, args=('loadcell', loadcell_workq, message_handler_workq))
        hb_thread = mp.Process(target=heartbeat_thread, args=('heartbeat', heartbeat_workq, message_handler_workq))
        
        # Add the threads to the thread pool
        thread_pool['uart'] = {'thread': uart_thread, 'workq': uart_workq}
        thread_pool['radio'] = {'thread': radio_thread, 'workq': radio_workq}
        thread_pool['database'] = {'thread': db_thread, 'workq': db_workq}
        thread_pool['loadcell'] = {'thread': lc_thread, 'workq': loadcell_workq}
        thread_pool['heartbeat'] = {'thread': hb_thread, 'workq': heartbeat_workq}
        
        tm.thread_pool = thread_pool
        return

if __name__ == "__main__":
  tm()
  initialize_threads()
  tm.start_threads()

  while 1:
    tm.handle_thread_messages()