cmake_minimum_required(VERSION 2.8.3)
project(arduino_pc)

find_package(catkin REQUIRED COMPONENTS
  navigation
  planning
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  PC.msg
  Arduino.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
   CATKIN_DEPENDS 
)

include_directories(include/arduino_pc)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(arduino_pc src/pc.cpp)
add_dependencies(arduino_pc ${catkin_EXPORTED_TARGETS})
add_dependencies(arduino_pc navigation_generate_messages_cpp)
target_link_libraries(arduino_pc ${catkin_LIBRARIES} )
