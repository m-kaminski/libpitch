#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "types/rpi.h"

namespace pitch::types
{
    class rpi_type_test : public ::testing::Test
    {
    };

    TEST_F(rpi_type_test, buy_and_sell_side)
    {
        std::string from(" A ");
        rpi_type to = get_rpi_type(next(from.begin()));
        EXPECT_EQ(rpi_type::buy_and_sell_side, to);
    }

    TEST_F(rpi_type_test, buy_side)
    {
        std::string from(" B ");
        rpi_type to = get_rpi_type(next(from.begin()));
        EXPECT_EQ(rpi_type::buy_side, to);
    }

    TEST_F(rpi_type_test, sell_side)
    {
        std::string from(" S ");
        rpi_type to = get_rpi_type(next(from.begin()));
        EXPECT_EQ(rpi_type::sell_side, to);
    }

    TEST_F(rpi_type_test, no_rpi)
    {
        std::string from(" N ");
        rpi_type to = get_rpi_type(next(from.begin()));
        EXPECT_EQ(rpi_type::no_rpi, to);
    }

    TEST_F(rpi_type_test, string_extract_rpi_exception)
    {
        std::string from(" X ");

        EXPECT_THROW(get_rpi_type(next(from.begin())), std::invalid_argument);
        try
        {
            get_rpi_type(next(from.begin()));
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Valid rpi type is 'B'/'S'/'A'/'N'", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
