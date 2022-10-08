import RPi.GPIO as GPIO
from time import sleep

GPIO.setwarnings(True)
 
GPIO.setmode(GPIO.BCM) 
GPIO.setup(40, GPIO.OUT)

while (True):
    GPIO.output(40, True) 
    sleep(2)
    GPIO.output(40, False)
    sleep(2)