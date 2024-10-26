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
# Project specific imports ========================================================================
from backend.src.StateMachine.BaseStateMachine import BaseStateMachine

# Class Definitions ===============================================================================
@unique
class State(Enum):
    """
    Represents the states of the rocket and the rcu. If there is a use case to make the state class more general,
    and the RocketState and RCUState to be a subclass, we can consider that option at that time. Right now, we don't have
    enough states to justify using inheritance and subclasses.

    """
    RCU_INITIALIZED = 0
    RCU_WAIT = 1
    RCU_RETRANSMIT = 2
    RCU_TIMEOUT = 3
    RCU_SEND_NEXT_CMD = 4
    ROCKET_LISTENING = 5
    ROCKET_INITIALIZED = 6
    ROCKET_READY_FOR_CMD = 7

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
    ROCKET_LISTENING = 5
    ROCKET_RCVD_CMD = 6
    ROCKET_SEND_ACK = 7

class StateMachineManager(BaseStateMachine):
    """
    Manage state transitions for the communication between the RCU and the rocket. 
    """
    pass





