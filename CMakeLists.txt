# cmake_minimum_required(VERSION 3.11.3)

# project(traffic_system_sim)

# set(CXX_STANDARD 20)

include_directories(include)

file(GLOB SRC_FILES src/*.cpp)

add_executable(main ${SRC_FILES})