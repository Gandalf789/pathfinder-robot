# Pathfinding robot in a maze
### <sub>Finding the shortest path using the wall-following method</sub>
## _Documentation_


## Contents
1. [Installing Webots](#1-installing-webots)
2. [Extracting the .zip file](#2-extracting-the-zip-file)
1. [Opening the world file](#3-opening-the-world-file)
2. [Before running the simulation](#4-before-running-the-simulation)
3. [Running the simulation](#5-running-the-simulation)
4. [How it works](#6-how-it-works)
5. [Editing the source code](#6-editing-the-source-code)
6. [Structure of the code](#7-structure-of-the-code)


  ## 1. Installing Webots
  - On Linux, run the command `sudo apt install webots` in terminal to install the Webots app.
  - On Windows, install the official executable file from the [Webots website](https://cyberbotics.com/) and run it.

  ## 2. Extracting the .zip file
  Extract the .zip file. It contains two folders:
  - `worlds` folder containing the world files
  - `controllers` folder with the actual source code for the controller of the e-puck
    
  ## 3. Opening the world file
  To open the world file of this particular simulation you have to first 
  1. open Webots,
  then 
  2. go to `File` and
  3. click the `Open World` button.
  4. navigate then in the location where you extracted the .zip file
  5. go to `Worlds` and
  6. select one of the two simulation.

     
  ## 4. Before running the simulation
  In some cases it may be neccesary to give running permission to the executable of the code manually.
  
  If you run the simulation and the Webots console prompts you to do this:
  - open up a console
  - type `$cd /location_of_the_extracted_folder/controllers/Comenzi`
  - then to give executing permission type `chmod u+x Comenzi`

  ## 5. Running the simulation
  To run the simulation simply click the play button from the above or press _Ctrl+2_
  
  To increase the speed of the simulation press the button next to the play button or _Ctrl+3_

  A console should pop-up in the bottom of the screen, if not, it can be activated using _Ctrl+N_

  **Running the simulation**![simulation](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/74df26d9-dfe5-4424-a9a6-a5de3da5f5f5)
  
  ## 6. How it works

-The robot **must always** begin from the left side (the left wall).

-The start line and the finish line are physically denoted by two small black tapes on the floor.

-It then goes along that left wall until the finish line, and then it comes back following the same left wall from the  beggining that is actually the right hand side wall taken from the start line.

-When it arrives at the start line it know the distance if you take the left or the right wall, so for one final run towards the finish line it takes the shortest way found.

-It then stops on the finish line showing on the console the length of the shortest path.
  
  ## 6. Editing the source code

  If you want to change the source code, select _edit_ from the controller menu 
  
  ![Screenshot from 2024-01-01 17-59-08](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/f09964f0-7f17-4ec0-9f16-5c34423ce7d2)

- Select the file you wish to edit then press _open_
- Edit the code then build the code by pressing the ![Screenshot from 2024-01-01 18-03-24](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/fa7bdd2b-cd40-4297-bbd9-d2ff47bf10c8) button ( don't forget to save it before)
- Press `Reset` the start the simulation

  ## 7. Structure of the code

  The code is modularized in 4 different modules that are connected through an header file with the main source as shown below
  
  ![Screenshot from 2024-01-03 18-58-52](https://github.com/Gandalf789/pathfinder-robot/assets/109030213/17d790d0-54d1-4590-9de5-4cdac9422dcb)


