/****************************************************************
 * E-puck controller                                            *
 * author: Timotei Ciupei                                       *
 * version: 8/1/24                                              *
 * updates: https://github.com/Gandalf789/pathfinder-robot      *
 ****************************************************************/


/*Headers*/
#include <stdio.h>
#include <webots/robot.h>
#include "headers/odometry.h"
#include "headers/logic.h"
#include "headers/movement.h"
#include "headers/sensors.h"


/*Constants*/
#define TIME_STEP 64
#define MAX_SPEED 6.28
#define WALL_THRESHOLD 80
#define COLOR_THRESHOLD 135


int main(int argc, char **argv) {
    wb_robot_init();//Necessary for the robot to function

    int sharp_turn_counter = 0;

    printf("\n--------\n");


    /*Initializes and assigns tags for the motors*/
    WbDeviceTag left_motor = init_motor_left();
    WbDeviceTag right_motor = init_motor_right();


    /*Starts position sensors and IR sensor*/
    WbDeviceTag left_pos = init_pos_left();
    WbDeviceTag right_pos = init_pos_right();
    WbDeviceTag color_sensor = init_ir();


   /*Main while loop*/
    while (wb_robot_step(TIME_STEP) != -1) {

        /*         Used only for seeing the actual numbers
            printf("[P0]=%.2f\n", *(dist_ptr));
            printf("[P1]=%.2f\n", *(dist_ptr + 1));
            for (int i = 5; i < 8; ++i) {
                printf("[%d]=%.2f\n", i, *(snsr_ptr + i));
            }
            printf("[IR]=%.2f\n", wb_distance_sensor_get_value(color_sensor));

        */




        double *dist_ptr = dist_calc(color_sensor, COLOR_THRESHOLD, left_pos, right_pos);//Pointer with the values of the 2 distances

        //double *snsr_ptr = init_prox_sensors();//Array of all 8 of the proximity sensors data (not neccesary for the program)

        if(*(dist_ptr + 1) == 0){//True until the last distance is measured

            //Main movement function until the both distances are found
            follow_left(WALL_THRESHOLD, left_motor, right_motor);

        }
        else{
            //If the right wall is faster, then take that way
            if(*(dist_ptr + 1) < *(dist_ptr)){

                /*The following block of code is used to turn only one time*/
                if(sharp_turn_counter == 0){
                    turn_sharp_right(left_motor, right_motor, 1000);
                    sharp_turn_counter++;
                }

                follow_right(WALL_THRESHOLD, left_motor, right_motor);
                printf("Driving through the fastest way (right wall) ...\n");
            }

            //If the left wall is faster, then take that way
            if(*(dist_ptr + 1) > *(dist_ptr)){
                follow_left(WALL_THRESHOLD, left_motor, right_motor);
                printf("Driving through the fastest way (left wall) ...\n");
            }

            //Used to determine when the robot arrives at the finish line for the second time
            if(*(dist_ptr + 2) == 1){
                stop(left_motor, right_motor);
                printf("Shortest path is the %s one\n", *(dist_ptr) > *(dist_ptr + 1) ? "second":"first");
                printf("with %.2fm\n", *(dist_ptr) > *(dist_ptr + 1) ? *(dist_ptr + 1):*(dist_ptr));
            }

        }
        printf("[I] = %f\t[II] = %f\t\n", *(dist_ptr), *(dist_ptr + 1));


        printf("\n--------\n");
    }
    /*End of while loop*/

    wb_robot_cleanup();

  return 0;
}



