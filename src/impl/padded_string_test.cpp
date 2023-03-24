#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "padded_string.h"

namespace pitch
{
    namespace types
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
            copy_padded_string(from.begin()+2, from.end(), back_inserter(to));
            EXPECT_STREQ("QQQ", to.c_str());
        }

        TEST_F(padded_string_test, string_extract_after)
        {
            std::string from("  QQQ    ");
            std::string to("X");
            copy_padded_string(from.begin()+2, from.end(), inserter(to, to.begin()));
            EXPECT_STREQ("QQQX", to.c_str());
        }

        TEST_F(padded_string_test, string_extract_middle)
        {
            std::string from("  QQQ    ");
            std::string to("XY");
            copy_padded_string(from.begin()+2, from.end(), inserter(to, to.begin()+1));
            EXPECT_STREQ("XQQQY", to.c_str());
        }

        TEST_F(padded_string_test, string_extract_get_string)
        {
            std::string from("QQQ    ");
            std::string to(get_padded_string(from.begin(), from.end()));
            EXPECT_STREQ("QQQ", to.c_str());
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
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
