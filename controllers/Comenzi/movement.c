//
// Created by timo on 12/30/23.
//

#include <robot.h>
#include <motor.h>
#include <utils/ansi_codes.h>

/*Constants*/
#define MAX_SPEED 6.28
#define TIME_STEP 64

/*Motors initialization*/

/*Initialize the right motor and sets the position to INFINITY*/
WbDeviceTag init_motor_right(){
    WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
    wb_motor_set_position(right_motor,  INFINITY);
    return right_motor;
}
/*Initialize the left motor and sets the position to INFINITY*/
WbDeviceTag init_motor_left(){
    WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
    wb_motor_set_position(left_motor,INFINITY );
    return left_motor;
}


/*Specific movement functions*/

void turn_left( WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, MAX_SPEED/2);
    wb_motor_set_velocity(right_motor, -MAX_SPEED/2);
}
void turn_right( WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, -MAX_SPEED/2);
    wb_motor_set_velocity(right_motor, MAX_SPEED/2);
}
void turn_corner_left( WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, MAX_SPEED/8);
    wb_motor_set_velocity(right_motor, MAX_SPEED);
}
void turn_corner_right( WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, MAX_SPEED);
    wb_motor_set_velocity(right_motor, MAX_SPEED/8);
}
void forward(WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, MAX_SPEED);
    wb_motor_set_velocity(right_motor, MAX_SPEED);
}
/*Function used to turn in a safe way to the right in the case that the fastest way is the right wall
 * It uses the time elapsed as a measure on when to stop rather than sensors data*/
void turn_sharp_right(WbDeviceTag left_motor, WbDeviceTag right_motor, int turn_duration){
    int elapsed_time = 0;
    wb_motor_set_velocity(left_motor, 0);
    wb_motor_set_velocity(right_motor, MAX_SPEED/2);
    while(elapsed_time < turn_duration){
        wb_robot_step(TIME_STEP);
        elapsed_time += TIME_STEP;
    }
}
/*Completely stops the robot*/
void stop(WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, 0);
    wb_motor_set_velocity(right_motor, 0);
    printf("%s%s[<][^][>]%s\n--------%c\n", ANSI_BOLD, ANSI_RED_FOREGROUND, ANSI_RESET, ANSI_CLEAR_CONSOLE());
}