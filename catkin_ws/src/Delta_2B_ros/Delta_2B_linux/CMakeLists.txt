cmake_minimum_required(VERSION 2.8.3)
project(iiiroboticslidar2)

set(iiiroboticslidar2_SDK_PATH "./src/")

FILE(GLOB iiiroboticslidar2_SDK_SRC 
  "${iiiroboticslidar2_SDK_PATH}/src/*.cpp"
)

include_directories(
  ${iiiroboticslidar2_SDK_PATH}/include
  ${iiiroboticslidar2_SDK_PATH}/src
)

add_executable(iiirobotics_lidar2_node app/node.cpp ${iiiroboticslidar2_SDK_SRC})
target_link_libraries(iiirobotics_lidar2_node -lrt -lpthread)


