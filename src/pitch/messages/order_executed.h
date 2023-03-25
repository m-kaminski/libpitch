#ifndef _LIBPITCH_PITCH_ORDER_EXECUTE_H
#define _LIBPITCH_PITCH_ORDER_EXECUTE_H

#include "message.h"

namespace pitch::messages
{

    class order_executed : public message
    {
    public:
        order_executed() : message(1) {}
        message_type get_type() { return message_type::order_executed; }
    };

#define OFFSET_PAIR(O, L) (begin + O), (begin + O + L)
    template <typename T1>
    class _order_executed_decoder
    {
    public:
        template <typename T2>
        static T1 decode_message(T2 begin, T2 end)
        {
            T1 p_result;

            p_result.reset(new order_executed);

            return p_result;
        }
    };
#undef OFFSET_PAIR

}

#endif