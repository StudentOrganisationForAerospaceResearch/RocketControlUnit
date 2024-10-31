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

# Project specific imports ========================================================================
dirname, _ = os.path.split(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend'))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'src/StateMachine'))
from src.StateMachine.BaseStateMachine import BaseStateMachine
from src.ThreadManager import *
from src.SerialHandler import SerialHandler
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

class StateMachineManager(BaseStateMachine):
    """
    Manage state transitions for the communication between the RCU and the rocket. 

    """
    def __init__(self):
        self.sys_state = SystemState.SYS_NORMAL_OPERATION
        self.rocket_state = RocketState.RS_LISTENING
        self.event = Event.RCU_START
        self.message = None
        self.retransmit_counter = 0

    def start_sending_msg(self, message: WorkQ_Message, ser_han: SerialHandler):
        """
        Send control/command message from RCU (radio) to Rocket (DMB) by calling
        the appropriate send functions that corresponds to the message type.
        Set the RCU and rocket state to the appropriate state and call the next function

        Args:
            message: message from the workq to identify whether to send control 
                or command message
            ser_han: Serial Handler class to call the functions to send the messages

        """
        messageID = message.message_type
        if messageID == THREAD_MESSAGE_SERIAL_WRITE:
            command = message.message[0]
            target = message.message[1]
            command_param = message.message[2]
            source_sequence_number = message.message[3]
            ser_han.send_serial_command_message(command, target, command_param, source_sequence_number)
        elif messageID == THREAD_MESSAGE_HEARTBEAT_SERIAL:
            ser_han.send_serial_control_message(message.message[0])
        
        #Update the state and call next step in the state machine
        self.sys_state = SystemState.SYS_WAIT
        self.handle_wait(message, ser_han)

    def handle_wait(self, message: WorkQ_Message, ser_han: SerialHandler,):

        """
        Handle the logic of calling other functions depending on rocket responses. 
        """
        #Ideally, should have another function to parse the response received from DMB
        # response = parse_rocket_response(), change the if blocks below to if, elif,else, etc
        response = self.simulate_rocket_response()

        if self.sys_state == SystemState.SYS_WAIT:
            #If received NAK from Rocket:
            if response == "NAK":
                self.handle_retransmit(message, ser_han)
            elif response == "ACK":
                self.handle_send_next_cmd()
            elif response == "TIMEOUT":
                self.sys_state = SystemState.SYS_TIMEOUT
                self.handle_timeout()
            else:
                print("Bro, you messed up\n\r")

    def handle_retransmit(self, message: WorkQ_Message, ser_han: SerialHandler):
        #If retransmit counter is within range, retransmit the same message
        if self.retransmit_counter < 2:
            self.retransmit_counter += 1
            self.start_sending_msg(message, ser_han)
        else:
            self.sys_state = SystemState.SYS_SEND_NEXT_CMD
            self.handle_send_next_cmd()

    def handle_send_next_cmd(self):
        #Send next cmd
        self.sys_state = SystemState.SYS_WAIT
        #reset retransmit counter
        self.retransmit_counter = 0 
    def handle_timeout(self, message: WorkQ_Message, ser_han: SerialHandler):

        #Call retransmit 
        self.sys_state = SystemState.SYS_RETRANSMIT
        self.handle_retransmit(message, ser_han)

    def simulate_rocket_response(self):
        # Simulate different responses from Rocket
        responses = ["ACK", "NAK", "TIMEOUT"]
        return random.choice(responses)
    
    def exit(self):
        """
        Exit the state machine for RCU and Rocket serial communication by setting RCU state to be uninitialized 
        and event to RCU Exit.

        """
        self.sys_state = SystemState.SYS_INVALID
        self.rocket_state = RocketState.RS_NONE
        self.event = Event.RCU_EXIT

    def get_rcu_state(self):
        """
        Return the current state of the RCU.

        """
        print("\nThe current RCU state:")
        return self.sys_state

    def get_rocket_state(self):
        """"
        Return the current state of the rocket.

        """
        print("\nThe current rocket state:")
        return self.rocket_state
    


#Test - Do NOT commit
test = StateMachineManager()
print(test.start())
print(test.get_rcu_state())
print(test.get_rocket_state())








