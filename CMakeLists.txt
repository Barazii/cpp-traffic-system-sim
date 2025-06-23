cmake_minimum_required(VERSION 3.11.3)

project(traffic_system_sim)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

include_directories(include)
add_compile_definitions(TESTING)

file(GLOB SRC_FILES src/*.cpp)
add_executable(main ${SRC_FILES})
if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
    message(STATUS "C++20 or later detected")
    target_compile_definitions(main PRIVATE CXX20)
endif()
target_link_libraries(main ${OpenCV_LIBRARIES})

add_subdirectory(tests)