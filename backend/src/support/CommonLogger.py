from datetime import datetime
import os, git
from loguru import logger

git_repo = git.Repo(__file__, search_parent_directories=True).git.rev_parse("--show-toplevel")
log_path = os.path.join(git_repo, "backend", "logs")

LOG_TO_TERMINAL = True
DISABLE_LOGGING = False

logger = logger

if not LOG_TO_TERMINAL or DISABLE_LOGGING:
    logger.remove()

if not DISABLE_LOGGING:
    time_now = datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
    os.makedirs(log_path, exist_ok=True)
    log_file_path = os.path.join(log_path, f"log_{time_now}.log")
    logger.add(log_file_path, format="{time:HH:mm:ss} {level} {message}", level="DEBUG", enqueue=True)
