#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "padded_string.h"

namespace pitch::types
{
    class padded_string_test : public ::testing::Test
    {
    };

    TEST_F(padded_string_test, string_extract)
    {
        std::string from("QQQ    ");
        std::string to;
        copy_padded_string(from.begin(), from.end(), back_inserter(to));
        EXPECT_STREQ("QQQ", to.c_str());
    }

    TEST_F(padded_string_test, string_extract_padded_left)
    {
        std::string from("  QQQ    ");
        std::string to;
        copy_padded_string(from.begin() + 2, from.end(), back_inserter(to));
        EXPECT_STREQ("QQQ", to.c_str());
    }

    TEST_F(padded_string_test, string_extract_after)
    {
        std::string from("  QQQ    ");
        std::string to("X");
        copy_padded_string(from.begin() + 2, from.end(), inserter(to, to.begin()));
        EXPECT_STREQ("QQQX", to.c_str());
    }

    TEST_F(padded_string_test, check_output_iterator)
    {
        std::string from("  GM    ");
        std::string to("123456");
        auto it = copy_padded_string(from.begin() + 2, from.end(), to.begin() + 1);
        EXPECT_STREQ("1GM456", to.c_str());
        EXPECT_EQ(it, to.begin() + 3);
        EXPECT_EQ(*it, '4');
    }

    TEST_F(padded_string_test, string_extract_middle)
    {
        std::string from("  AAPL    ");
        std::string to("XY");
        copy_padded_string(from.begin() + 2, from.end(), inserter(to, to.begin() + 1));
        EXPECT_STREQ("XAAPLY", to.c_str());
    }

    TEST_F(padded_string_test, string_extract_get_string)
    {
        std::string from("SPY    ");
        std::string to(get_padded_string(from.begin(), from.end()));
        EXPECT_STREQ("SPY", to.c_str());
    }

    TEST_F(padded_string_test, string_invalid)
    {
        std::string from("QQQ   A ");
        EXPECT_THROW(get_padded_string(from.begin(), from.end()), std::invalid_argument);
        try
        {
            get_padded_string(from.begin(), from.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Invalid space padded string", e.what());
        }
    }

    TEST_F(padded_string_test, string_empty)
    {
        std::string from("         ");
        EXPECT_THROW(get_padded_string(from.begin(), from.end()), std::invalid_argument);
        try
        {
            get_padded_string(from.begin(), from.end());
        }
        catch (const std::invalid_argument &e)
        {
            EXPECT_STREQ("Empty space padded string", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
