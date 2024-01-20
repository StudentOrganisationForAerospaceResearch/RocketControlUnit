#
# FILE: Main.py (Python Test Project)
# BRIEF: 
# AUTHOR: Christopher Chan (cjchanx)
#
# PIP PACKAGE LIST: pip install cobs; pip install pyserial; pip install protobuf
#

#todo:  add writting load cell offset and slope to file, test

import sys
import Ethernet_handler as EtHan
import Serial_handler as SeHan
#import json

if __name__ == '__main__':
    #serial port needs to be initialized first to avoid race conditions to an uninitialized serial port
    SeHan.init_serial_port(sys.argv[1], sys.argv[2])
    EtHan.init_mqtt()

    while True:
        SeHan.handle_serial_message()
        #EtHan.soar_publish("CONTROL_SYS_STATE", json.dumps({"dmb_state": str("RS_TEST")}))
