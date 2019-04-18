cmake_minimum_required(VERSION 2.8.3)
project(delta_2b_lidar)

set(DELTA_2B_LIDAR_SDK_PATH "./sdk/")

FILE(GLOB DELTA_2B_LIDAR_SDK_SRC 
  "${DELTA_2B_LIDAR_SDK_PATH}/src/*.cpp"
)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
  sensor_msgs
)

include_directories(
  ${DELTA_2B_LIDAR_SDK_PATH}/include
  ${DELTA_2B_LIDAR_SDK_PATH}/src
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(delta_2b_lidar_node src/node.cpp ${DELTA_2B_LIDAR_SDK_SRC})
target_link_libraries(delta_2b_lidar_node ${catkin_LIBRARIES} -lrt)

add_executable(delta_2b_lidar_node_client src/client.cpp)
target_link_libraries(delta_2b_lidar_node_client ${catkin_LIBRARIES})

install(TARGETS delta_2b_lidar_node delta_2b_lidar_node_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch rviz sdk
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  USE_SOURCE_PERMISSIONS
)
