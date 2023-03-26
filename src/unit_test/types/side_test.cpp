#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "side.h"

namespace pitch::types
{
    class side_test : public ::testing::Test
    {
    };

    TEST_F(side_test, string_extract_sell)
    {
        std::string from(" S ");
        side_type to = get_side(next(from.begin()));
        EXPECT_EQ(side_type::sell, to);
    }

    TEST_F(side_test, string_extract_buy)
    {
        std::string from(" B ");
        side_type to = get_side(next(from.begin()));
        EXPECT_EQ(side_type::buy, to);
    }

    TEST_F(side_test, string_extract_exception)
    {
        std::string from(" X ");

        EXPECT_THROW(get_side(next(from.begin())), std::invalid_argument);
        try
        {
            get_side(next(from.begin()));
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Valid side is either 'S' or 'B'", e.what());
        }
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
