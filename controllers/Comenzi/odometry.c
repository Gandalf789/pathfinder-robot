/*****************************************************************
 * odometry.c - Measures the distances                           *
 *****************************************************************/

#include <webots/robot.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>

/*Constants*/
#define WHEEL_RADIUS 0.02
#define TIME_STEP 64


/*Odometry for the robot*/
double odometry(WbDeviceTag left_position_sensor, WbDeviceTag right_position_sensor) {
    double left_wheel = wb_position_sensor_get_value(left_position_sensor);
    double right_wheel = wb_position_sensor_get_value(right_position_sensor);
    double dist_left = left_wheel * WHEEL_RADIUS;         // distance covered by left wheel in meter
    double dist_right = right_wheel * WHEEL_RADIUS;         // distance covered by right wheel in meter
    return (dist_left + dist_right)/2;
}

/*Deactivate the IR sensor*/
void deact_ir() {
    WbDeviceTag ir_sensor = wb_robot_get_device("ir");
    wb_distance_sensor_disable(ir_sensor);
}

double *dist_calc(WbDeviceTag line_sensor, int threshold, WbDeviceTag left_pos_sensor, WbDeviceTag right_pos_sensor){
    double distance = odometry(left_pos_sensor, right_pos_sensor);// calculates the distances based on position sensors

    double ir_value = wb_distance_sensor_get_value(line_sensor);//gets the values of the IR sensor

    int elapsed_time = 0;//used to measure time in a while loop

    static double distArray[3] = {0};// stores the distances of every path and when the robot has finished its job

    static int i = 0;//counts the amount of time the robot has scanned a black band


    if(ir_value > threshold && ir_value != 1000){

        /*The following block deactivates the IR sensor for a certain amount of time*/
        while(elapsed_time < 160){
            wb_robot_step(TIME_STEP);
            elapsed_time += TIME_STEP;
            deact_ir();
        }
        wb_distance_sensor_enable(line_sensor, TIME_STEP);
        /*End of the block*/

        i++;//increments the band measure

        /*Used to put the coresponding distance values to each run*/
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

