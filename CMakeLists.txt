# cmake_minimum_required(VERSION 3.11.3)

# project(traffic_system_sim)

# set(CMAKE_CXX_STANDARD 17)
# set(CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

include_directories(include)
file(GLOB SRC_FILES src/*.cpp)

add_executable(main ${SRC_FILES})
target_link_libraries(main ${OpenCV_LIBRARIES})