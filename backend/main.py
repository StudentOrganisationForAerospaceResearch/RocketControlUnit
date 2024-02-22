from DatabaseHandler import DatabaseHandler
# from SerialHandler import SerialHandler

from CommonLogger import CommonLogger

LOG_TO_TERMINAL = True

if __name__ == "__main__":
  CommonLogger(LOG_TO_TERMINAL)

  db_thread = DatabaseHandler()
  db_thread.start()

  # serial_thread = SerialHandler()
  # serial_thread.start()

  while 1:
    pass
