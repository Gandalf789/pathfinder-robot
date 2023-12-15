//
// Created by timo on 11/26/23.
//

#ifndef MYWEBOTSCONTROLLER_MODULE1_H
#define MYWEBOTSCONTROLLER_MODULE1_H

/*Initialization*/
WbDeviceTag init_right_motor();
WbDeviceTag init_left_motor();
WbDeviceTag init_left_pos();
WbDeviceTag init_right_pos();
//double *init_prox_sensors();

/*Movement*/
void stop(WbDeviceTag, WbDeviceTag);
void follow_left(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);
void follow_right(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);

/*Distance*/
double *dist_calc(WbDeviceTag, int, WbDeviceTag, WbDeviceTag);

#endif //MYWEBOTSCONTROLLER_MODULE1_H
