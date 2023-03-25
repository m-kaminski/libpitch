add_executable(message_test message_test.cpp)
target_compile_options(message_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(message_test GTest::gtest_main gcov)
gtest_discover_tests(message_test)
