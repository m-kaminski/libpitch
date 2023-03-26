#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class trading_status_test : public ::testing::Test
    {
    };


    TEST_F(trading_status_test, test_build)
    {
        std::string line("29000020HAAPL    T0RR");
        //[29000020][H][AAPL    ][T][0][R][R]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        trading_status * a = dynamic_cast<trading_status*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
        EXPECT_EQ(a->get_halt_status(), types::halt_status_type::trading);
        EXPECT_EQ(a->get_reg_sho_action(), types::reg_sho_action_type::no_price_test);
    }

    TEST_F(trading_status_test, test_build_alternative)
    {
        std::string line("29000020HAAPL    Q1RR");
        //[29000020][H][AAPL    ][Q][1][R][R]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        trading_status * a = dynamic_cast<trading_status*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
        EXPECT_EQ(a->get_halt_status(), types::halt_status_type::quote_only);
        EXPECT_EQ(a->get_reg_sho_action(), types::reg_sho_action_type::price_test);
    }
    
    TEST_F(trading_status_test, test_build_bad_symbol)
    {
        std::string line("29000020HA A A   Q1RR");
        //[29000020][H][AAPL    ][Q][1][R][R]

        pitch::decoder d;        
        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Invalid space padded string", e.what());
        }
    }
    
    TEST_F(trading_status_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020HAAPL    T0RR   too long input ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 21 for trading status message", e.what());
        }
    }
    
    TEST_F(trading_status_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020HAAPL  ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 21 for trading status message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
