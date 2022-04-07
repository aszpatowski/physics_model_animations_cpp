# Physics model animations C++
3 projects prepared for "physical modeling in computer animation" classes using C++ openFrameworks toolkit (https://openframeworks.cc/). 
(5 semester of Applied Computer Science and Measurment Systems)
## Particle System
Fully object oriented engine for creating complex scenes using particles and forces between them.<br> Below two scenes created using it:<br>
<img src='https://raw.githubusercontent.com/aszpatowski/physics_model_animations_cpp/master/gifs/4_1.gif'>
<img src='https://raw.githubusercontent.com/aszpatowski/physics_model_animations_cpp/master/gifs/4_2.gif'><br>
## Spring Mass System
Simple game using spring mass system mechanic.<br>
<img src='https://raw.githubusercontent.com/aszpatowski/physics_model_animations_cpp/master/gifs/5_1.gif'>
<img src='https://raw.githubusercontent.com/aszpatowski/physics_model_animations_cpp/master/gifs/5_2.gif'><br>
## Disks
Simple simulation of 2d disks in attraction forces, self-collisions and moving in liquids (with pre-set viscosity)<br>
<img src='https://raw.githubusercontent.com/aszpatowski/physics_model_animations_cpp/master/gifs/3.gif'>
## How to run
To run projects first of all must be downloaded openframeworks. 
After that put projects in of_v0.11.2_linux64gcc6_release/apps/myApps (version of openframeworks may be different, but 0.11.2+). 
Last things are change path to your own location of 'of' in 'config.make' of each project, 
run 'make' in projects directory and finally run 'make RunRelease'.
