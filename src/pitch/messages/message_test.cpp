#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "message.h"

namespace pitch::messages
{

    class message_test : public ::testing::Test
    {
    };

    TEST_F(message_test, construct_executed)
    {
        std::shared_ptr<message> m(new order_executed);
        EXPECT_EQ(m->get_type(), message::order_executed);
    }

    TEST_F(message_test, construct_add)
    {
        std::shared_ptr<message> m(new add_order);
        EXPECT_EQ(m->get_type(), message::add_order);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
