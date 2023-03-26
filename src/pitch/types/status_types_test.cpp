#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "status_types.h"

namespace pitch::types
{
    class status_types_test : public ::testing::Test
    {
    };

    TEST_F(status_types_test, string_extract_orders)
    {
        std::string from(" A ");
        halt_status_type to = get_halt_status(next(from.begin()));
        EXPECT_EQ(halt_status_type::accepting_orders, to);
    }

    TEST_F(status_types_test, string_extract_halted)
    {
        std::string from(" H ");
        halt_status_type to = get_halt_status(next(from.begin()));
        EXPECT_EQ(halt_status_type::halted, to);
    }

    TEST_F(status_types_test, string_extract_quote_only)
    {
        std::string from(" Q ");
        halt_status_type to = get_halt_status(next(from.begin()));
        EXPECT_EQ(halt_status_type::quote_only, to);
    }

    TEST_F(status_types_test, string_extract_suspension)
    {
        std::string from(" S ");
        halt_status_type to = get_halt_status(next(from.begin()));
        EXPECT_EQ(halt_status_type::exchange_specific_suspension, to);
    }

    TEST_F(status_types_test, string_extract_trading)
    {
        std::string from(" T ");
        halt_status_type to = get_halt_status(next(from.begin()));
        EXPECT_EQ(halt_status_type::trading, to);
    }

    TEST_F(status_types_test, string_extract_exception)
    {
        std::string from(" X ");

        EXPECT_THROW(get_halt_status(next(from.begin())), std::invalid_argument);
        try
        {
            get_halt_status(next(from.begin()));
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Valid side status is 'A'/'H'/'Q'/'S'/'T'", e.what());
        }
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
