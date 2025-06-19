//
// Created by shibo zhao on 2020-09-27.
//
#pragma once
#ifndef IMUPREINTEGRATION_H
#define IMUPREINTEGRATION_H

#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>
#include <tf/LinearMath/Quaternion.h>
#include <tf/transform_broadcaster.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Rot3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/CombinedImuFactor.h>
#include <gtsam/navigation/GPSFactor.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/linear/linearExceptions.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>
#include "super_odometry/utils/Twist.h"
#include "super_odometry/container/MapRingBuffer.h"
#include "super_odometry/config/parameter.h"
#include "super_odometry/tic_toc.h"
#include <glog/logging.h>
#include "super_odometry/sensor_data/imu/imu_data.h"

namespace super_odometry {

    using gtsam::symbol_shorthand::B; // Bias  (ax,ay,az,gx,gy,gz)
    using gtsam::symbol_shorthand::V; // Vel   (xdot,ydot,zdot)
    using gtsam::symbol_shorthand::X; // Pose3 (x,y,z,r,p,y)
    using FrameId = std::uint64_t;

    struct imuPreintegration_config{
        float imuAccNoise;
        float imuAccBiasN;
        float imuGyrNoise;
        float imuGyrBiasN;
        float imuGravity;
        float lidar_correction_noise;
        float smooth_factor;
        bool  use_imu_roll_pitch;
        SensorType sensor;

        double imu_acc_x_limit;
        double imu_acc_y_limit;
        double imu_acc_z_limit;
    };

    class imuPreintegration {
    public:
        imuPreintegration(ros::NodeHandle& nh);

        static constexpr double delta_t = 0;
        static constexpr double imu_laser_timedelay= 0.8;

    public:
        void initInterface();

        bool readParameters();

        void laserodometryHandler(const nav_msgs::Odometry::ConstPtr& odomMsg);

        void imuHandler(const sensor_msgs::Imu::ConstPtr& imu_raw);

        void initial_system(double currentCorrectionTime, gtsam::Pose3 lidarPose);

        void process_imu_odometry(double currentCorrectionTime, gtsam::Pose3 relativePose);

        bool build_graph(gtsam::Pose3 lidarPose, double curLaserodomtimestamp);

        void repropagate_imuodometry(double currentCorrectionTime);

        bool failureDetection(const gtsam::Vector3 &velCur,
                         const gtsam::imuBias::ConstantBias &biasCur);

        void obtainCurrodometry(nav_msgs::Odometry::Ptr &odomMsg, double &currentCorrectionTime,
                           gtsam::Pose3 &lidarPose,
                           int &currentResetId);

        void integrate_imumeasurement(double currentCorrectionTime);

        void reset_graph();

        void resetOptimization();

        void resetParams();

        bool handleIMUInitialization(const sensor_msgs::Imu::ConstPtr& imu_raw, 
        sensor_msgs::Imu& thisImu);

        void updateAndPublishPath(nav_msgs::Odometry &odometry, const sensor_msgs::Imu& thisImu);

        void publishTransform(nav_msgs::Odometry &odometry, const sensor_msgs::Imu& thisImu);

        void prepareOdometryMessage(nav_msgs::Odometry &odometry, const sensor_msgs::Imu& thisImu, const gtsam::NavState &currentState);

        void publishOdometry(const sensor_msgs::Imu& thisImu, const gtsam::NavState& currentState, nav_msgs::Odometry &odometry);

        void publishTransformsAndPath(nav_msgs::Odometry &odometry, const sensor_msgs::Imu& thisImu);

        void processTiming(const sensor_msgs::Imu& thisImu);

        void initializeImu(const sensor_msgs::Imu::ConstPtr& imu_raw);

        void correctLivoxGravity(sensor_msgs::Imu& thisImu);

        sensor_msgs::Imu imuConverter(const sensor_msgs::Imu &imu_in);

        template<typename T>
        double secs(T msg) {
            return msg->header.stamp.toSec();
        }

    private:
        ros::NodeHandle nh_;
        ros::Subscriber subImu;
        ros::Subscriber subLaserOdometry;
        
        ros::Publisher pubImuOdometry;
        ros::Publisher pubHealthStatus;
        ros::Publisher pubImuPath;

        tf::TransformBroadcaster tfBroadcaster;

    public:
        gtsam::noiseModel::Diagonal::shared_ptr priorPoseNoise;
        gtsam::noiseModel::Diagonal::shared_ptr priorVelNoise;
        gtsam::noiseModel::Diagonal::shared_ptr priorBiasNoise;
        gtsam::noiseModel::Diagonal::shared_ptr correctionNoise;
        gtsam::Vector noiseModelBetweenBias;
        std::shared_ptr<gtsam::PreintegratedImuMeasurements> imuIntegratorOpt_;
        std::shared_ptr<gtsam::PreintegratedImuMeasurements> imuIntegratorImu_;
        gtsam::Pose3 prevPose_;
        gtsam::Vector3 prevVel_;
        gtsam::NavState prevState_;
        gtsam::imuBias::ConstantBias prevBias_;
        gtsam::NavState prevStateOdom;
        gtsam::imuBias::ConstantBias prevBiasOdom;
        gtsam::ISAM2 optimizer;
        gtsam::NonlinearFactorGraph graphFactors;
        gtsam::Values graphValues;
        gtsam::Pose3 lidarodom_w_pre;
        gtsam::Pose3 lidarodom_w_cur;

    public:
        //Modify the extrinsic matrxi between laser and imu, laser and camera
        gtsam::Pose3 imu2cam;
        gtsam::Pose3 cam2Lidar;
        gtsam::Pose3 imu2Lidar;
        gtsam::Pose3 lidar2Imu;

    public:
        MapRingBuffer<Imu::Ptr> imuBuf;
        std::deque<sensor_msgs::Imu> imuQueOpt;
        std::deque<sensor_msgs::Imu> imuQueImu;
        MapRingBuffer<nav_msgs::Odometry::Ptr> lidarOdomBuf;
        std::mutex mBuf;
        Imu::Ptr imu_Init = std::make_shared<Imu>();

    public:
        bool systemInitialized = false;
        bool doneFirstOpt = false;
        bool health_status = true;
        bool imu_init_success = false;

        Eigen::Quaterniond firstImu;
        Eigen::Vector3d gyr_pre;

        double first_imu_time_stamp;
        double last_processed_lidar_time = -1;
        double lastImuT_imu = -1;
        double lastImuT_opt = -1;
        int key = 1;
        int imuPreintegrationResetId = 0;
        int frame_count = 0;

        enum IMU_STATE : uint8_t {
            FAIL=0,    //lose imu information 
            SUCCESS=1, //Obtain the good imu data 
            UNKNOW=2
        };  

        IMU_STATE RESULT;
        nav_msgs::Odometry::Ptr cur_frame = nullptr;
        nav_msgs::Odometry::Ptr last_frame = nullptr;
        imuPreintegration_config config_;
    };

}

#endif // IMUPREINTEGRATION_H
