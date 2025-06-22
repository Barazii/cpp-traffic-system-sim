# cmake_minimum_required(VERSION 3.11.3)

# project(traffic_system_sim)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

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

file(GLOB TESTS_SRC_FILES tests/*.cpp)
file(GLOB SRC_FILES_WITHOUT_MAIN src/*.cpp)
list(REMOVE_ITEM SRC_FILES_WITHOUT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_executable(tests ${TESTS_SRC_FILES} ${SRC_FILES_WITHOUT_MAIN})
target_link_libraries(tests ${OpenCV_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})