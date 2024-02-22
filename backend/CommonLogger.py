from datetime import datetime
import os
from loguru import logger

class CommonLogger():

    logger = logger

    def __init__(self, log_to_terminal = True): #TODO: write description
        CommonLogger.log_to_terminal = log_to_terminal
        CommonLogger.start_logs()

    @staticmethod
    def start_logs(): #TODO: write description
        dir_path = os.path.dirname(os.path.realpath(__file__)) + "/logs/"
        time_now = datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
        os.makedirs(dir_path, exist_ok=True)
        if not CommonLogger.log_to_terminal:
            CommonLogger.logger.remove()
        log_file_path = os.path.join(dir_path, f"log_{time_now}.log")
        CommonLogger.logger.add(log_file_path, format="{time:HH:mm:ss} {level} {message}", level="DEBUG")