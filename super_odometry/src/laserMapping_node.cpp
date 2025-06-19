//
// Created by shibo zhao on 2020-09-27.
//
#include "ros/ros.h"
#include "super_odometry/LaserMapping/laserMapping.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "laser_mapping_node");
    
    ros::NodeHandle nh;
    super_odometry::laserMapping laserMapping(nh);

    laserMapping.initInterface();
    
    ros::spin();

    return 0;
}

