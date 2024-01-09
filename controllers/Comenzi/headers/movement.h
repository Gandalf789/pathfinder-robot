/****************************************************************
 * movement.h - Header file for the movement module             *
 * author: Timotei Ciupei                                       *
 * version: 8/1/24                                              *
 * updates: https://github.com/Gandalf789/pathfinder-robot      *
 ****************************************************************/

#ifndef COMENZI_MOVEMENT_H
#define COMENZI_MOVEMENT_H

extern WbDeviceTag init_motor_right();
extern WbDeviceTag init_motor_left();

extern void turn_sharp_right(WbDeviceTag left_motor, WbDeviceTag right_motor, int);
extern void turn_left(WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void turn_right(WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void turn_corner_left(WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void turn_corner_right(WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void forward(WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void stop(WbDeviceTag left_motor, WbDeviceTag right_motor);

#endif //COMENZI_MOVEMENT_H
