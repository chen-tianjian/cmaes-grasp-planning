# cmaes-grasp-planning
A GraspIt plugin to search for good grasp(s) with an arbitrary hand, object, obstacle(s) and quality metric, using CMA-ES.

## To install

First install *GraspIt*: <http://graspit-simulator.github.io/build/html/installation_linux.html>

Then install this package:
```
git clone --recursive git@github.com:chen-tianjian/cmaes-grasp-planning.git
cd cmaes-grasp-planning
mkdir build
cd build
export GRASPIT_PLUGIN_DIR=$PWD
cmake ..
make -j4
```

## To run
```
cd build
export GRASPIT_PLUGIN_DIR=$PWD
$GRASPIT/build/graspit_simulator -p libcmaesgraspplanning
```
Example: 
* In the GraspIt GUI, load the "plannerMug.xml" world file (by "File-Open"), add the Epsilon quality metric (by "Grasp-Quality Measures").
* In the plugin GUI, load the "barret_hand_mug.xml" optimization config file (by "Load Config").
* Then click "Plan grasp".

Note:
You can create other config files by following the "barret_hand_mug.xml", keep in mind that the dimension of the bounds and x0 need to match the robot hand (format: palm X, Y, Z, R, P, Y, and finger joint angles).
