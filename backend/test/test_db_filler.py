import random
import time
from pocketbase import Client

client = Client("http://127.0.0.1:8090")
i = 0

while 1:
    print("Troll db")
    random_ib = "{:.2f}".format(random.uniform(0,100))
    random_pv = "{:.2f}".format(random.uniform(0,100))
    i += 1
    client.collection('CommandMessage').create({
        "command_param": 0,
        "target": "DMB",
        "command": "RSC_OPEN_VENT",
        "source_sequence_num": i,
    })
    time.sleep(1)