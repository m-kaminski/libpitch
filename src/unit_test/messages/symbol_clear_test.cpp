#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "message.h"
#include "../pitch.h"

namespace pitch::messages
{

    class symbol_clear_test : public ::testing::Test
    {
    };


    TEST_F(symbol_clear_test, test_build_short)
    {
        std::string line("29000020sAAPL    ");
        //[29000020][X][AAPL    ]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        symbol_clear * a = dynamic_cast<symbol_clear*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020LL);
        EXPECT_EQ(a->get_symbol(), "AAPL");
    }
    
    TEST_F(symbol_clear_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020sAAPL    too long input ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 17 for symbol clear message", e.what());
        }
    }
    
    TEST_F(symbol_clear_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020sAAPL ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 17 for symbol clear message", e.what());
        }
    }
    }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
