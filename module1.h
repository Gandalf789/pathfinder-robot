//
// Created by timo on 11/26/23.
//

#ifndef MYWEBOTSCONTROLLER_MODULE1_H
#define MYWEBOTSCONTROLLER_MODULE1_H

/*Movement*/
void go_forward(float);
void go_backwards(float);
void stop();
void go_left();
void go_right();

/*Proximity sensors*/
double front_sensors();
double back_sensors();
double left_sensors();
double right_sensors();
#endif //MYWEBOTSCONTROLLER_MODULE1_H
