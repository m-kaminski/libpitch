#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "message.h"
#include "../pitch.h"

namespace pitch::messages
{

    class auction_update_test : public ::testing::Test
    {
    };


    TEST_F(auction_update_test, test_build_short)
    {
        std::string line("29000020IAAPL    C0000213700000000100000000020000000210000");
        //[29000020][X][AAPL    ][C][0000213700][0000001000][0000002000][0000210000]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        auction_update * a = dynamic_cast<auction_update*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
    }
    
    TEST_F(auction_update_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020IAAPL    C0000213700000000100000000020000000210000  extra characters");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 58 for auction update message", e.what());
        }
    }
    
    TEST_F(auction_update_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020IAAPL    C00002137000000001000000000200000002100");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 58 for auction update message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
