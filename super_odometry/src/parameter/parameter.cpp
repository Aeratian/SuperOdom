//
// Created by shibo zhao on 2020-09-27.
//
#include "super_odometry/config/parameter.h"
#include <tf/transform_datatypes.h>
#include <tf/LinearMath/Quaternion.h>
#include <tf/LinearMath/Matrix3x3.h>

// Define color escape codes for ~beautification~
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define ITALIC "\033[3m"

std::string IMU_TOPIC;
std::string LASER_TOPIC;
std::string ODOM_TOPIC;
std::string DepthUP_TOPIC;
std::string DepthDown_TOPIC;
std::string ProjectName;

std::string WORLD_FRAME;
std::string WORLD_FRAME_ROT;
std::string SENSOR_FRAME;
std::string SENSOR_FRAME_ROT;
SensorType sensor;

int PROVIDE_IMU_LASER_EXTRINSIC;

Eigen::Matrix3d imu_laser_R;
Eigen::Vector3d imu_laser_T;
Eigen::Vector3d imu_laser_offset;
Eigen::Matrix3d cam_laser_R;
Eigen::Vector3d cam_laser_T;
Eigen::Matrix3d imu_camera_R;
Eigen::Vector3d imu_camera_T;

Transformd Tcam_lidar;
Transformd T_i_c;
Transformd T_i_l;
Transformd T_l_i;
Transformd T_ouster_sensor;

Eigen::Matrix3d ouster_sensor_R;
Eigen::Vector3d ouster_sensor_T;

float lidar_imu_offset_roll;
float up_realsense_roll;
float up_realsense_pitch;
float up_realsense_yaw;
float up_realsense_x;
float up_realsense_y;
float up_realsense_z;
float down_realsense_roll;
float down_realsense_pitch;
float down_realsense_yaw;
float down_realsense_x;
float down_realsense_y;
float down_realsense_z;
float yaw_ratio;
float IMU_ACC_X_LIMIT;
float IMU_ACC_Y_LIMIT;
float IMU_ACC_Z_LIMIT;
bool USE_IMU_ROLL_PITCH;
std::string SENSOR;

template <typename T>
T readParam(ros::NodeHandle& nh, std::string name)
{
    T ans;
    if (nh.getParam(name, ans)) {
        ROS_INFO("Loaded %s: ", name.c_str());
    }
    else {
        ROS_ERROR("Failed to load %s", name.c_str());
        ros::shutdown();
    }
    return ans;
}

