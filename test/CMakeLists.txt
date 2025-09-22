cmake_minimum_required(VERSION 3.11.3)

file(GLOB TEST_SOURCES *.cpp)

file(GLOB CORE_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Exclude the application main from tests to avoid multiple mains
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

add_executable(unit_tests ${TEST_SOURCES} ${CORE_SOURCES})

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(unit_tests PRIVATE Boost::unit_test_framework ${OpenCV_LIBRARIES})