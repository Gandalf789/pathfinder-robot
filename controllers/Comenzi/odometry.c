//
// Created by timo on 12/30/23.
//

#include <position_sensor.h>
#include <distance_sensor.h>

/*Constants*/
#define WHEEL_RADIUS 0.02


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
    static double distArray[3] = {0};// stores the distances of every path
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
            default:
                break;
        }
        if(i >= 3){//if the counter is more than 3 that usually means that both walls have been measured and the fastest way has been browsed
            distArray[2] = 1;
        }
    }
    return distArray;
}
