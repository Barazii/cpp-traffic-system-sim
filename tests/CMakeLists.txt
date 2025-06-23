file(GLOB TESTS_SRC_FILES *.cpp)
file(GLOB SRC_FILES_WITHOUT_MAIN ../src/*.cpp)
list(REMOVE_ITEM SRC_FILES_WITHOUT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")

# C++20 path
add_executable(tests_cxx20 ${TESTS_SRC_FILES} ${SRC_FILES_WITHOUT_MAIN})
target_compile_definitions(tests_cxx20 PRIVATE CXX20)
target_link_libraries(tests_cxx20 ${OpenCV_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_include_directories(tests_cxx20 PRIVATE ${Boost_INCLUDE_DIRS})

# pre-C++20 path
add_executable(tests_precxx20 ${TESTS_SRC_FILES} ${SRC_FILES_WITHOUT_MAIN})
target_compile_definitions(tests_precxx20 PRIVATE)
target_link_libraries(tests_precxx20 ${OpenCV_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_include_directories(tests_precxx20 PRIVATE ${Boost_INCLUDE_DIRS})