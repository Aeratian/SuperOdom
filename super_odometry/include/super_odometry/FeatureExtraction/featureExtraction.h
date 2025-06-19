//
// Created by shibo zhao on 2020-09-27.
//

#ifndef super_odometry_FEATUREEXTRACTION_H
#define super_odometry_FEATUREEXTRACTION_H

// #include "super_odometry/logging.h"


#include <cmath>
#include <string>
#include <vector>
#include <sophus/so3.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <super_odometry_msgs/LaserFeature.h>

#include "super_odometry/container/MapRingBuffer.h"
#include "super_odometry/sensor_data/imu/imu_data.h"
#include "super_odometry/sensor_data/pointcloud/point_os.h"
#include "super_odometry/tic_toc.h"
#include "super_odometry/utils/Twist.h"
#include "super_odometry/config/parameter.h"

#include <mutex>


// #include <livox_ros_driver/CustomMsg.h>
#include "super_odometry/utils/superodom_utils.h"


namespace super_odometry {


    using std::atan2;
    using std::cos;
    using std::sin;
    std::vector<std::queue<sensor_msgs::PointCloud2::Ptr>> all_cloud_buf(2);
     
    constexpr unsigned int BLOCK_TIME_NS = 55296;   // Time in ns for one block (measurement + recharge)
    constexpr std::size_t NUM_BLOCKS = 12;    // Number of blocks in a Velodyne packet
    constexpr double LIDAR_MESSAGE_TIME = (double)(NUM_BLOCKS * BLOCK_TIME_NS * 151) * 1e-9;
    constexpr double IMU_TIME_LENIENCY = 0.1;
   

    struct bounds_t
    {
        double blindFront;
        double blindBack;
        double blindRight;
        double blindLeft;
    };

    struct feature_extraction_config{
        bounds_t box_size;
        int skipFrame;
        int N_SCANS;
        int provide_point_time;
        bool use_dynamic_mask;
        bool use_imu_roll_pitch;
        bool debug_view_enabled;
        float min_range;
        float max_range;
        int filter_point_size;
        SensorType sensor;
        double imu_acc_x_limit;
        double imu_acc_y_limit;
        double imu_acc_z_limit;
    };

    struct ImuMeasurement {
        double timestamp;
        Eigen::Vector3d accel;
        Eigen::Vector3d gyr;
        Eigen::Quaterniond orientation;
    };

    typedef feature_extraction_config feature_extraction_config;

    class featureExtraction {
    public:

        /* TODO: return this as a parameter */

        static constexpr double scanPeriod = 0.100859904 - 20.736e-6;
        static constexpr double columnTime = 55.296e-6;
        static constexpr double laserTime = 2.304e-6;

        featureExtraction(ros::NodeHandle& nh);

        void initInterface();
  
        template <typename Meas>
        bool synchronize_measurements(MapRingBuffer<Meas> &measureBuf,
                                        MapRingBuffer<pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr> &lidarBuf);

        void imuRemovePointDistortion(double lidar_start_time, double lidar_end_time, MapRingBuffer<Imu::Ptr> &imuBuf,
                                    pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr &lidar_msg);

        void vioRemovePointDistortion(double lidar_start_time, double lidar_end_time, MapRingBuffer<nav_msgs::Odometry::Ptr>&vioBuf,
                                    pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr &lidar_msg);

        void undistortionAndFeatureExtraction();

        void extractFeatures(double lidar_start_time, const pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr& lidar_msg, const Eigen::Quaterniond& quaternion);

        void imu_Handler(const sensor_msgs::Imu::ConstPtr& msg_in);

        void visual_odom_Handler(const nav_msgs::Odometry::ConstPtr& visualOdometry);

        void laserCloudHandler(const sensor_msgs::PointCloud2::ConstPtr& laserCloudMsg);

        // void livoxHandler(const livox_ros_driver::CustomMsg::ConstPtr& msg);

