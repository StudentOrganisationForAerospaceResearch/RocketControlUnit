# FILE: Utils.py
# BRIEF: This file contains generic utility functions for the backend

# General imports =================================================================================
import os, sys, git
import multiprocessing as mp
from dataclasses import dataclass

# Project specific imports ========================================================================
import proto.Python.CoreProto_pb2 as ProtoCore

from src.support.CommonLogger import logger


# Constants ========================================================================================
THREAD_MESSAGE_KILL = 'stop'
THREAD_MESSAGE_DB_WRITE = 'db_write'
THREAD_MESSAGE_SERIAL_WRITE = 'serial_write'
THREAD_MESSAGE_DB_COMMAND_NOTIF = 'db_command_notif'
THREAD_MESSAGE_DB_BACKEND_NOTIF = 'db_backend_notif'
TEST_RECEIVE_SERIAL_MESSAGE = 'test_receive_serial_message'

UART_BAUDRATE = 115200
RADIO_BAUDRATE = 115200 #NOTE: might need to change this (57600 ???)

# Data Classes =====================================================================================
@dataclass
class WorkQ_Message:
    src_thread: str
    dest_thread: str
    message_type: str
    message: tuple

# Class Definitions ===============================================================================
class Utils:
    def __init__(self) -> None:
        Utils.thread_pool = dict()

    @staticmethod
    def start_threads():
        '''
        Start the threads in the thread pool
        '''
        for thread in Utils.thread_pool:
            if Utils.thread_pool[thread]['thread']:
                Utils.thread_pool[thread]['thread'].start()
        return

    @staticmethod
    def kill_threads():
        '''
        Kill the threads in the thread pool
        '''
        for thread in Utils.thread_pool:
            if Utils.thread_pool[thread]['thread']:
                Utils.get_workq(thread).put(THREAD_MESSAGE_KILL)
                Utils._get_thread(thread).join()

    @staticmethod
    def _get_workq(thread_name) -> mp.Queue:
        '''
        Get the work queue for the specified thread
        '''
        return Utils.thread_pool[thread_name]['workq']

    @staticmethod
    def _get_thread(thread_name) -> mp.Process:
        '''
        Get the work queue for the specified thread
        '''
        return Utils.thread_pool[thread_name]['thread']

    @staticmethod
    def handle_thread_messages():
        '''
        Handle the messages in the thread work queues
        '''
        message_workq = Utils.thread_pool['message_handler']['workq']

        if message_workq.empty():
            return
        
        message = message_workq.get()

        logger.debug(f"Handling thread messages from {message.src_thread} to {message.dest_thread} with message type: {message.message_type}")

        if message.dest_thread == "all_serial":
            for serial_thread in ['uart', 'radio']:
                if (serial_thread not in Utils.thread_pool) or (not Utils.thread_pool[serial_thread]['thread'].is_alive()):
                    logger.error(f"Attempting to send message to non-existent thread: {serial_thread}")
                    continue
                Utils.thread_pool[serial_thread]['workq'].put(message)
        else:
            if (message.dest_thread not in Utils.thread_pool) or (not Utils.thread_pool[message.dest_thread]['thread'].is_alive()):
                logger.error(f"Attempting to send message to non-existent thread: {message.dest_thread}")
                return
            dest_workq = Utils.thread_pool[message.dest_thread]['workq']
            if dest_workq:
                dest_workq.put(message)

    @staticmethod
    def get_node_from_str(target):
        """
        Get the ProtoCore.Node enum number value from the string target.
        """
        return ProtoCore.Node.DESCRIPTOR.values_by_name[target].number

    @staticmethod
    def get_command_from_str(target, command):
        """
        Get the command enum number value from the string command.
        """
        return target.DESCRIPTOR.values_by_name[command].number

    @staticmethod
    def get_node_from_enum(target):
        """
        Get the node name from the ProtoCore.Node enum number.
        """
        return ProtoCore.Node.DESCRIPTOR.values_by_number[target].name
    
    @staticmethod
    def get_message_from_enum(target):
        """
        Get the message name from the ProtoCore.Node enum number.
        """
        return ProtoCore.MessageID.DESCRIPTOR.values_by_number[target].name
