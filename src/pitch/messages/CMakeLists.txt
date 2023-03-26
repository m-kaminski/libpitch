add_executable(message_test message_test.cpp)
target_compile_options(message_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(message_test GTest::gtest_main gcov)
gtest_discover_tests(message_test)

add_executable(add_order_test add_order_test.cpp)
target_compile_options(add_order_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(add_order_test GTest::gtest_main gcov)
gtest_discover_tests(add_order_test)

add_executable(order_executed_test order_executed_test.cpp)
target_compile_options(order_executed_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(order_executed_test GTest::gtest_main gcov)
gtest_discover_tests(order_executed_test)

add_executable(order_cancel_test order_cancel_test.cpp)
target_compile_options(order_cancel_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(order_cancel_test GTest::gtest_main gcov)
gtest_discover_tests(order_cancel_test)

add_executable(trade_test trade_test.cpp)
target_compile_options(trade_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(trade_test GTest::gtest_main gcov)
gtest_discover_tests(trade_test)
