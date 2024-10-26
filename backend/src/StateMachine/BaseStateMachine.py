"""
BaseStateMachine.py

Define a common Application Program Interface(API) for a set of State Machine subclasses. 
Enable code reuse and maintainability when the code base grows in the future. The implementation of the methods
are left for the subclasses that inherit from this class.

Since the BaseStateMachine is an abstract class. Do NOT instantiate this because there is no actual implementation.

"""

# General imports =================================================================================
from abc import ABC, abstractmethod

# Class Definitions ===============================================================================
class BaseStateMachine(ABC):

    @abstractmethod
    def enter_state(self):
        pass
    @abstractmethod
    def exit_state(self):
        pass
    @abstractmethod
    def update_state(self):
        pass
    @abstractmethod
    def get_next_state(self):
        pass
    @abstractmethod
    def on_trigger_enter_state(self):
        pass
    @abstractmethod
    def on_trigger_stay_state(self):
        pass
    @abstractmethod
    def on_trigger_exit_state(self):
        pass
