add_executable(base_test base_test.cpp)
target_compile_options(base_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(base_test GTest::gtest_main gcov)
gtest_discover_tests(base_test)

add_executable(base36_test base36_test.cpp)
target_compile_options(base36_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(base36_test GTest::gtest_main gcov)
gtest_discover_tests(base36_test)