        void uniformFeatureExtraction(const pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr &pc_in, 
            pcl::PointCloud<pcl::PointXYZI>::Ptr &pc_out_surf, int skip_num, float block_range);

        void assignTimeforPointCloud(pcl::PointCloud<PointType>::Ptr laserCloudIn_ptr_);
        
        template <typename Point>
        sensor_msgs::PointCloud2 publishCloud(ros::Publisher thisPub, typename pcl::PointCloud<Point>::Ptr thisCloud, ros::Time thisStamp, std::string thisFrame);

        bool readParameters();

        void publishTopic(double lidar_start_time, 
                                         pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr laser_no_distortion_points,
                                         pcl::PointCloud<PointType>::Ptr edgePoints,
                                         pcl::PointCloud<PointType>::Ptr plannerPoints, 
                                         pcl::PointCloud<PointType>::Ptr depthPoints,
                                         Eigen::Quaterniond q_w_original_l);

        void manageLidarBuffer(pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr pointCloud, double timestamp);

        ImuMeasurement parseImuMessage(const sensor_msgs::Imu::ConstPtr& msg);

        double calculateDeltaTime(double current_timestamp);

        Imu::Ptr createImuData(const ImuMeasurement& measurement);

        void updateImuOrientation(Imu::Ptr& imudata);

        void imuInitialization(double timestamp);

        template<typename BufferType>
        void removePointDistortion(
            double lidar_start_time, 
            double lidar_end_time,
            MapRingBuffer<BufferType> &buffer,
            pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr &lidar_msg);

       
        
        template<typename BufferType>
        Transformd getInterpolatedPose(double timestamp, MapRingBuffer<BufferType> &buffer,
                                const std::function<Transformd(const BufferType&)>& extractPose);

        Eigen::Vector3d transformPoint(const point_os::PointcloudXYZITR& point, const Transformd& T_w_original,
                                        const Transformd& point_pose, bool is_imu_data);
        
        void updatePointPosition(point_os::PointcloudXYZITR& point, const Eigen::Vector3d& new_pos);

        bool isPointValid(const point_os::PointcloudXYZITR& point);

        
        Imu::Ptr imu_Init = std::make_shared<Imu>();
        MapRingBuffer<Imu::Ptr> imuBuf;
        MapRingBuffer<pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr> lidarBuf;
        MapRingBuffer<nav_msgs::Odometry::ConstPtr> visualOdomBuf;


    private:
        ros::NodeHandle nh_;
        // Subscribers
        ros::Subscriber subLaserCloud;
        ros::Subscriber subImu;
        ros::Subscriber subOdom;
        ros::Subscriber subLivoxCloud;

        // Publishers
        ros::Publisher pubLaserCloud;
        ros::Publisher pubEdgePoints;
        ros::Publisher pubPlannerPoints;
        ros::Publisher pubBobPoints;
        ros::Publisher pubLaserFeatureInfo;
        std::vector<ros::Publisher> pubEachScan;

        int delay_count_;
        std::mutex m_buf;
        int frameCount = 0;

        bool PUB_EACH_LINE = false;
        bool LASER_IMU_SYNC_SCCUESS = false;
        bool LASER_CAMERA_SYNC_SUCCESS = false;
        bool IMU_INIT=false;
        double m_imuPeriod;

        super_odometry_msgs::LaserFeature laserFeature;
        std_msgs::Header FeatureHeader;
        Eigen::Quaterniond q_w_original_l;
        Eigen::Vector3d t_w_original_l;
        pcl::PointCloud<point_os::PointcloudXYZITR>::Ptr pointCloudwithTime=nullptr;
        pcl::PointCloud<point_os::OusterPointXYZIRT>::Ptr tmpOusterCloudIn=nullptr;
        feature_extraction_config config_;
    };

} // namespace super_odometry

#endif //super_odometry_FEATUREEXTRACTION_H
