#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

#include "pitch.h"

namespace pitch
{

    class pitch_test : public ::testing::Test
    {
    };

    TEST_F(pitch_test, construct_shared)
    {
        std::string line;
        decoder<std::shared_ptr<messages::message>> d;
        auto s_p =
            d.decode_message(line.begin(), line.end());
        EXPECT_EQ(s_p->get_type(), messages::message::message_type::unknown_message);
        static_assert(std::is_same<decltype(s_p), std::shared_ptr<messages::message>>::value,
                      "expecting a shared pointer");
    }

    TEST_F(pitch_test, construct_unique)
    {
        std::string line;
        decoder<std::unique_ptr<messages::message>> d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::unknown_message);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
    }

    TEST_F(pitch_test, construct_default)
    {
        std::string line;
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::unknown_message);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
