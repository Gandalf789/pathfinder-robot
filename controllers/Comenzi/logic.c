/*****************************************************************
 * logic.c - Wall following commands                             *
 *****************************************************************/

#include <stdio.h>
#include <webots/robot.h>
#include <webots/utils/ansi_codes.h>
#include "headers/movement.h"
#include "headers/sensors.h"

//Prototypes for module-only functions
void PrintAction(int);


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
            printf("%s%s[<]%s[^][>]\n--------%c\n", ANSI_BOLD, ANSI_CYAN_FOREGROUND, ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        case 1:
            printf("%s[<][^]%s[>]%s\n--------%c\n", ANSI_BOLD,ANSI_CYAN_FOREGROUND,ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        case 2:
            printf("%s[<]%s[^]%s[>]\n--------%c\n", ANSI_BOLD, ANSI_CYAN_FOREGROUND,ANSI_RESET, ANSI_CLEAR_CONSOLE());
            break;
        default:
            puts("");
            break;
    }
}






