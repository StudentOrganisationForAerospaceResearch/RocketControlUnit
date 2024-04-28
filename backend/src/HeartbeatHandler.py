# General imports =================================================================================
import multiprocessing as mp
import threading
import time
# Project specific imports ========================================================================
from proto.Python.ControlMessage_pb2 import ControlMessage, Heartbeat
from src.support.CommonLogger import logger
from src.ThreadManager import THREAD_MESSAGE_HEARTBEAT, THREAD_MESSAGE_HEARTBEAT_SERIAL, THREAD_MESSAGE_SERIAL_WRITE, WorkQ_Message
import proto.Python.CoreProto_pb2 as ProtoCore

class HeartbeatHandler:
    def __init__(self, thread_name: str, thread_workq: mp.Queue, message_handler_workq: mp.Queue, timeout: int):
        logger.info("HeartbeatHandler initializing")
        HeartbeatHandler.thread_workq = thread_workq
        HeartbeatHandler.send_message_workq = message_handler_workq
        HeartbeatHandler.thread_name = thread_name
        self.timeout = timeout
        self.timer = None
        self.running = False
        self.dmb_thread = None

        logger.success(f"Successfully started {thread_name} thread")

    def reset_timer(self):
        if self.timer is not None:
            self.timer.cancel()

        self.timer = threading.Timer(self.timeout, self.handle_timeout)
        self.timer.start()

    def handle_timeout(self):
        logger.error("Heartbeat timeout, aborting the DMB")
        self.stop()
        HeartbeatHandler.send_message_workq.put(
            WorkQ_Message(
                HeartbeatHandler.thread_name,
                'radio',
                THREAD_MESSAGE_SERIAL_WRITE,
                ("RSC_ANY_TO_ABORT", "NODE_DMB", 0, 0,)
            )
        )

    def stop(self):
        self.running = False
        if self.dmb_thread is not None:
            self.dmb_thread.join()
            self.dmb_thread = None
        if self.timer is not None:
            self.timer.cancel()

    def start(self):
        self.running = True
        self.dmb_thread = threading.Thread(target=self.dmb_heartbeat_send)
        self.dmb_thread.start()
        self.reset_timer()

    def dmb_heartbeat_send(self):
        while self.running:
            msg = ControlMessage()
            msg.source = ProtoCore.NODE_RCU
            msg.target = ProtoCore.NODE_DMB
            hbMsg = Heartbeat()
            hbMsg.hb_response_sequence_num = 1234
            msg.hb.CopyFrom(hbMsg)

            self.send_message_workq.put(
                WorkQ_Message(
                    self.thread_name,
                    'radio', 
                    THREAD_MESSAGE_HEARTBEAT_SERIAL,
                    (msg.SerializeToString(),)
                )
            )
            time.sleep(5)


def heartbeat_thread(thread_name: str, heartbeat_workq: mp.Queue, message_handler_workq: mp.Queue):
    """
    The main loop of the heartbeat handler. This function will process the messages from the workq and spawn the dmb heartbeat thread.
    """

    # 20 minutes
    timeout_seconds = 1200
    heartbeat_handler = HeartbeatHandler(thread_name, heartbeat_workq, message_handler_workq, timeout_seconds)
    heartbeat_handler.start()

    while (1):
        if not process_workq_message(heartbeat_workq.get(block=True), heartbeat_handler):
            return


def process_workq_message(message: WorkQ_Message, heartbeat_handler: HeartbeatHandler) -> bool:
    """
    Process the message from the workq.

    Args:
        message (WorkQ_Message):
            The message from the workq.
    """
    logger.debug(f"Processing heartbeat workq message: {message.message_type}")
    messageID = message.message_type

    if messageID == THREAD_MESSAGE_HEARTBEAT:
        logger.debug(f"Resetting Heartbeat Timer")
        if heartbeat_handler.running == False:
            heartbeat_handler.start()
        else:
            heartbeat_handler.reset_timer()
        return True
    else:
        logger.error(f"Unknown message type: {messageID}")
    return True
