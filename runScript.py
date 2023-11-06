#!/usr/bin/env python3
import math
import numpy as np
import os
import rospy
import tf
import time
import cv2
import serial
import subprocess
import sys

#os.system("gnome-terminal -e 'bash -c \" roslaunch robot_navigation simulation_robot.launch 2> >(grep -v TF_REPEATED_DATA buffer_core) ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" roslaunch robot_navigation simulation_robot.launch ;bash\"'")
time.sleep(8)

os.system("gnome-terminal -e 'bash -c \" cd catkin_ws/movel_ai/ && docker-compose up -d ;bash\"'")
time.sleep(3)

os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv1.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv2.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv3.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv4.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv5.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv6.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv7.py ;bash\"'")
os.system("gnome-terminal -e 'bash -c \" python3 $HOME/catkin_ws/pySeirios/pythoncode/customTaskConv8.py ;bash\"'")

time.sleep(30)
os.system("gnome-terminal -e 'bash -c \" rostopic pub /battery_percentage std_msgs/Float64 \"99\" ;bash\"'")
time.sleep(1)
