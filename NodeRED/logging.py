from json import load
from time import sleep
import csv
import random
import math
from datetime import datetime

dt=datetime.now()

col_names=["time","nos1Temp","nos2Temp","nos1LoadCell","nos2LoadCell","ac1","ac2","p1","p2","p3","p4","AirTemp","LoadCell","Continuity"]
with open("log.txt",'w',newline='') as f:
        my_writer = csv.writer(f, delimiter = ',')
        my_writer.writerow(col_names)


Continuity=0
while True:
    nos1Temp=round(random.random()*100000%3,2)-180
    nos2Temp=round(random.random()*100000%3,2)-172
    nos1LoadCell=round(24.6+random.random()*100000%0.2,4)
    nos2LoadCell=round(24.6+random.random()*100000%0.2,4)
    ac1=round(random.random()*100000%3+42,2)
    ac2=round(random.random()*100000%3+35,2)
    p1=round(random.random()+22,2)
    p2=round(random.random()+14,2)
    p3=round(random.random()+22,2)
    p4=round(random.random()+14,2)
    AirTemp=round(random.random()*100000%3+22,2)
    LoadCell=round(62.2+random.random()*100000%0.2,4)
    if LoadCell<0:
        LoadCell=100
    Continuity=(Continuity+1)%2000  

    status=[dt,nos1Temp,nos2Temp,nos1LoadCell,nos2LoadCell,ac1,ac2,p1,p2,p3,p4,AirTemp,LoadCell,Continuity]
    print(status)
    
    with open("log.txt",'a',newline='') as f:
        my_writer = csv.writer(f, delimiter = ',')
        my_writer.writerow(status)
        
    
    sleep(math.pi/4)
