#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#include "../lib/WiringPi/wiringPi/wiringPi.h"
#include <stdlib.h>

#define CONTROLLER "/dev/input/js0"

#define LEFT_WHEEL_A 23 // forward
#define LEFT_WHEEL_B 24 // forward
#define RIGHT_WHEEL_A 27 // backwards
#define RIGHT_WHEEL_B 22 // backwards


void gpio_setup() {
    pinMode(LEFT_WHEEL_A, OUTPUT);
    pinMode(LEFT_WHEEL_B, OUTPUT);
    pinMode(RIGHT_WHEEL_A, OUTPUT);
    pinMode(RIGHT_WHEEL_B, OUTPUT);
}

void drive_forward() {
    printf("Drive forward");
    digitalWrite(LEFT_WHEEL_A, HIGH);
    digitalWrite(LEFT_WHEEL_B, HIGH);
    digitalWrite(RIGHT_WHEEL_A, HIGH);
    digitalWrite(RIGHT_WHEEL_B, HIGH);
}

void turn_forward_left() {
    printf("Turn forward left");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, LOW);
    digitalWrite(RIGHT_WHEEL_A, HIGH);
    digitalWrite(RIGHT_WHEEL_B, LOW);
}
    
void rotate_left() {
    printf("Rotate left");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, HIGH);
    digitalWrite(RIGHT_WHEEL_A, HIGH);
    digitalWrite(RIGHT_WHEEL_B, LOW);
}

void turn_reverse_left() {
    printf("Turn reverse left");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, LOW);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, HIGH);
}

void turn_forward_right() {
    printf("Turn forward right");
    digitalWrite(LEFT_WHEEL_A, HIGH);
    digitalWrite(LEFT_WHEEL_B, LOW);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, LOW);
}

void rotate_right() {
    printf("Rotate right");
    digitalWrite(LEFT_WHEEL_A, HIGH);
    digitalWrite(LEFT_WHEEL_B, LOW);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, HIGH);
}

void turn_reverse_right() {
    printf("Turn reverse right");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, HIGH);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, LOW);
}

void drive_reverse() {
    printf("Drive reverse");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, HIGH);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, HIGH);
}

void stop() {
    printf("Stop");
    digitalWrite(LEFT_WHEEL_A, LOW);
    digitalWrite(LEFT_WHEEL_B, LOW);
    digitalWrite(RIGHT_WHEEL_A, LOW);
    digitalWrite(RIGHT_WHEEL_B, LOW);
}

//returns LEFT STICK: L->R, U->D,  RIGHT_STICK: L->R, U->D

void choose_drive_direction(int X, int Y, int RX, int RY) {
    if(abs(X) < 5000 && abs(Y) < 5000) {
        stop();
    }
    else if(X < 0) {
        if(abs(Y) < 9830) {
            rotate_right();
        } else if(-9830 > Y > -32111) {
            turn_forward_right();
        } else if(9830 < Y < 32111) {
            turn_reverse_right();
        } else {
            if(Y < -32111) {
                drive_forward();
            } else if(Y > 32111) {
                drive_reverse();
            }
        }
    } else {
        if(abs(Y) < 9830) {
            rotate_left();
        } else if(-9830 > Y > -32111) {
            turn_forward_left();
        } else if(9830 < Y < 32111) {
            turn_reverse_left();
        } else {
            if(Y < -32111) {
                drive_forward();
            } else if(Y > 32111) {}
                drive_reverse();
        }
    }
}

wiringPiSetupGpio();

int main()
{
	int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];
	struct js_event js;

	if( ( joy_fd = open(CONTROLLER, O_RDONLY)) == -1 )
	{
		printf( "Couldn't open joystick\n" );
		return -1;
	}

	ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
	ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

	axis = (int *) calloc( num_of_axis, sizeof( int ) );
	button = (char *) calloc( num_of_buttons, sizeof( char ) );

	printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
		, name_of_joystick
		, num_of_axis
		, num_of_buttons );

	fcntl( joy_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */

	while( 1 ) 	/* infinite loop */
	{

			/* read the joystick state */
		read(joy_fd, &js, sizeof(struct js_event));
		
			/* see what to do with the event */
		switch (js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS:
				axis   [ js.number ] = js.value;
				break;
			case JS_EVENT_BUTTON:
				button [ js.number ] = js.value;
				break;
		}

        choose_drive_direction(axis[0], axis[1], axis[3], axis[4]);

        /*
			// print the results
		printf( "X: %6d  Y: %6d  ", axis[0], axis[1] );
		
		if( num_of_axis > 2 )
			printf("Z: %6d  ", axis[2] );
			
		if( num_of_axis > 3 )
			printf("RX: %6d  ", axis[3] );

        if ( num_of_axis > 4)
            printf("RY: %6d  ", axis[4] );
			
		for( x=0 ; x<num_of_buttons ; ++x )
			printf("B%d: %d  ", x, button[x] );

		printf("  \r");
        */
		fflush(stdout);
	}

	close( joy_fd );	/* too bad we never get here */
	return 0;
}