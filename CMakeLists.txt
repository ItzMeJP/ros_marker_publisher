cmake_minimum_required(VERSION 3.0.2)
project(ros_marker_publisher)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
             roscpp
             rospy
             visualization_msgs
             tf2
             tf2_ros
             #xacro
)
#External packages
find_package(Eigen3 REQUIRED) # To matrix operations
#Headers
file(GLOB PROGRAM_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/${PROJECT_NAME}/*.h")

catkin_package(
        INCLUDE_DIRS
        include
        LIBRARIES
        ${PROJECT_NAME}
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${Eigen3_INCLUDE_DIRS}

)

## Declare a C++ library
add_library(common
            src/common/verbosity_levels.cpp
            src/common/std_vector_operations.cpp
            )

add_library(${PROJECT_NAME}
            src/marker_publisher_server.cpp
            src/marker_base.cpp
            #and all child classes.cpp
              src/arrow_marker.cpp
              src/arrow_pp_marker.cpp
              src/cube_marker.cpp
              src/sphere_marker.cpp
              src/cylinder_marker.cpp
              src/text_marker.cpp
              src/mesh_marker.cpp
            )

## Set dependencies of the library
target_link_libraries(common
                      ${catkin_LIBRARIES}
                      )

target_link_libraries(${PROJECT_NAME}
                      ${catkin_LIBRARIES}
                      common
                      )

## Define a executable
add_executable(${PROJECT_NAME}_node
               src/marker_publisher_node.cpp)

## Define the executable dependencies
target_link_libraries(${PROJECT_NAME}_node
                      common
                      ${catkin_LIBRARIES}
                      ${PROJECT_NAME})

#add_executable(${PROJECT_NAME} src/grasp_estimation_skill_server.cpp src/grasp_estimation_skill_server_node.cpp ${PROGRAM_HEADERS})
#target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
#add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
