/****************************************************************
 * sensors.h - Header file for the sensors module               *
 * author: Timotei Ciupei                                       *
 * version: 8/1/24                                              *
 * updates: https://github.com/Gandalf789/pathfinder-robot      *
 ****************************************************************/

#ifndef COMENZI_SENSORS_H
#define COMENZI_SENSORS_H

extern WbDeviceTag init_ir();
extern WbDeviceTag init_pos_left();
extern WbDeviceTag init_pos_right();
extern double *init_prox_sensors();

#endif //COMENZI_SENSORS_H
