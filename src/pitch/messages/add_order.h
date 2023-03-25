#ifndef _LIBPITCH_PITCH_ADD_ORDER_H
#define _LIBPITCH_PITCH_ADD_ORDER_H

#include "message.h"

namespace pitch::messages
{

    class add_order : public message
    {
    public:
        message_type get_type() { return message_type::add_order; }
    };
    
    template <typename T1, typename T2>
    T1 decode_message_add_order(T2 begin, T2 end)
    {
        T1 p_result;

        p_result.reset(new add_order);

        return p_result;
    }
}

#endif