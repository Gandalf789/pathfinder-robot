//
// Created by timo on 12/30/23.
//

#include <robot.h>
#include <position_sensor.h>
#include <distance_sensor.h>

/*Constants*/
#define TIME_STEP 64


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
