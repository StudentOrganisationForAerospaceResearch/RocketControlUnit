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
import os, sys

# Project specific imports ========================================================================
dirname, _ = os.path.split(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'backend'))
sys.path.insert(0, os.path.join(dirname.split("backend", 1)[0], 'src/StateMachine'))
from src.StateMachine.BaseStateMachine import BaseStateMachine
# import proto.Python.CoreProto_pb2 as ProtoCore
# import src.StateMachine.BaseStateMachine as BaseStateMachine



# Class Definitions ===============================================================================
@unique
class State(Enum):
    """
    Represents the states of the rocket and the rcu. If there is a use case to make the state class more general,
    and the RocketState and RCUState to be a subclass, we can consider that option at that time. Right now, we don't have
    enough states to justify using inheritance and subclasses.

    """
    RCU_UNINITIALIZED = 0
    RCU_INITIALIZED = 1
    RCU_WAIT = 2
    RCU_RETRANSMIT = 3
    RCU_TIMEOUT = 4
    RCU_SEND_NEXT_CMD = 5
    ROCKET_UNINITIALIZED = 6
    ROCKET_LISTENING = 7
    ROCKET_INITIALIZED = 8
    ROCKET_READY_FOR_CMD = 9

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
    def start(self):
        """
        Start the state machine for RCU and Rocket serial communication by setting the RCU state to be 
        initialized and event to RCU Start.
        """
        self.rcu_state = State.RCU_INITIALIZED
        self.rocket_state = State.ROCKET_LISTENING
        self.event = Event.RCU_START

    def exit(self):
        """
        Exit the state machine for RCU and Rocket serial communication by by setting RCU state to be uninitialized 
        and event to RCU Exit.
        """
        self.rcu_state = State.RCU_UNINITIALIZED
        self.rocket_state = State.ROCKET_UNINITIALIZED
        self.event = Event.RCU_EXIT

    def get_rcu_state(self):
        print("\nThe current RCU state:")
        return self.rcu_state

    def get_rocket_state(self):
        print("\nThe current rocket state:")
        return self.rocket_state
    
    def get_event(self):
        print("\nThe current event:")
        return self.event

    def transition(self, event, from_state, to_state):
        #Check to make sure inputs are part of the enum list

        #Check if event is a valid transition from from_state

        #Check if event is a valid transition to to_state

        #if valid, then set the current event and current state

        #Idk if I want to code the update step separately from the transition step yet - prob to break it up tbh
        return



#Test - Do NOT commit
test = StateMachineManager()
print(test.start())
print(test.get_event())
print(test.get_rcu_state())
print(test.get_rocket_state())








