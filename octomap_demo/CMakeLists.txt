cmake_minimum_required(VERSION 3.10)
project(octomap_demo)

set(CMAKE_CXX_STANDARD 11)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

find_package(octomap REQUIRED)
include_directories(${OCTOMAP_INCLUDE_DIRS})

add_executable(octomap_demo src/simple_example.cpp)
target_link_libraries(octomap_demo ${OCTOMAP_LIBRARIES})

add_executable(octomap_creation src/creating_octomap.cpp)
target_link_libraries(octomap_creation ${OCTOMAP_LIBRARIES})

add_executable(octree_pruning src/pruning.cpp)
target_link_libraries(octree_pruning ${OCTOMAP_LIBRARIES})

add_executable(3d_raycasting src/3d_raycasting.cpp)
target_link_libraries(3d_raycasting ${OCTOMAP_LIBRARIES})