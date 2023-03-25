#ifndef _LIBPITCH_PITCH_ORDER_EXECUTE_H
#define _LIBPITCH_PITCH_ORDER_EXECUTE_H

#include "message.h"

namespace pitch::messages
{

    class order_executed : public message
    {
    public:
        message_type get_type() { return message_type::order_executed; }
    };


    template <typename T1, typename T2>
    T1 decode_message_order_executed(T2 begin, T2 end)
    {
        T1 p_result;

        p_result.reset(new order_executed);

        return p_result;
    }

}

#endif