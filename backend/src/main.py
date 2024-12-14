
# General imports =================================================================================
import os, sys, time
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
from src.StateMachineManager import state_machine_manager_thread
from queue import Queue

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
        uart_event_queue = mp.Queue()
        radio_event_queue = mp.Queue()
        radio_state_queue = mp.Queue()
        heartbeat_workq = mp.Queue()
        uart_event = mp.Event()
        radio_event = mp.Event()
        radio_state_change_event = mp.Event()

        # Create a main thread for handling thread messages
        thread_pool['message_handler'] = {'thread': None, 'workq': message_handler_workq}

        # Initialize the threads
        # uart_thread = mp.Process(target=serial_thread, args=('uart', sd.UART, UART_BAUDRATE, uart_workq, message_handler_workq, uart_event_queue))
        radio_thread = mp.Process(target=serial_thread, args=('radio', sd.RADIO, RADIO_BAUDRATE, radio_workq, message_handler_workq, radio_event_queue, radio_state_queue,  radio_event, radio_state_change_event))
        # db_thread = mp.Process(target=database_thread, args=('database', db_workq, message_handler_workq))
        # lc_thread = mp.Process(target=load_cell_thread, args=('loadcell', loadcell_workq, message_handler_workq))
        # hb_thread = mp.Process(target=heartbeat_thread, args=('heartbeat', heartbeat_workq, message_handler_workq))
        serial_state_machine_thread = mp.Process(target=state_machine_manager_thread, args=(radio_event_queue, radio_state_queue,  radio_event, radio_state_change_event))
        
        # Add the threads to the thread pool
        # thread_pool['uart'] = {'thread': uart_thread, 'workq': uart_workq}
        thread_pool['radio'] = {'thread': radio_thread, 'workq': radio_workq}
        # thread_pool['database'] = {'thread': db_thread, 'workq': db_workq}
        # thread_pool['loadcell'] = {'thread': lc_thread, 'workq': loadcell_workq}
        # thread_pool['heartbeat'] = {'thread': hb_thread, 'workq': heartbeat_workq}
        thread_pool['state_machine'] = {'thread': serial_state_machine_thread, 'workq': None}
        
        tm.thread_pool = thread_pool
        return

if __name__ == "__main__":
  # tm()
  # initialize_threads()
  # tm.start_threads()

  # while 1:
  #   tm.handle_thread_messages()

  #Testing the work flow with the state machine integration into serial handler. 
  #Only testing the radio serial rx thread right now to keep things simple
  #If need to do testing/debugging for longer, increment the time.sleep(X) to the desired number
  #Without it, the threads will terminate immediately, thus, unable to do any debugging
  radio_workq = mp.Queue()
  message_handler_workq = mp.Queue()
  radio_event_queue = mp.Queue()
  radio_state_queue = mp.Queue()
  radio_event = mp.Event()
  radio_state_change_event = mp.Event()
  radio_thread = mp.Process(target=serial_thread, args=('radio', sd.RADIO, RADIO_BAUDRATE, radio_workq, message_handler_workq, radio_event_queue, radio_state_queue,  radio_event, radio_state_change_event))
  serial_state_machine_thread = mp.Process(target=state_machine_manager_thread, args=(radio_event_queue, radio_state_queue,  radio_event, radio_state_change_event))
  radio_thread.start()
  serial_state_machine_thread.start()
 
  time.sleep(60)

  radio_thread.terminate()
  serial_state_machine_thread.terminate()

