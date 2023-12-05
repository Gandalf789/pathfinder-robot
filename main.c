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
        if(front_sensors() > 150 && right_sensors() > 130 && left_sensors() < 130){
            go_left();
        }
        if(front_sensors() > 150 && right_sensors() < 130 && left_sensors() > 130){
            go_right();
        }
        if(front_sensors() < 150 || (right_sensors() > 160 && left_sensors() > 160)){
            go_forward(0.8);
        }
        if(front_sensors() > 150 && right_sensors() > 150 && left_sensors() > 150){
            go_backwards(0.8);
        }
        printf("\n--------\n");
    }
    wb_robot_cleanup();

  return 0;
}

