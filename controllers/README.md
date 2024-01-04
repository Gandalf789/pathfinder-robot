# Code documentation

### Contents
1. Structure of the code
2. movement.c
3. sensors.c
4. logic.c
5. odometry.c
7. main.c


## 1.Structure of the code

As explained before, the following is the schematic of the structure of the code

![Screenshot from 2024-01-03 18-58-52](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/15cf3726-084b-499f-8ad2-a99036611fdc)


## 2.  Movement.c

It initializes the two motors and sets the position to `INFINITY` so that their speed can be changed later.


## 3. Sensors.c

Initializes the two position sensors, the IR sensor and all 8 proximity sensors. 

Also, it outputes a array containing the values of the 8 proximity sensors.

## 4. Logic.c

The logic of the left wall following algorithm is described below 

![Screenshot from 2024-01-04 13-55-00](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/9cca28db-f4b6-4f2e-a21a-ff4da1ff82b2)

(The same but with the directions inversed for the right wall following function)

## 5. Odometry.c

Module used to calculate the distance runned and also when a milestone has been achieved ( the start or the finish line).

it stores this values in an array.

## 6. Main.c

Main source file of the app. 


