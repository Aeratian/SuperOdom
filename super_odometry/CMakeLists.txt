cmake_minimum_required(VERSION 3.5)
project(super_odometry)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -Wall -g")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(TBB_INCLUDE_DIR "/usr/include/tbb")
add_compile_options(-Wall -Wextra -Wpedantic -Wunused-parameter)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra )
endif()

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
  super_odometry_msgs
  image_transport
  cv_bridge
  tf
  tf2
  tf2_ros
  tf2_geometry_msgs
  visualization_msgs
  pcl_ros
  pcl_conversions
  #livox_ros_driver
)

find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)
find_package(PCL REQUIRED)
find_package(Ceres REQUIRED)
find_package(GTSAM REQUIRED QUIET)
find_package(TBB REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES SuperOdomLib
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs nav_msgs sensor_msgs super_odometry_msgs tf tf2_ros
)

# Include directories
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${CERES_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${GTSAM_INCLUDE_DIR}
  ${TBB_INCLUDE_DIR}
  ${Sophus_INCLUDE_DIRS}
  ${pcl_conversions_INCLUDE_DIRS}
  ${livox_ros_driver2_INCLUDE_DIRS}
)

# Link directories
link_directories(
  include
  ${PCL_LIBRARY_DIRS}
  ${OpenCV_LIBRARY_DIRS}
  ${GTSAM_LIBRARY_DIRS}
)

set(GTSAM_LIBRARIES gtsam)

# SuperOdom Library
add_library(SuperOdomLib SHARED
  src/FeatureExtraction/featureExtraction.cpp
  src/ImuPreintegration/imuPreintegration.cpp
  src/LaserMapping/laserMapping.cpp
  src/LaserMapping/lidarOptimization.cpp
  src/LaserMapping/LocalMap.cpp
  src/LidarProcess/LidarSlam.cpp
  src/LidarProcess/pose_local_parameterization.cpp
  src/LidarProcess/SE3AbsolutatePoseFactor.cpp
  src/parameter/parameter.cpp
  src/utils/superodom_utils.cpp
)

add_dependencies(SuperOdomLib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(SuperOdomLib
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${OpenCV_LIBRARIES}
  gtsam
  ${CERES_LIBRARIES}
)

# IMU PreIntegration node
add_executable(imu_preintegration_node src/imuPreintegration_node.cpp)
target_link_libraries(imu_preintegration_node
    ${catkin_LIBRARIES}
    gtsam
    SuperOdomLib
)

# Feature Extraction node
add_executable(feature_extraction_node src/featureExtraction_node.cpp)
target_link_libraries(feature_extraction_node 
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${TBB_LIBRARIES}
  SuperOdomLib
)

# LiDAR Mapping node
add_executable(laser_mapping_node src/laserMapping_node.cpp)
target_link_libraries(laser_mapping_node
    ${catkin_LIBRARIES}
    ${PCL_LIBRARIES}
    ${CERES_LIBRARIES}
    SuperOdomLib
)

# Install targets
install(TARGETS SuperOdomLib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS
  imu_preintegration_node
  feature_extraction_node
  laser_mapping_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
