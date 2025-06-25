#!/bin/bash
 
set -e

# Ros build
source "/opt/ros/noetic/setup.bash"

echo "==============Super Odometry ROS1 Docker Env Ready================"

cd /root/ros1_ws

exec "$@"
