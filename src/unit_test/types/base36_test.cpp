#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cassert>

#include "types/base.h"

namespace pitch::types
{
    static const std::uint64_t base36_max = 4738381338321616895LL; //  value of 12 'Z' characters (largest all-Z sequence)

    class base36_test : public ::testing::Test
    {
    };

    TEST_F(base36_test, conversion_1_MAX)
    {
        std::string B36_1("1");
        std::string B36_10("A");
        std::string B36_144("40");
        std::string B36_948437811("FOOBAR");
        std::string B36_MAX("ZZZZZZZZZZZZ");
        EXPECT_EQ(get_base36(B36_1), 1);
        EXPECT_EQ(get_base36(B36_10), 10);
        EXPECT_EQ(get_base36(B36_144), 144);
        EXPECT_EQ(get_base36(B36_948437811), 948437811);
        EXPECT_EQ(get_base36(B36_MAX), base36_max);
        EXPECT_EQ(B36_MAX.size(), 12);
    }

    TEST_F(base36_test, conversion_10_MAX_iterators)
    {
        std::string B36_10("A");
        std::string B36_144("40");
        std::string B36_948437811("FOOBAR");
        std::string B36_MAX("ZZZZZZZZZZZZ");
        EXPECT_EQ(get_base36(B36_10.begin(), B36_10.end()), 10);
        EXPECT_EQ(get_base36(B36_144.begin(), B36_144.end()), 144);
        EXPECT_EQ(get_base36(B36_948437811.begin(), B36_948437811.end()), 948437811);
        EXPECT_EQ(get_base36(B36_MAX.begin(), B36_MAX.end()), base36_max);
    }

    TEST_F(base36_test, conversion_0)
    {
        std::string B36_0("0");
        EXPECT_EQ(get_base36(B36_0.begin(), B36_0.end()), 0);
    }

    TEST_F(base36_test, conversion_empty)
    {
        std::string B36_E(""); // empty string converted to 0
        EXPECT_EQ(get_base36(B36_E.begin(), B36_E.end()), 0);
    }

    TEST_F(base36_test, conversion_lowercase_throw)
    {
        std::string B36_L("foobar"); // Lowercase
        EXPECT_THROW(get_base36(B36_L.begin(), B36_L.end()), std::invalid_argument);
        try
        {
            get_base36(B36_L.begin(), B36_L.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Not a base36 digit", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
