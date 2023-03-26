#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "types/auction.h"

namespace pitch::types
{
    class auction_type_test : public ::testing::Test
    {
    };

    TEST_F(auction_type_test, opening_auction)
    {
        std::string from(" O ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::opening_auction, to);
    }

    TEST_F(auction_type_test, closing_auction)
    {
        std::string from(" C ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::closing_auction, to);
    }

    TEST_F(auction_type_test, halt_auction)
    {
        std::string from(" H ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::halt_auction, to);
    }

    TEST_F(auction_type_test, ipo_auction)
    {
        std::string from(" I ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::ipo_auction, to);
    }

    TEST_F(auction_type_test, cboe_market_close)
    {
        std::string from(" M ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::cboe_market_close, to);
    }

    TEST_F(auction_type_test, periodic_auction)
    {
        std::string from(" P ");
        auction_type to = get_auction_type(next(from.begin()));
        EXPECT_EQ(auction_type::periodic_auction, to);
    }

    TEST_F(auction_type_test, string_extract_auction_exception)
    {
        std::string from(" X ");

        EXPECT_THROW(get_auction_type(next(from.begin())), std::invalid_argument);
        try
        {
            get_auction_type(next(from.begin()));
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Valid auction type is 'O'/'C'/'H'/'I'/'M'/'P'", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
