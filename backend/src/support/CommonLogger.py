from datetime import datetime
import os, git
from loguru import logger

git_repo = git.Repo(__file__, search_parent_directories=True).git.rev_parse("--show-toplevel")
log_path = os.path.join(git_repo, "backend", "logs")

class CommonLogger():

    logger = logger

    def __init__(self, log_to_terminal = True):
        """
        Common logger class for the backend, provides thread
        safe logging to the terminal and to log files.
        
        Args:
            log_to_terminal (bool, optional): 
                Log to terminal. Defaults to True.
        """
        CommonLogger.log_to_terminal = log_to_terminal
        CommonLogger.start_logs()

    @staticmethod
    def start_logs():
        """
        Start the logs for the backend, create a log folder and
        log file for the current run of the backend.
        """
        time_now = datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
        os.makedirs(log_path, exist_ok=True)
        if not CommonLogger.log_to_terminal:
            CommonLogger.logger.remove()
        log_file_path = os.path.join(log_path, f"log_{time_now}.log")
        CommonLogger.logger.add(log_file_path, format="{time:HH:mm:ss} {level} {message}", level="DEBUG", enqueue=True)