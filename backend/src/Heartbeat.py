import threading
import time

class HeartbeatHandler:
    def __init__(self, timeout):
        self.timeout = timeout
        self.timer = None
        self.heartbeat_collection = PB.collection('Heartbeat')

    def start(self):
        self.subscribe_to_heartbeat()
        self.reset_timer()

    def subscribe_to_heartbeat(self):
        self.heartbeat_collection.subscribe('*', self.handle_heartbeat)

    def handle_heartbeat(self, heartbeat):
        print("Received heartbeat")
        self.reset_timer()

    def reset_timer(self):
        if self.timer is not None:
            self.timer.cancel()

        self.timer = threading.Timer(self.timeout, self.handle_timeout)
        self.timer.start()

    def handle_timeout(self):
        print("Heartbeat timeout, sending command")

heartbeat_handler = HeartbeatHandler(10) # seconds
heartbeat_handler.start()