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
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091");
        decoder<std::shared_ptr<messages::message>> d;
        auto s_p =
            d.decode_message(line.begin(), line.end());
        EXPECT_EQ(s_p->get_type(), messages::message::message_type::order_executed);
        static_assert(std::is_same<decltype(s_p), std::shared_ptr<messages::message>>::value,
                      "expecting a shared pointer");
    }

    TEST_F(pitch_test, construct_unique)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091");
        decoder<std::unique_ptr<messages::message>> d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::order_executed);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
    }

    TEST_F(pitch_test, construct_default_executed)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::order_executed);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::order_executed&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::order_executed*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_add)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::add_order);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::add_order&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::add_order*>(u_p.get()));
    }

    TEST_F(pitch_test, timestamp_parsed_add)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(dynamic_cast<messages::add_order&>(*u_p).get_timestamp(),29000020LL);
    }
    
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}