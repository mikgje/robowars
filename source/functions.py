import RPi.GPIO as GPIO

left_wheel_a = 23 # forward
left_wheel_b = 24 # forward
right_wheel_a = 27 # backwards
right_wheel_b = 22 # backwards

def gpio_setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(left_wheel_a, GPIO.OUT)
    GPIO.setup(left_wheel_b, GPIO.OUT)
    GPIO.setup(right_wheel_a, GPIO.OUT)
    GPIO.setup(right_wheel_b, GPIO.OUT)

def drive_forward():
    GPIO.output(left_wheel_a, 1)
    GPIO.output(right_wheel_a, 1)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_b, 0)

def turn_left():
    GPIO.output(left_wheel_a, 1)
    GPIO.output(right_wheel_b, 1)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 0)

def turn_right():
    GPIO.output(left_wheel_b, 1)
    GPIO.output(right_wheel_a, 1)
    GPIO.output(left_wheel_a, 0)
    GPIO.output(right_wheel_b, 0)
    
def drive_backward():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(left_wheel_b, -1)
    GPIO.output(right_wheel_b, -1)

def stop():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_b, 0)