bool readCalibration(ros::NodeHandle& nh)
{
    ROS_INFO("[super_odometry] read parameter");
    std::string calib_file;
    nh.param<std::string>("calibration_file", calib_file, "");
    ROS_INFO("[super_odometry] calib_file: %s", calib_file.c_str());
    
    cv::FileStorage fsSettings(calib_file, cv::FileStorage::READ);
    if (!fsSettings.isOpened()) {
        std::cerr << "ERROR: Wrong path to settings" << std::endl;
        return false;
    }
    
    nh.param("provide_imu_laser_extrinsic", PROVIDE_IMU_LASER_EXTRINSIC, 1);
    ROS_INFO("PROVIDE_IMU_LASER_EXTRINSIC: %d", PROVIDE_IMU_LASER_EXTRINSIC);

    // Defaults to 0 if no entry
    up_realsense_roll = fsSettings["up_realsense_roll"];
    up_realsense_pitch = fsSettings["up_realsense_pitch"];
    up_realsense_yaw = fsSettings["up_realsense_yaw"];
    up_realsense_x = fsSettings["up_realsense_x"];
    up_realsense_y = fsSettings["up_realsense_y"];
    up_realsense_z = fsSettings["up_realsense_z"];

    down_realsense_roll = fsSettings["down_realsense_roll"];
    down_realsense_pitch = fsSettings["down_realsense_pitch"];
    down_realsense_yaw = fsSettings["down_realsense_yaw"];
    down_realsense_x = fsSettings["down_realsense_x"];
    down_realsense_y = fsSettings["down_realsense_y"];
    down_realsense_z = fsSettings["down_realsense_z"];
    
    yaw_ratio = fsSettings["yaw_ratio"];

    ROS_INFO("up realsense extrinsic to velodyne (RPYXYZ): %f, %f, %f, %f, %f, %f",
                up_realsense_roll,
                up_realsense_pitch,
                up_realsense_yaw,
                up_realsense_x,
                up_realsense_y,
                up_realsense_z);

    ROS_INFO("down realsense extrinsic to velodyne (RPYXYZ): %f, %f, %f, %f, %f, %f",
                down_realsense_roll,
                down_realsense_pitch,
                down_realsense_yaw,
                down_realsense_x,
                down_realsense_y,
                down_realsense_z);

    ROS_INFO("yaw ratio: %f", yaw_ratio);
    
    if (PROVIDE_IMU_LASER_EXTRINSIC)
    {
        cv::Mat cv_R, cv_T;

        cv::Mat imu_laser_rotation_offset;
        fsSettings["imu_laser_rotation_offset"] >> imu_laser_rotation_offset;
        fsSettings["extrinsicRotation_imu_laser"] >> cv_R;
        fsSettings["extrinsicTranslation_imu_laser"] >> cv_T;
        cv::cv2eigen(cv_R, imu_laser_R);
        cv::cv2eigen(cv_T, imu_laser_T);
        cv::cv2eigen(imu_laser_rotation_offset, imu_laser_offset);

        //previous rotation matrix
        T_i_l = Transformd(imu_laser_R, imu_laser_T);
        T_l_i = T_i_l.inverse();   
        
        //previous roll, pitch, yaw
        double roll, pitch, yaw;
        tf::Quaternion orientation_pre(T_i_l.rot.x(), T_i_l.rot.y(), T_i_l.rot.z(), T_i_l.rot.w());
        tf::Matrix3x3(orientation_pre).getRPY(roll, pitch, yaw);
        ROS_INFO(BLUE"\n previous roll: %f previous pitch: %f previous yaw: %f" RESET, roll *180/M_PI, pitch *180/M_PI, yaw *180/M_PI); 

        //add offset rotation matrix
        tf::Quaternion IMU_LASER_R_offset;
        IMU_LASER_R_offset.setRPY(imu_laser_offset[0]* M_PI / 180, imu_laser_offset[1] * M_PI / 180, 
                            imu_laser_offset[2]* M_PI / 180);

        tf::Quaternion IMU_LASER_R(T_i_l.rot.x(), T_i_l.rot.y(), T_i_l.rot.z(),
                                                        T_i_l.rot.w());
        tf::Quaternion IMU_LASER = IMU_LASER_R_offset * IMU_LASER_R;
        Eigen::Quaterniond imu_laser_rot;             
        imu_laser_rot = Eigen::Quaterniond(IMU_LASER.w(), IMU_LASER.x(), IMU_LASER.y(),
                                                      IMU_LASER.z());
         
        T_i_l.rot = imu_laser_rot;
        T_l_i = T_i_l.inverse(); 
        imu_laser_R = T_i_l.rot.toRotationMatrix();
        
        ROS_INFO_STREAM(GREEN BOLD "T_i_l Extrinsic : \n" << T_i_l.matrix());
        ROS_INFO_STREAM(GREEN BOLD "T_l_i Extrinsic : \n" << T_l_i.matrix()); 

        //lasted roll pitch yaw
        double updated_roll, updated_pitch, updated_yaw;
        tf::Quaternion orientation_curr(IMU_LASER.x(), IMU_LASER.y(), IMU_LASER.z(), IMU_LASER.w());
        tf::Matrix3x3(orientation_curr).getRPY(updated_roll, updated_pitch, updated_yaw);
        
        ROS_INFO(GREEN BOLD"\n updated roll: %f updated pitch: %f updated yaw: %f" RESET, updated_roll*180/M_PI, updated_pitch *180/M_PI, updated_yaw*180/M_PI); 
    }
    else
    {
        cv::Mat cv_R, cv_T;
        fsSettings["extrinsicRotation_camera_laser"] >> cv_R;
        fsSettings["extrinsicTranslation_camera_laser"] >> cv_T;
        cv::cv2eigen(cv_R, cam_laser_R);
        cv::cv2eigen(cv_T, cam_laser_T);

        Tcam_lidar = Transformd(cam_laser_R, cam_laser_T);

        fsSettings["extrinsicRotation_imu_camera"] >> cv_R;
        fsSettings["extrinsicTranslation_imu_camera"] >> cv_T;

        cv::cv2eigen(cv_R, imu_camera_R);
        cv::cv2eigen(cv_T, imu_camera_T);
        Eigen::Quaterniond Q(imu_camera_R);
        imu_camera_R = Q.normalized();

        T_i_c = Transformd(imu_camera_R, imu_camera_T);

        T_i_l = T_i_c * Tcam_lidar;
        T_l_i = T_i_l.inverse();

        ROS_INFO_STREAM(GREEN BOLD "T_i_l Extrinsic : \n" << T_i_l.matrix());
        ROS_INFO_STREAM(GREEN BOLD "T_l_i Extrinsic : \n" << T_l_i.matrix());
    }

    ouster_sensor_R << -1, 0,  0,
                    0, -1, 0,
                    0,  0,  1;

    ouster_sensor_T << 0, 0, 0.036180;

    T_ouster_sensor = Transformd(ouster_sensor_R, ouster_sensor_T);

    return true;
}

