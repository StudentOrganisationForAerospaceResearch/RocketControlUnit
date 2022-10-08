import RPi.GPIO as GPIO
from time import sleep

GPIO.setwarnings(True)
 
GPIO.setmode(GPIO.BCM) 
GPIO.setup(21, GPIO.OUT)

while (True):
    GPIO.output(21, True) 
    sleep(2)
    GPIO.output(21, False)
    sleep(2)