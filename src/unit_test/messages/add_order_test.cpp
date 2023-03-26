#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "messages/message.h"
#include "pitch.h"

namespace pitch::messages
{

    class add_test : public ::testing::Test
    {
    };


    TEST_F(add_test, test_build_short)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y");
        //[29000020][A][A000ABDDCF0X][S][000300][AMD   ][0000213700][Y]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        add_order * a = dynamic_cast<add_order*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020);
        EXPECT_EQ(a->get_type(), message::add_order);
        EXPECT_EQ(a->get_order_id(), 1316217846817392657LL);
        EXPECT_EQ(a->get_side(), types::side_type::sell);
        EXPECT_EQ(a->get_shares(), 300);
        EXPECT_EQ(a->get_symbol(), "AMD");
        EXPECT_EQ(a->get_price(), 213700);
    }
    
    TEST_F(add_test, test_build_short_error_handling_long_input)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 45 for short format add order message", e.what());
        }
    }
    
    TEST_F(add_test, test_build_short_error_handling_short_input)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 45 for short format add order message", e.what());
        }
    }

    TEST_F(add_test, test_build_long)
    {
        std::string line("29000020dA000ABDDCF0XS000300AMD     0000213700YRTALR");
        //[29000020][d][A000ABDDCF0X][S][000300][AMD     ][0000213700][Y][RTAL][R]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        add_order * a = dynamic_cast<add_order*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020);
        EXPECT_EQ(a->get_type(), message::add_order);
        EXPECT_EQ(a->get_order_id(), 1316217846817392657LL);
        EXPECT_EQ(a->get_side(), types::side_type::sell);
        EXPECT_EQ(a->get_shares(), 300);
        EXPECT_EQ(a->get_symbol(), "AMD");
        EXPECT_EQ(a->get_price(), 213700);
    }    

    TEST_F(add_test, test_build_long_error_handling_long_input)
    {
        std::string line("29000020dA000ABDDCF0XS000300AMD     0000213700YRTALR ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 52 for long format add order message", e.what());
        }
    }
    
    TEST_F(add_test, test_build_long_error_handling_short_input)
    {
        std::string line("29000020dA000ABDDCF0XS000300AMD     0000213700YRTAL");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 52 for long format add order message", e.what());
        }
    }}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
