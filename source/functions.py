import RPi.GPIO as GPIO
import pygame

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
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 1)
    GPIO.output(right_wheel_b, 0)

def turn_forward_left():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 1)
    GPIO.output(right_wheel_b, 0)
    
def rotate_left():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 1)
    GPIO.output(right_wheel_a, 1)
    GPIO.output(right_wheel_b, 0)

def turn_reverse_left():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 1)

def turn_forward_right():
    GPIO.output(left_wheel_a, 1)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 0)

def rotate_right():
    GPIO.output(left_wheel_a, 1)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 1)

def turn_reverse_right():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 1)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 0)

def drive_reverse():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 1)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 1)

def stop():
    GPIO.output(left_wheel_a, 0)
    GPIO.output(left_wheel_b, 0)
    GPIO.output(right_wheel_a, 0)
    GPIO.output(right_wheel_b, 0)

def get_joystick_axes():
    pygame.joystick.init()
    #returns LEFT STICK: L->R, U->D,  RIGHT_STICK: l->R, U->D
    return [pygame.joystick.Joystick(0).get_axis(0), pygame.joystick.Joystick(0).get_axis(1),
            pygame.joystick.Joystick(0).get_axis(3), pygame.joystick.Joystick(0).get_axis(4)]

def choose_drive_direction():
    if abs(get_joystick_axes()[0]) < 0.25 and abs(get_joystick_axes()[1]) < 0.25:
        print("Stop")
        stop()
    elif abs(get_joystick_axes(0))
    elif get_joystick_axes()[0] < 0:
        if abs(get_joystick_axes()[1]) < 0.5:
            print("Rotate left")
            rotate_left()
        elif -0.5 > get_joystick_axes()[1] > -0.9:
            print("Turn forward left")
            turn_forward_left()
        elif 0.5 < get_joystick_axes()[1] < 0.9:
            print("Turn reverse left")
            turn_reverse_left()
        else:
            if get_joystick_axes()[1] > 0.9:
                print("Drive forward")
                drive_forward()
            elif get_joystick_axes()[1] < -0.9:
                print("Drive reverse")
                drive_reverse()
    else:
        if abs(get_joystick_axes()[1]) < 0.5:
            print("Rotate right")
            rotate_right()
        elif -0.5 > get_joystick_axes()[1] > -0.9:
            print("Turn forward right")
            turn_forward_right()
        elif 0.5 < get_joystick_axes()[1] < 0.9:
            print("Turn reverse right")
            turn_reverse_right()
        else:
            if get_joystick_axes()[1] > 0.9:
                print("Drive forward")
                drive_forward()
            elif get_joystick_axes()[1] < -0.9:
                print("Drive reverse")
                drive_reverse()


while True:
    choose_drive_direction()