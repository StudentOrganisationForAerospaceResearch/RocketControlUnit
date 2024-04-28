from datetime import datetime
import os
from loguru import logger


dirname, _ = os.path.split(os.path.abspath(__file__))
log_path = os.path.join(dirname.split("backend", 1)[0], 'backend', 'logs')

LOG_TO_TERMINAL = True
DISABLE_LOGGING = True

logger = logger

if not LOG_TO_TERMINAL or DISABLE_LOGGING:
    logger.remove()

if not DISABLE_LOGGING:
    time_now = datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
    os.makedirs(log_path, exist_ok=True)
    log_file_path = os.path.join(log_path, f"log_{time_now}.log")
    logger.add(log_file_path, format="{time:HH:mm:ss} {level} {message}", level="DEBUG", enqueue=True)
