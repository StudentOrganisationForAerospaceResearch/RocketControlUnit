from pocketbase import Client
import time 
import random

client = Client("http://127.0.0.1:8090")

while(1):
    random_float = "{:.2f}".format(random.uniform(0,100))
    client.collection('sensors').create({
        "tc1": random_float,
    })
    time.sleep(1)
