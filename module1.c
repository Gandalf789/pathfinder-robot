//
// 11/26/23.
//

#include <stdio.h>
#include <math.h>
#include <robot.h>
#include <motor.h>
#include <distance_sensor.h>
#include <utils/ansi_codes.h>
#include <position_sensor.h>



//Constants
#define TIME_STEP 64
#define MAX_SPEED 6.28
#define WHEEL_RADIUS 0.02
//#define AXLE_LENGTH 0.052


//Prototypes for module-only functions
double *init_prox_sensors();
void PrintAction(int);



//Initializations and tagging functions

/*The function returns a pointer to a static array containing
 * all the 8 values of the proximity sensors.
 *
 *To use it simply create a type double pointer and then assign it
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


/*Initializes and assigns the position sensor*/

WbDeviceTag init_pos_left(){
    WbDeviceTag left_position = wb_robot_get_device("left wheel sensor");
    wb_position_sensor_enable(left_position, TIME_STEP);
    return left_position;
}
WbDeviceTag init_pos_right(){
    WbDeviceTag right_position = wb_robot_get_device("right wheel sensor");
    wb_position_sensor_enable(right_position, TIME_STEP);
    return right_position;
}


/*Initializes and assigns the IR sensor*/
WbDeviceTag init_ir(){
    WbDeviceTag ir_sensor = wb_robot_get_device("ir");
    wb_distance_sensor_enable(ir_sensor, TIME_STEP);
    return ir_sensor;
}


/*Completely stops the robot*/
void stop(WbDeviceTag left_motor, WbDeviceTag right_motor){
    wb_motor_set_velocity(left_motor, 0);
    wb_motor_set_velocity(right_motor, 0);
    printf("%s%s[<][^][>]%s\n--------%c\n", ANSI_BOLD, ANSI_RED_FOREGROUND, ANSI_RESET, ANSI_CLEAR_CONSOLE());
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


/*Main movement functions*/

void follow_left(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor){
    double *snsr_ptr = init_prox_sensors();//gets the sensor data

    if( *(snsr_ptr + 7) > threshold_value){
        PrintAction(0);
        turn_left(left_motor, right_motor);
    }
    else{
        if(*(snsr_ptr + 5) > threshold_value){
            PrintAction(2);
            forward(left_motor, right_motor);
        }
        else{
            PrintAction(0);
            turn_corner_left(left_motor, right_motor);
        }
        if(*(snsr_ptr + 6) > threshold_value){
            PrintAction(1);
            turn_corner_right(left_motor, right_motor);
        }
    }
}
void follow_right(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor){
    double *snsr_ptr = init_prox_sensors();//gets the sensor data

    if( *(snsr_ptr + 0) > threshold_value){
        PrintAction(1);
        turn_right(left_motor, right_motor);
    }

    else{

        if(*(snsr_ptr + 2) > threshold_value){
            PrintAction(2);
            forward(left_motor, right_motor);
        }

        else{
            PrintAction(1);
            turn_corner_right(left_motor, right_motor);
        }

        if(*(snsr_ptr + 1) > threshold_value){
            PrintAction(0);
            turn_corner_left(left_motor, right_motor);
        }
    }
}

/*It prints the arrows, showing the movement*/
void PrintAction(int action){// action = 0 for <, 1 for >, 2 for ^
    switch (action) {
        case 0:
            printf("%s%s[<]%s[^][>]\n--------%c\n", ANSI_BOLD, ANSI_GREEN_FOREGROUND, ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        case 1:
            printf("%s[<][^]%s[>]%s\n--------%c\n", ANSI_BOLD,ANSI_GREEN_FOREGROUND,ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        case 2:
            printf("%s[<]%s[^]%s[>]\n--------%c\n", ANSI_BOLD, ANSI_GREEN_FOREGROUND,ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        default:
            puts("");
            break;
    }
}

/*Odometry for the robot*/
double odometry(WbDeviceTag left_position_sensor, WbDeviceTag right_position_sensor) {
    double l = wb_position_sensor_get_value(left_position_sensor);
    double r = wb_position_sensor_get_value(right_position_sensor);
    double dl = l * WHEEL_RADIUS;         // distance covered by left wheel in meter
    double dr = r * WHEEL_RADIUS;         // distance covered by right wheel in meter
    return (dl + dr)/2;
}

/*Calculates and asisgns the values for the first and second run to an array of doubles*/
double *dist_calc(WbDeviceTag line_sensor, int threshold, WbDeviceTag left_pos_sensor, WbDeviceTag right_pos_sensor){
    double distance = odometry(left_pos_sensor, right_pos_sensor);
    double ir_value = wb_distance_sensor_get_value(line_sensor);
    static double distArray[3] = {0};
    static int i = 0;
    if(ir_value > threshold && ir_value != 1000){
        i++;
        switch (i) {
            case 1:
                distArray[0] = distance;
                break;
            case 2:
                distArray[1] = distance - distArray[0];
                break;
            case 6:
                distArray[2] = 1;
                break;
            default:
                break;
        }
    }
    return distArray;
}





