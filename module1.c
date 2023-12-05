//
// Created by timo on 11/26/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <robot.h>
#include <motor.h>
#include <distance_sensor.h>
#include <utils/ansi_codes.h>
#include <led.h>

#define TIME_STEP 64
#define MAX_SPEED 6.28
#define DESTINATION 290

double *init_prox_sensors();
WbDeviceTag init_right_motor();
WbDeviceTag init_left_motor();

/*--->The function returns a pointer to a static array containing
 * all the 8 values of the proximity sensors.
 *
 *--->To use it simply create a type double pointer and then assign it
 * the init_prox_sensors() value, after which you can go through
 * the values of the array with a for loop with pointer arithmetics.
 * */
double *init_prox_sensors(){

    static double sensor_values[8] = {0};

    //Assigning a tag for every sensor
    WbDeviceTag prox_sensor0 = wb_robot_get_device("ps0");
    WbDeviceTag prox_sensor1 = wb_robot_get_device("ps1");
    WbDeviceTag prox_sensor2 = wb_robot_get_device("ps2");
    WbDeviceTag prox_sensor3 = wb_robot_get_device("ps3");
    WbDeviceTag prox_sensor4 = wb_robot_get_device("ps4");
    WbDeviceTag prox_sensor5 = wb_robot_get_device("ps5");
    WbDeviceTag prox_sensor6 = wb_robot_get_device("ps6");
    WbDeviceTag prox_sensor7 = wb_robot_get_device("ps7");

    //An array of the tags
    WbDeviceTag sensors[8] = {prox_sensor0, prox_sensor1, prox_sensor2, prox_sensor3, prox_sensor4,
                              prox_sensor5, prox_sensor6, prox_sensor7};

    //Activate every sensor and getting its current value
    for (int i = 0; i < 8; ++i) {
        wb_distance_sensor_enable(sensors[i], TIME_STEP);
        sensor_values[i] = wb_distance_sensor_get_value(sensors[i]);
    }

    //Returns an array with all the sensors values
    return sensor_values;
}

/*---->Initialize the right motor and sets the position to INFINITY*/
WbDeviceTag init_right_motor(){
    WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
    wb_motor_set_position(right_motor,  INFINITY);
    return right_motor;
}
/*---->Initialize the left motor and sets the position to INFINITY*/
WbDeviceTag init_left_motor(){
    WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
    wb_motor_set_position(left_motor,INFINITY );
    return left_motor;
}

/*Direction functions*/
void go_forward(float speed){
    printf(" %sgoing forward%s\n", ANSI_GREEN_BACKGROUND, ANSI_RESET);
    wb_motor_set_velocity(init_left_motor(), speed * MAX_SPEED);
    wb_motor_set_velocity(init_right_motor(), speed * MAX_SPEED);
}
void go_backwards(float speed){
    printf(" %sgoing backwards%s\n", ANSI_YELLOW_BACKGROUND, ANSI_RESET);
    wb_motor_set_velocity(init_left_motor(), -speed * MAX_SPEED);
    wb_motor_set_velocity(init_right_motor(), -speed * MAX_SPEED);
}
void go_left(){
    printf(" %sgoing left%s\n", ANSI_BLUE_BACKGROUND, ANSI_RESET);
    wb_motor_set_velocity(init_left_motor(), 0.4 * MAX_SPEED);
    wb_motor_set_velocity(init_right_motor(), 0 * MAX_SPEED);
}
void go_right(){
    printf(" %sgoing right%s\n", ANSI_MAGENTA_BACKGROUND, ANSI_RESET);
    wb_motor_set_velocity(init_left_motor(), 0 * MAX_SPEED);
    wb_motor_set_velocity(init_right_motor(), 0.4 * MAX_SPEED);
}
void stop(){
    WbDeviceTag led1 = wb_robot_get_device("led0");
    wb_motor_set_velocity(init_right_motor(), 0);
    wb_motor_set_velocity(init_left_motor(), 0);
    printf(" %sstoped%s\n", ANSI_RED_BACKGROUND, ANSI_RESET);
    wb_led_set(led1, 1);

}


double front_sensors(){
    return (*(init_prox_sensors()) + *(init_prox_sensors() + 7));
    //A value above 160 means an obstacle
}
double back_sensors(){
    return (*(init_prox_sensors() + 3) + *(init_prox_sensors() + 4));
}
double left_sensors(){
    return (*(init_prox_sensors() + 1) + *(init_prox_sensors() + 2));
}
double right_sensors(){
    return (*(init_prox_sensors() + 5) + *(init_prox_sensors() + 6));
}


