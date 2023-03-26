
add_executable(auction_test auction_test.cpp)
target_compile_options(auction_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(auction_test GTest::gtest_main gcov)
gtest_discover_tests(auction_test)

add_executable(base_test base_test.cpp)
target_compile_options(base_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(base_test GTest::gtest_main gcov)
gtest_discover_tests(base_test)

add_executable(base36_test base36_test.cpp)
target_compile_options(base36_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(base36_test GTest::gtest_main gcov)
gtest_discover_tests(base36_test)

add_executable(padded_string_test padded_string_test.cpp)
target_compile_options(padded_string_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(padded_string_test GTest::gtest_main gcov)
gtest_discover_tests(padded_string_test)

add_executable(side_test side_test.cpp)
target_compile_options(side_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(side_test GTest::gtest_main gcov)
gtest_discover_tests(side_test)

add_executable(status_types_test status_types_test.cpp)
target_compile_options(status_types_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(status_types_test GTest::gtest_main gcov)
gtest_discover_tests(status_types_test)