bool readGlobalparam(ros::NodeHandle& nh)
{
    nh.param<std::string>("imu_topic", IMU_TOPIC, "imu/data");
    nh.param<std::string>("laser_topic", LASER_TOPIC, "velodyne_points");
    nh.param<std::string>("odom_topic", ODOM_TOPIC, "integrated_to_init");
    nh.param<std::string>("depthup_topic", DepthUP_TOPIC, "/rs_up/depth/cloud_filtered");
    nh.param<std::string>("depthdown_topic", DepthDown_TOPIC, "/rs_down/depth/cloud_filtered");
    nh.param<std::string>("world_frame", WORLD_FRAME, "sensor_init");
    nh.param<std::string>("world_frame_rot", WORLD_FRAME_ROT, "sensor_init_rot");
    nh.param<std::string>("sensor_frame", SENSOR_FRAME, "sensor");
    nh.param<std::string>("sensor_frame_rot", SENSOR_FRAME_ROT, "sensor_rot");
    nh.param<std::string>("PROJECT_NAME", ProjectName, "");
    nh.param<std::string>("sensor", SENSOR, "livox");
    
    // IMU acceleration limits
    if (!nh.param("imu_acc_x_limit", IMU_ACC_X_LIMIT, 0.5f)) {
        ROS_WARN("Parameter imu_acc_x_limit not found, using default value: 0.5");
    }
    if (!nh.param("imu_acc_y_limit", IMU_ACC_Y_LIMIT, 0.2f)) {
        ROS_WARN("Parameter imu_acc_y_limit not found, using default value: 0.2");
    }
    if (!nh.param("imu_acc_z_limit", IMU_ACC_Z_LIMIT, 0.4f)) {
        ROS_WARN("Parameter imu_acc_z_limit not found, using default value: 0.4");
    }
    
    //check whether sensor is support 
    const std::unordered_map<std::string, SensorType> sensorTypeMap = {
        {"velodyne", SensorType::VELODYNE},
        {"ouster", SensorType::OUSTER},
        {"livox", SensorType::LIVOX}
    };

    if (sensorTypeMap.find(SENSOR) == sensorTypeMap.end()) {
        ROS_ERROR("Unsupported sensor type: %s", SENSOR.c_str());
        return false;
    }
    
    ROS_INFO("LASER_TOPIC %s", LASER_TOPIC.c_str());
    ROS_INFO("IMU_TOPIC %s", IMU_TOPIC.c_str());
    ROS_INFO("ODOM_TOPIC %s", ODOM_TOPIC.c_str());
    ROS_INFO("DepthUP_TOPIC %s", DepthUP_TOPIC.c_str());
    ROS_INFO("DepthDown_TOPIC %s", DepthDown_TOPIC.c_str());
    ROS_INFO("WORLD_FRAME %s", WORLD_FRAME.c_str());
    ROS_INFO("WORLD_FRAME_ROT %s", WORLD_FRAME_ROT.c_str());
    ROS_INFO("SENSOR_FRAME %s", SENSOR_FRAME.c_str());
    ROS_INFO("SENSOR_FRAME_ROT %s", SENSOR_FRAME_ROT.c_str());
    ROS_INFO("ProjectName %s", ProjectName.c_str());
    ROS_INFO("SENSOR %s", SENSOR.c_str());
    ROS_INFO("IMU_ACC_X_LIMIT: %f", IMU_ACC_X_LIMIT);
    ROS_INFO("IMU_ACC_Y_LIMIT: %f", IMU_ACC_Y_LIMIT);
    ROS_INFO("IMU_ACC_Z_LIMIT: %f", IMU_ACC_Z_LIMIT);

    return true;
}