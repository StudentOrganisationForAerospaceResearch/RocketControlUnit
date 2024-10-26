# Python program showing
# abstract base class work
from abc import ABC, abstractmethod


class Polygon(ABC):

    @abstractmethod
    def noofsides(self):
        pass

    @abstractmethod
    def start(self):
        pass


class StateMachineManager(Polygon):
    """
    Manage state transitions for the communication between the RCU and the rocket. 
    """
    # def __init__(self):
    #     self.state = State(6)
    #     self.event = Event(3)
    def start(self):
        print("Im here")

#Test - Do NOT commit
test = StateMachineManager()
test.start()

class Triangle(Polygon):

    # overriding abstract method
    def noofsides(self):
        print("I have 3 sides")

    def start(self):
        print("Starting")


test = StateMachineManager()
test.start()