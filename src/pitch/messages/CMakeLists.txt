add_executable(message_test message_test.cpp)
target_compile_options(message_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(message_test GTest::gtest_main gcov)
gtest_discover_tests(message_test)

# keep same ordering of tests, as ordering of messages in Cboe spec
add_executable(symbol_clear_test symbol_clear_test.cpp)
target_compile_options(symbol_clear_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(symbol_clear_test GTest::gtest_main gcov)
gtest_discover_tests(symbol_clear_test)

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

add_executable(trade_break_test trade_break_test.cpp)
target_compile_options(trade_break_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(trade_break_test GTest::gtest_main gcov)
gtest_discover_tests(trade_break_test)

add_executable(trading_status_test trading_status_test.cpp)
target_compile_options(trading_status_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(trading_status_test GTest::gtest_main gcov)
gtest_discover_tests(trading_status_test)

add_executable(auction_update_test auction_update_test.cpp)
target_compile_options(auction_update_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
target_link_libraries(auction_update_test GTest::gtest_main gcov)
gtest_discover_tests(auction_update_test)
