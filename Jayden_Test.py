import RPi.GPIO as GPIO 
from time import sleep 

GPIO.setwarnings(False) 
 
GPIO.setmode(GPIO.BCM) 
GPIO.setup(17, GPIO.OUT)

while (True):
    GPIO.output(17, True) 