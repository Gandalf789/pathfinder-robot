/****************************************************************
 * logic.h - Header file for the logic module                   *
 * author: Timotei Ciupei                                       *
 * version: 8/1/24                                              *
 * updates: https://github.com/Gandalf789/pathfinder-robot      *
 ****************************************************************/

#ifndef COMENZI_LOGIC_H
#define COMENZI_LOGIC_H

extern void follow_left(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);
extern void follow_right(int threshold_value, WbDeviceTag left_motor, WbDeviceTag right_motor);

#endif //COMENZI_LOGIC_H
