#include <stdio.h>
#include <linux/joystick.h>

#include "../lib/WiringPi/wiringPi/wiringPi.h""

wiringPiSetupGpio();

int left_wheel_a = 23; // forward
int left_wheel_b = 24; // forward
int right_wheel_a = 27; // backwards
int right_wheel_b = 22; // backwards

void gpio_setup() {
    pinMode(left_wheel_a, OUTPUT);
    pinMode(left_wheel_b, OUTPUT);
    pinMode(right_wheel_a, OUTPUT);
    pinMode(right_wheel_b, OUTPUT);
}

void drive_forward() {
    digitalWrite(left_wheel_a, HIGH);
    digitalWrite(left_wheel_b, HIGH);
    digitalWrite(right_wheel_a, HIGH);
    digitalWrite(right_wheel_b, HIGH);
}

void turn_forward_left() {
    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, LOW);
    digitalWrite(right_wheel_a, HIGH);
    digitalWrite(right_wheel_b, LOW);
}
    
void rotate_left() {
    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, HIGH);
    digitalWrite(right_wheel_a, HIGH);
    digitalWrite(right_wheel_b, LOW);
}

void turn_reverse_left() {
    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, LOW);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, HIGH);
}

void turn_forward_right() {
    digitalWrite(left_wheel_a, HIGH);
    digitalWrite(left_wheel_b, LOW);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, LOW);
}

void rotate_right() {
    digitalWrite(left_wheel_a, HIGH);
    digitalWrite(left_wheel_b, LOW);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, HIGH);
}

void turn_reverse_right() {

    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, HIGH);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, LOW);
}

void drive_reverse() {
    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, HIGH);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, HIGH);
}

void stop() {
    digitalWrite(left_wheel_a, LOW);
    digitalWrite(left_wheel_b, LOW);
    digitalWrite(right_wheel_a, LOW);
    digitalWrite(right_wheel_b, LOW);
}

def get_joystick_axes():
    #returns LEFT STICK: L->R, U->D,  RIGHT_STICK: l->R, U->D
    return [pygame.joystick.Joystick(0).get_axis(0), pygame.joystick.Joystick(0).get_axis(1),
            pygame.joystick.Joystick(0).get_axis(3), pygame.joystick.Joystick(0).get_axis(4)]

def choose_drive_direction():
    joystick_axes = get_joystick_axes()
    if abs(joystick_axes[0]) < 0.25 and abs(joystick_axes[1]) < 0.25:
        print("Stop")
        stop()
    elif joystick_axes[0] < 0:
        if abs(joystick_axes[1]) < 0.3:
            print("Rotate left")
            rotate_right()
        elif -0.3 > joystick_axes[1] > -0.98:
            print("Turn forward left")
            turn_forward_right()
        elif 0.3 < joystick_axes[1] < 0.98:
            print("Turn reverse left")
            turn_reverse_right()
        else:
            if joystick_axes[1] < -0.98:
                print("Drive forward")
                drive_forward()
            elif joystick_axes[1] > 0.98:
                print("Drive reverse")
                drive_reverse()
    else:
        if abs(joystick_axes[1]) < 0.3:
            print("Rotate right")
            rotate_left()
        elif -0.3 > joystick_axes[1] > -0.98:
            print("Turn forward right")
            turn_forward_left()
        elif 0.3 < joystick_axes[1] < 0.98:
            print("Turn reverse right")
            turn_reverse_left()
        else:
            if joystick_axes[1] < -0.98:
                print("Drive forward")
                drive_forward()
            elif joystick_axes[1] > 0.98:
                print("Drive reverse")
                drive_reverse()

gpio_setup()
pygame.joystick.init()

while True:
    choose_drive_direction()