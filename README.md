# RSE-5_HomeServiceRobot
Final Project of the Robotic Software Engineering Nanodegree

**Installation**



git clone https://github.com/markaajan/RSE5_HSR.git

cd RSE-5_HomeServiceRobot/

cd RSE-5_HomeServiceRobot/catkin_ws

catkin_make

echo "source /path/to/RSE-5_HomeServiceRobot/catkin_ws/devel/setup.bash" >> ~/.bashrc

bash

./path/to/RSE-5_HomeServiceRobot/catkin_ws/src/scripts/home_service.sh

**Packages Used**


Localization

The map of the area is previously known. AMCL is used for localization. In this method particles are randomly spread through the map. For each point the position and orientation (from sensor readings) is calculated and compared to that of the sensor readings of the rebot. This is then used to assign weights during the resampling step where particles with higher weights are more likely to survive.
Repeated iterations of this method gives us the pose.

Mapping

Since this is a known map problem, the pgm_map creator tool is used to generate a 2D Map from the 3D World in Gazebo.

Navigation

Navigation is done using the ROS Navigation Stack and move_base package. This used Dijkstra algorithm.
