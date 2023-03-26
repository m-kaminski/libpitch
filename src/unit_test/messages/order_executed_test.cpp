#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class order_executed_test : public ::testing::Test
    {
    };


    TEST_F(order_executed_test, test_build_short)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091");
        //[29000600][E][A000ABDDCF0X][000020][0000ZAB00091]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        order_executed * a = dynamic_cast<order_executed*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000600);
        EXPECT_EQ(a->get_executed_shares(), 20);
        EXPECT_EQ(a->get_order_id(), 1316217846817392657LL);
        EXPECT_EQ(a->get_execution_id(), 2765178694981LL);
    }
    
    TEST_F(order_executed_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091 ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 39 for order executed message", e.what());
        }
    }
    
    TEST_F(order_executed_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB0009");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 39 for order executed message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
