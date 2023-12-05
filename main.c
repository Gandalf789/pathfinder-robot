#include <stdio.h>
#include <robot.h>
#include "module1.h"

#define TIME_STEP 64

int main(int argc, char **argv) {
    wb_robot_init();
    printf("\n--------\n");
    while (wb_robot_step(TIME_STEP) != -1) {
        printf("[^] = %.2f\n", front_sensors());
        printf("[<] = %.2f\n", left_sensors());
        printf("[>] = %.2f\n", right_sensors());

        //It does not work currently, it might work with some tweaking of the threshold values

        if(((front_sensors() > 160) && (right_sensors() > 160)) && (left_sensors() < 140)){
            go_left();
        }
        if(((front_sensors() > 160) && (right_sensors() < 140)) && (left_sensors() > 160)){
            go_right();
        }
        if((front_sensors() < 140) || ((right_sensors() > 160) && (left_sensors() > 160))){
            go_forward(0.8);
        }
        if((front_sensors() > 160) && ((right_sensors() < 140) && (left_sensors() < 140))){
            go_left();
        }
        printf("\n--------\n");
    }
    wb_robot_cleanup();

  return 0;
}

