#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class order_cancel_test : public ::testing::Test
    {
    };


    TEST_F(order_cancel_test, test_build_short)
    {
        std::string line("28800168X1K27GA00000Y000100");
        //[28800168][X][1K27GA00000Y][000100]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        order_cancel * a = dynamic_cast<order_cancel*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 28800168LL);
        EXPECT_EQ(a->get_canceled_shares(), 100);
        EXPECT_EQ(a->get_order_id(), 204969015920664610LL);
    }
    
    TEST_F(order_cancel_test, test_build_short_error_handling_long_input)
    {
        std::string line("28800168X1K27GA00000Y000100 ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 27 for order cancel message", e.what());
        }
    }
    
    TEST_F(order_cancel_test, test_build_short_error_handling_short_input)
    {
        std::string line("28800168X1K27GA00000Y00010");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 27 for order cancel message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
