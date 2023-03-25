#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cassert>

#include "message.h"


namespace pitch
{
    namespace messages
    {

        class message_test : public ::testing::Test
        {
        };

        TEST_F(message_test, construct)
        {
            message m;
            EXPECT_EQ(m.get_type(), message_type::unknown_message);
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
