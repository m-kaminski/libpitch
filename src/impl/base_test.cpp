#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cassert>

#include "base.h"


namespace pitch
{
    namespace types
    {

        class base_test : public ::testing::Test
        {
        };

        TEST_F(base_test, conversions_base10)
        {
            std::string B10_1("1");
            std::string B10_10("10");
            std::string B10_144("144");
            std::string B10_948437811("948437811");
            std::string B10_MAX("9223372036854775807");
            EXPECT_EQ(read_base<10>(B10_1), 1);
            EXPECT_EQ(read_base<10>(B10_10), 10);
            EXPECT_EQ(read_base<10>(B10_144), 144);
            EXPECT_EQ(read_base<10>(B10_948437811), 948437811);
            EXPECT_EQ(read_base<10>(B10_MAX), 9223372036854775807);
        }

        TEST_F(base_test, conversions_base10_iterators)
        {
            std::string B10_1("1");
            std::string B10_10("10");
            std::string B10_144("144");
            std::string B10_948437811("948437811");
            std::string B10_MAX("9223372036854775807");
            EXPECT_EQ(read_base<10>(B10_1.begin(), B10_1.end()), 1);
            EXPECT_EQ(read_base<10>(B10_10.begin(), B10_10.end()), 10);
            EXPECT_EQ(read_base<10>(B10_144.begin(), B10_144.end()), 144);
            EXPECT_EQ(read_base<10>(B10_948437811.begin(), B10_948437811.end()), 948437811);
            EXPECT_EQ(read_base<10>(B10_MAX.begin(), B10_MAX.end()), 9223372036854775807);
        }


        TEST_F(base_test, conversion_base_35)
        {
            std::string B35_1("1");
            std::string B35_10("A");
            std::string B35_155("4F");
            std::string B35_824885977("FOOBAR");
            std::string B35_MAX("ZZZZZZZZZZZZ");
            EXPECT_EQ(read_base<35>(B35_1), 1);
            EXPECT_EQ(read_base<35>(B35_10), 10);
            EXPECT_EQ(read_base<35>(B35_155), 155);
            EXPECT_EQ(read_base<35>(B35_824885977), 824885977);
            EXPECT_EQ(read_base<35>(B35_MAX), 3478609346528894760);
            EXPECT_EQ(B35_MAX.size(), 12);
        }

        TEST_F(base_test, conversion_base_16)
        {
            std::string B35_1("1");
            std::string B35_10("A");
            std::string B35_155("9B");
            std::string B35_824885977("312AC2D9");
            EXPECT_EQ(read_base<16>(B35_1), 1);
            EXPECT_EQ(read_base<16>(B35_10), 10);
            EXPECT_EQ(read_base<16>(B35_155), 155);
            EXPECT_EQ(read_base<16>(B35_824885977), 824885977);
        }

        TEST_F(base_test, conversion_base_2)
        {
            std::string B35_1("1");
            std::string B35_10("1010");
            std::string B35_155("10011011");
            std::string B35_824885977("110001001010101100001011011001");
            EXPECT_EQ(read_base<2>(B35_1), 1);
            EXPECT_EQ(read_base<2>(B35_10), 10);
            EXPECT_EQ(read_base<2>(B35_155), 155);
            EXPECT_EQ(read_base<2>(B35_824885977), 824885977);
        }

    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
