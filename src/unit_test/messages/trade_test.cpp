#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "message.h"
#include "../pitch.h"

namespace pitch::messages
{
    class trade_test : public ::testing::Test
    {
    };

    TEST_F(trade_test, test_build_short)
    {
        std::string line("28880387P4K27GA0000EZB000100DRYS  0001074900000A001NJEPR");
        //[28880387][P][4K27GA0000EZ][B][000100][DRYS  ][0001074900][000A001NJEPR]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        trade *a = dynamic_cast<trade *>(p.get());
        EXPECT_EQ(a->get_timestamp(), 28880387LL);
        EXPECT_EQ(a->get_type(), message::trade);
        EXPECT_EQ(a->get_order_id(), 599834127447466523LL);
        EXPECT_EQ(a->get_side(), types::side_type::buy);
        EXPECT_EQ(a->get_shares(), 100);
        EXPECT_EQ(a->get_symbol(), "DRYS");
        EXPECT_EQ(a->get_price(), 1074900);
        EXPECT_EQ(a->get_execution_id(), 28211199077439);
    }

    TEST_F(trade_test, test_build_short_error_handling_long_input)
    {
        std::string line("28880387P4K27GA0000EZB000100DRYS  0001074900000A001NJEPR ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 56 for short format trade message", e.what());
        }
    }

    TEST_F(trade_test, test_build_short_error_handling_short_input)
    {
        std::string line("28880387P4K27GA0000EZB000100DRYS  0001074900000A001NJEP");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 56 for short format trade message", e.what());
        }
    }

    TEST_F(trade_test, test_build_long)
    {
        std::string line("28880387r4K27GA0000EZB000100DRYS    0001074900000A001NJEPR");
        //[28880387][r][4K27GA0000EZ][B][000100][DRYS    ][0001074900][000A001NJEPR]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        trade *a = dynamic_cast<trade *>(p.get());
        EXPECT_EQ(a->get_timestamp(), 28880387LL);
        EXPECT_EQ(a->get_type(), message::trade);
        EXPECT_EQ(a->get_order_id(), 599834127447466523LL);
        EXPECT_EQ(a->get_side(), types::side_type::buy);
        EXPECT_EQ(a->get_shares(), 100);
        EXPECT_EQ(a->get_symbol(), "DRYS");
        EXPECT_EQ(a->get_price(), 1074900);
        EXPECT_EQ(a->get_execution_id(), 28211199077439);
    }

    TEST_F(trade_test, test_build_long_error_handling_long_input)
    {
        std::string line("28880387r4K27GA0000EZB000100DRYS    0001074900000A001NJEPR ");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 58 for long format trade message", e.what());
        }
    }

    TEST_F(trade_test, test_build_long_error_handling_short_input)
    {
        std::string line("28880387r4K27GA0000EZB000100DRYS    0001074900000A001NJEP");
        pitch::decoder d;

        EXPECT_THROW(d.decode_message(line.begin(), line.end()), std::invalid_argument);
        try
        {
            d.decode_message(line.begin(), line.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("expected length of 58 for long format trade message", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
