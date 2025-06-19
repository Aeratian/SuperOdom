cmake_minimum_required(VERSION 3.0.2)
project(super_odometry_msgs)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
)

# Generate messages in the 'msg' folder
add_message_files(
  FILES
  IterationStats.msg
  OptimizationStats.msg
  LaserFeature.msg
)

# Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime std_msgs geometry_msgs nav_msgs sensor_msgs
)
