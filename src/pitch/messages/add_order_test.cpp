#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "message.h"
#include "../pitch.h"

namespace pitch::messages
{

    class add_test : public ::testing::Test
    {
    };


    TEST_F(add_test, test_build_short)
    {
        std::string line("29000020AA000ABDDCF0XS000300AMD   0000213700Y");
        //[29000020][A][A000ABDDCF0X][S][000300][AMD   ][0000213700][Y]

        pitch::decoder d;
        auto p = d.decode_message(line.begin(), line.end());
        add_order * a = dynamic_cast<add_order*>(p.get());
        EXPECT_EQ(a->get_timestamp(), 29000020);
        EXPECT_EQ(a->get_type(), message::add_order);
        EXPECT_EQ(a->get_side(), types::side_type::sell);
        EXPECT_EQ(a->get_shares(), 300);
        EXPECT_EQ(a->get_order_id(), 1316217846817392657LL);
        EXPECT_EQ(a->get_symbol(), "AMD");
        EXPECT_EQ(a->get_price(), 213700);
    }
    
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
