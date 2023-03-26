#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class auction_summary_test : public ::testing::Test
    {
    };


    TEST_F(auction_summary_test, test_build_short)
    {
        std::string line("29000020JAAPL    C00002137000000001000");
        //[29000020][J][AAPL    ][C][0000213700][0000001000]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        auction_summary * a = dynamic_cast<auction_summary*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
        EXPECT_EQ(a->get_auction_type(), types::auction_type::closing_auction);

        EXPECT_EQ(a->get_price(), 213700);
        EXPECT_EQ(a->get_shares(), 1000);
    }
    
    TEST_F(auction_summary_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020JAAPL    C0000213700000000100000000020000000210000  extra characters");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 38 for auction summary message", e.what());
        }
    }
    
    TEST_F(auction_summary_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020JAAPL    C000021370");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 38 for auction summary message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
