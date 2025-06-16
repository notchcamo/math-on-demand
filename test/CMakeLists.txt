# By notchcamo.

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the google_tests_run target
add_executable(google_tests_run vector3_test.cpp
        lerp_test.cpp
        matrix_test.cpp
        util_test.cpp)

# linking google_tests_run with the library which will be tested

target_link_libraries(google_tests_run gtest gtest_main)
