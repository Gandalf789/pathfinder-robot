/****************************************************************
 * odometry.h - Header file for the odometry module             *
 * author: Timotei Ciupei                                       *
 * version: 8/1/24                                              *
 * updates: https://github.com/Gandalf789/pathfinder-robot      *
 ****************************************************************/

#ifndef COMENZI_ODOMETRY_H
#define COMENZI_ODOMETRY_H

extern double *dist_calc(WbDeviceTag ir_sensor, int threshold, WbDeviceTag left_pos_sensor, WbDeviceTag right_pos_sensor);

#endif //COMENZI_ODOMETRY_H
