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


    /**
     *   ------------------ ADD ORDER: Standard (short) format ----------------
     *   FIELD          OFFSET    LENGTH    DATA TYPE (cboe)    DATA TYPE (C++) 
     *   timestamp      0         8         decimal             uint64_t
     *   type           8         1         alpha ("A")         message_type
     *   order_id       9         12        base36              uint64_t
     *   side           21        1         alpha ("B"/"S")     side_type
     *   shares         22        6         decimal             uint64_t
     *   stock_symbol   28        6         printable ascii     std::string
     *   price          34        10        price(decimal)      uint64_t
     *   display        44        1         Alpha ("Y"/"N")     bool
     * 
     *   ------------------ ADD ORDER: Extended (long) format -----------------
     *   FIELD          OFFSET    LENGTH    DATA TYPE (cboe)    DATA TYPE (C++) 
     *   timestamp      0         8         decimal             uint64_t
     *   type           8         1         alpha ("d")         message_type
     *   order_id       9         12        base36              uint64_t
     *   side           21        1         alpha ("B"/"S")     side_type
     *   shares         22        6         decimal             uint64_t
     *   stock_symbol   28        8         printable ascii     std::string
     *   price          36        10        price(decimal)      uint64_t
     *   display        46        1         Alpha ("Y"/"N")     bool
     *   participant    47        4         Alpha               N/A (ignore)
     *   customer       51        1         Alphanumeric        N/A (ignore)
     */

    template <typename T1, typename T2>
    T1 decode_message_add_order_short(T2 begin, T2 end)
    {
        T1 p_result;

        p_result.reset(new add_order);

        return p_result;
    }

    template <typename T1, typename T2>
    T1 decode_message_add_order_long(T2 begin, T2 end)
    {
        T1 p_result;

        p_result.reset(new add_order);

        return p_result;
    }

    // decode common fields that are at same offsets accross long and short versions
    template <typename T1, typename T2>
    void decode_message_add_order_common(T2 begin, T2 end, T1 m)
    {

    }
}

#endif