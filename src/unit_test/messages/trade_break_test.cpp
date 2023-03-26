#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class trade_break_test : public ::testing::Test
    {
    };


    TEST_F(trade_break_test, test_build_short)
    {
        std::string line("29000020B4K27GA0000EZ");
        //[29000020][B][4K27GA0000EZ]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        trade_break * a = dynamic_cast<trade_break*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_execution_id(), 599834127447466523LL);
    }
    
    TEST_F(trade_break_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020B4K27GA0000EZ ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 21 for trade break message", e.what());
        }
    }
    
    TEST_F(trade_break_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020B4K27GA000 ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 21 for trade break message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
