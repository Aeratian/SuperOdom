//
// Created by shibo zhao on 2020-09-27.
//
#include "ros/ros.h"
#include "super_odometry/ImuPreintegration/imuPreintegration.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "imu_preintegration_node");

    ros::NodeHandle nh;   
    
    super_odometry::imuPreintegration imuPreintegration(nh);
    
    imuPreintegration.imuBuf.allocate(1000);
    imuPreintegration.lidarOdomBuf.allocate(100);
    imuPreintegration.initInterface();

    ros::spin();
    
    return 0;
}
