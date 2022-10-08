import RPi.GPIO as GPIO

GPIO.setwarnings(False) 
 
GPIO.setmode(GPIO.BCM) 
GPIO.setup(40, GPIO.OUT)

while (True):
    GPIO.output(40, True) 