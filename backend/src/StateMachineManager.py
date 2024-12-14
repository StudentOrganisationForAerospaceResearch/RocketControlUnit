"""
StateMachine.py

This file will contain the class State and class Event to make things more modular and easier to add/remove
states and events in the future. This design pattern is selected to make it simple for a direct 
translation between the FSM (Finite State Machine) and code. This aims to make it easier to understand
and work with for the future developers, who will be mostly students  Both classes will utilize Enum 
because it is a common way being used in our code base currently. 

The FSM diagram is CommControlMSG.puml.

"""

# General imports =================================================================================
from enum import Enum, unique
import os, sys, time, random
from queue import Queue
import threading
import multiprocessing as mp
import google.protobuf.message as Message

# Project specific imports ========================================================================
from src.ThreadManager import *
from proto.Python.CoreProto_pb2 import RocketState
from proto.Python.ControlMessage_pb2 import SystemState

# Class Definitions ===============================================================================
@unique
class Event(Enum):
    """
    Represents the event that triggers the transition from one state to another. The events that trigger state transition
    for the RCU and Rocket are both grouped in here. If there is a case to make RocketEvent and RCUEvent subclass to 
    inherit from the Event enum, we can explore that option at the time. For now, because state machine isn't being used
    too much in our code base, we will stick with this for now.

    """
    RCU_SEND_MSG = 0
    RCU_RCVD_ACK = 1
    RCU_RCVD_NAK = 2
    RCU_NO_RCVD_ACK = 3
    RCU_RETRANSMIT_TWICE = 4
    RCU_EXIT = 5
    RCU_START = 6
    ROCKET_RCVD_CMD = 7
    ROCKET_SEND_ACK = 8

class StateMachineManager():
    """
    Manage state transitions for the communication between the RCU and the rocket. 

    """
    def __init__(self, serial_event_queue: Queue, system_state_queue: Queue, serial_event: mp.Event, state_change_event: mp.Event):
        self.retransmit_counter = 0
        self.serial_event_queue = serial_event_queue
        self.system_state_queue = system_state_queue
        self.serial_event = serial_event 
        self.state_change_event = state_change_event



    def start(self):

        self.system_state_queue.put(SystemState.SYS_SEND_NEXT_CMD)
        self.state_change_event.set()
        #Using the counter to control how many time the workflow will loop through
        #Making sure workflow is setting/resetting the flags and update the appropriate queues accordingly.
        #Would need to replace while counter for testing < 3: with while True
        # counter_for_testing = 0
        # while counter_for_testing < 3:
        while True:
            self.serial_event.wait()
            while not self.serial_event_queue.empty():
                queue_serial_event = self.serial_event_queue.get()
                #Need this so we can start the timer to handle TIMEOUT event
                if queue_serial_event == "WAIT":
                    print(f"Setting system state to: {SystemState.SYS_WAIT}")
                    self.system_state_queue.put(SystemState.SYS_WAIT)
                elif queue_serial_event == "ACK":
                    print(f"Setting system state to: {SystemState.SYS_SEND_NEXT_CMD}")
                    self.system_state_queue.put(SystemState.SYS_SEND_NEXT_CMD)
                elif queue_serial_event == "NAK":
                    if self.retransmit_counter < 2:
                        print(f"Setting system state to: {SystemState.SYS_RETRANSMIT}")
                        self.system_state_queue.put(SystemState.SYS_RETRANSMIT)
                        self.retransmit_counter += 1
                    else:
                        print(f"Setting system state to: {SystemState.SYS_SEND_NEXT_CMD}")
                        self.system_state_queue.put(SystemState.SYS_SEND_NEXT_CMD)
                        self.retransmit_counter = 0
                elif queue_serial_event == "TIMEOUT":
                    if self.retransmit_counter < 2:
                        print(f"Setting system state to: {SystemState.SYS_RETRANSMIT}")
                        self.system_state_queue.put(SystemState.SYS_RETRANSMIT)
                        self.retransmit_counter += 1
                    else:
                        print(f"Setting system state to: {SystemState.SYS_SEND_NEXT_CMD}")
                        self.system_state_queue.put(SystemState.SYS_SEND_NEXT_CMD)
                        self.retransmit_counter = 0
                self.state_change_event.set()
                print(f"Set self.state_change_event flag to {self.state_change_event.is_set()}")
            self.serial_event.clear()
            print(f"Cleared self.serial_event flag to {self.serial_event.is_set()}")
            # counter_for_testing += 1

                          
        # mock_msg = ["ACK", "NAK", "TIMEOUT", "TIMEOUT", "ACK", "NAK", "WAIT"]
        # for choice in mock_msg: 
        #     print("Choice: ", choice)
        #     if choice == "ACK": 
        #         self.sys_state = SystemState.SYS_SEND_NEXT_CMD
        #         self.serial_event_queue.put(self.sys_state)
        #     elif choice == "NAK":
        #         #If retransmit counter is less than 2, then resend
        #         if self.retransmit_counter < 2:
        #             self.sys_state = SystemState.SYS_RETRANSMIT
        #             self.serial_event_queue.put(self.sys_state)
        #             self.retransmit_counter += 1
        #         #If retransmit twice already, then send the next message and reset the retransmit flag 
        #         else:
        #             self.sys_state = SystemState.SYS_SEND_NEXT_CMD
        #             self.serial_event_queue.put(self.sys_state)
        #             self.retransmit_counter  = 0
        #     elif choice == "TIMEOUT":
        #         if self.retransmit_counter < 2:
        #             #Send time out event and let the uart thread call retransmit function
        #             self.sys_state = SystemState.SYS_TIMEOUT
        #             self.serial_event_queue.put(self.sys_state)
        #             self.retransmit_counter += 1
        #             #If retransmit twice already, then send the next message and reset the retransmit flag 
        #         else:
        #             self.sys_state = SystemState.SYS_SEND_NEXT_CMD
        #             # self.uart_queue.put(self.sys_state)
        #             self.serial_event_queue.put(self.sys_state)
        #             self.retransmit_counter  = 0
        #     elif choice == "WAIT":
        #         self.sys_state = SystemState.SYS_WAIT
        #         self.serial_event_queue.put(self.sys_state)
        #     self.serial_event.set()

    # def mock_receive_msg(self):
    #     mock_msg = ["ACK"]
    #     choice = random.choice(mock_msg)
    #     print(choice)
    #     return choice    

# def state_machine_manager_thread (uart_queue: Queue, radio_queue: Queue, uart_event: mp.Event, radio_event: mp.Event):
def state_machine_manager_thread (serial_event_queue: Queue, system_state_queue: Queue, serial_event: mp.Event, system_state_event: mp.Event):
    """
    State Machine manager function to start the state machine thread
    """
    new_state_machine = StateMachineManager(serial_event_queue, system_state_queue, serial_event, system_state_event)
    new_state_machine.start()








