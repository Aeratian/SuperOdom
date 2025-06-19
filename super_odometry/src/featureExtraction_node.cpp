//
// Created by shibo zhao on 2020-09-27.
//
#include "ros/ros.h"
#include "super_odometry/FeatureExtraction/featureExtraction.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "feature_extraction_node");
    
    ros::NodeHandle nh;
    super_odometry::featureExtraction featureExtraction(nh);

    featureExtraction.imuBuf.allocate(2000);
    featureExtraction.visualOdomBuf.allocate(2000);
    featureExtraction.lidarBuf.allocate(50);
    featureExtraction.initInterface();

    ros::spin();

    return 0;
}
