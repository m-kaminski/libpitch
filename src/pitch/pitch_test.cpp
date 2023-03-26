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

    TEST_F(pitch_test, construct_raw_pointer)
    {
        std::string line("29000600EA000ABDDCF0X0000200000ZAB00091");
        decoder<messages::message *> d;
        auto b_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(b_p->get_type(), messages::message::message_type::order_executed);
        static_assert(std::is_same<decltype(b_p), messages::message *>::value,
                      "expecting a raw C-style pointer");
        delete b_p;
    }

    TEST_F(pitch_test, construct_default_symbol_clear)
    {
        std::string line("29000020sAAPL    ");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::symbol_clear);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::symbol_clear&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::symbol_clear*>(u_p.get()));
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

    TEST_F(pitch_test, construct_default_cancel)
    {
        std::string line("28800168X1K27GA00000Y000100");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::order_cancel);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::order_cancel&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::order_cancel*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_trade)
    {
        std::string line("28880387P4K27GA0000EZB000100DRYS  0001074900000A001NJEPR");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::trade);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::trade&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::trade*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_trade_break)
    {
        std::string line("29000020B4K27GA0000EZ");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::trade_break);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::trade_break&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::trade_break*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_trading_status)
    {        
        std::string line("29000020HAAPL    T0RR");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::trading_status);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::trading_status&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::trading_status*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_auction_update)
    {        
        std::string line("29000020IAAPL    C00002137000000001000000000200000002100000123456789");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::auction_update);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::auction_update&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::auction_update*>(u_p.get()));
    }

    TEST_F(pitch_test, construct_default_auction_summary)
    {        
        std::string line("29000020JAAPL    C00002137000000001000");
        decoder d;
        auto u_p = d.decode_message(line.begin(), line.end());
        EXPECT_EQ(u_p->get_type(), messages::message::message_type::auction_summary);
        static_assert(std::is_same<decltype(u_p), std::unique_ptr<messages::message>>::value,
                      "expecting a unique pointer");
        EXPECT_NO_THROW(dynamic_cast<messages::auction_summary&>(*u_p));
        EXPECT_NE(nullptr, dynamic_cast<messages::auction_summary*>(u_p.get()));
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
