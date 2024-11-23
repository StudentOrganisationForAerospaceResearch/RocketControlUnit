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
    def __init__(self, uart_queue: Queue, radio_queue: Queue, uart_event: mp.Event, radio_event: mp.Event):
        self.sys_state = SystemState.SYS_NORMAL_OPERATION
        self.last_message = None
        self.retransmit_counter = 0
        self.uart_queue = uart_queue
        self.radio_queue = radio_queue
        self.uart_event = uart_event
        self.radio_event = radio_event 

    def start(self):

        #Randomnize ACK/NAK/TIMEOUT
        choice = self.mock_receive_msg()
        print("Choice: ", choice)
        if choice == "ACK": 
            self.sys_state = SystemState.SYS_SEND_NEXT_CMD
            self.uart_queue.put(self.sys_state)
        elif choice == "NAK":
            #If retransmit counter is less than 2, then resend
            if self.retransmit_counter < 2:
                self.sys_state = SystemState.SYS_RETRANSMIT
                self.uart_queue.put(self.sys_state)
                self.retransmit_counter += 1
            #If retransmit twice already, then send the next message and reset the retransmit flag 
            else:
                self.sys_state = SystemState.SYS_SEND_NEXT_CMD
                self.uart_queue.put(self.sys_state)
                self.retransmit_counter  = 0
        elif choice == "TIMEOUT":
            if self.retransmit_counter < 2:
                #Send time out event and let the uart thread call retransmit function
                self.sys_state = SystemState.SYS_TIMEOUT
                self.uart_queue.put(self.sys_state)
                self.retransmit_counter += 1
                #If retransmit twice already, then send the next message and reset the retransmit flag 
            else:
                self.sys_state = SystemState.SYS_SEND_NEXT_CMD
                self.uart_queue.put(self.sys_state)
                self.retransmit_counter  = 0
        self.uart_event.set()

    def mock_receive_msg(self):
        mock_msg = ["ACK"]
        choice = random.choice(mock_msg)
        print(choice)
        return choice

    # def handle_wait(self):

    #     """
    #     Handle the logic of calling other functions depending on rocket responses. 
    #     """
    #     #Ideally, should have another function to parse the response received from DMB
    #     # response = parse_rocket_response(), change the if blocks below to if, elif,else, etc
    #     response = self.simulate_rocket_response()

    #     if self.sys_state == SystemState.SYS_WAIT:
    #         #If received NAK from Rocket:
    #         if response == "NAK":
    #             self.handle_retransmit()
    #         elif response == "ACK":
    #             self.handle_send_next_cmd()
    #         elif response == "TIMEOUT":
    #             self.sys_state = SystemState.SYS_TIMEOUT
    #             self.handle_timeout()
    #         else:
    #             print("Bro, you messed up\n\r")

    # def handle_retransmit(self):
    #     #If retransmit counter is within range, retransmit the same message
    #     if self.retransmit_counter < 2:
    #         self.retransmit_counter += 1
    #         self.start_sending_msg()
    #     else:
    #         self.sys_state = SystemState.SYS_SEND_NEXT_CMD
    #         self.handle_send_next_cmd()

    # def handle_send_next_cmd(self):
    #     #Send next cmd
    #     self.sys_state = SystemState.SYS_WAIT
    #     #reset retransmit counter
    #     self.retransmit_counter = 0 
    # def handle_timeout(self):

    #     #Call retransmit 
    #     self.sys_state = SystemState.SYS_RETRANSMIT
    #     self.handle_retransmit()

    # def simulate_rocket_response(self):
    #     # Simulate different responses from Rocket
    #     responses = ["ACK", "NAK", "TIMEOUT"]
    #     return random.choice(responses)
    
    # def exit(self):
    #     """
    #     Exit the state machine for RCU and Rocket serial communication by setting RCU state to be uninitialized 
    #     and event to RCU Exit.

    #     """
    #     self.sys_state = SystemState.SYS_INVALID
    #     self.rocket_state = RocketState.RS_NONE
    #     self.event = Event.RCU_EXIT

    # def get_rcu_state(self):
    #     """
    #     Return the current state of the RCU.

    #     """
    #     print("\nThe current RCU state:")
    #     return self.sys_state

    # def get_rocket_state(self):
    #     """"
    #     Return the current state of the rocket.

    #     """
    #     print("\nThe current rocket state:")
    #     return self.rocket_state
    

def state_machine_manager_thread (uart_queue: Queue, radio_queue: Queue, uart_event: mp.Event, radio_event: mp.Event):
    """
    State Machine manager function to start the state machine thread
    """
    new_state_machine = StateMachineManager(uart_queue, radio_queue, uart_event, radio_event)
    new_state_machine.start()








