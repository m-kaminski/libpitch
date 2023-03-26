#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class retail_price_improvement_test : public ::testing::Test
    {
    };


    TEST_F(retail_price_improvement_test, test_build_retail_price_improvement_message)
    {
        std::string line("29000020RAAPL    A");
        //[29000020][R][AAPL    ][A]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        retail_price_improvement * a = dynamic_cast<retail_price_improvement*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
        EXPECT_EQ(a->get_rpi_type(), types::rpi_type::buy_and_sell_side);
    }
    
    TEST_F(retail_price_improvement_test, test_build_error_handling_long_input)
    {
        std::string line("29000020RAAPL    A    too long input ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 18 for retail price improvement message", e.what());
        }
    }
    
    TEST_F(retail_price_improvement_test, test_build_error_handling_short_input)
    {
        std::string line("29000020RAAPL ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 18 for retail price improvement message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
