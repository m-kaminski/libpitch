include_directories(../include/pitch)

add_executable(pitch_test pitch_test.cpp)
target_compile_options(pitch_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(pitch_test GTest::gtest_main gcov)
gtest_discover_tests(pitch_test)

add_subdirectory(types)
add_subdirectory(messages)
