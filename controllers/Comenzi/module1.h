//
// 11/26/23.
//

#ifndef MYWEBOTSCONTROLLER_MODULE1_H
#define MYWEBOTSCONTROLLER_MODULE1_H

/*Initialization*/
WbDeviceTag init_motor_right();
WbDeviceTag init_motor_left();
WbDeviceTag init_pos_left();
WbDeviceTag init_pos_right();
WbDeviceTag init_ir();
//double *init_prox_sensors();//only useful if you need the raw data of the prox sensors

/*Movement*/
void stop(WbDeviceTag left_motor, WbDeviceTag right_motor);
void follow_left(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);
void follow_right(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);

/*Distance*/
double *dist_calc(WbDeviceTag ir_sensor, int threshold, WbDeviceTag left_pos_sensor, WbDeviceTag right_pos_sensor);

#endif //MYWEBOTSCONTROLLER_MODULE1_H
