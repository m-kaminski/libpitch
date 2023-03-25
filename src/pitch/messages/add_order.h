#ifndef _LIBPITCH_PITCH_ADD_ORDER_H
#define _LIBPITCH_PITCH_ADD_ORDER_H
#include <cstdint>
#include <string>
#include "message.h"


namespace pitch::messages
{

    /**
     * Class representing
     */
    class add_order : public message
    {
    public:
        enum side_type
        {
            unknown_side,
            sell,
            buy
        };
        add_order() : message(1) {}

        message_type get_type() { return message_type::add_order; }
        uint64_t get_order_id() { return order_id; }
        side_type get_side() { return side; }
        uint64_t get_shares() { return shares; }
        std::string get_symbol() { return symbol; }
        uint64_t get_price() { return price; }

    private:
        uint64_t order_id;
        side_type side;
        uint64_t shares;
        std::string symbol;
        uint64_t price;
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
     *   display        44        1         Alpha ("Y"/"N")     N/A (ignore)
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
     *   display        46        1         Alpha ("Y"/"N")     N/A (ignore)
     *   participant    47        4         Alpha               N/A (ignore)
     *   customer       51        1         Alphanumeric        N/A (ignore)
     *
     * Source specification:
     * https://cdn.cboe.com/resources/membership/Cboe_US_Equities_TCP_PITCH_Specification.pdf
     * As of: March 25, 2022
     */

    template <typename T1>
    class _add_decoder
    {
    private:
        template <typename T2>
        static T1 decode_message_add_order_short(T2 begin, T2 end)
        {
            T1 p_result;

            p_result.reset(new add_order);

            return p_result;
        }

        template <typename T2>
        static T1 decode_message_add_order_long(T2 begin, T2 end)
        {
            T1 p_result;

            p_result.reset(new add_order);

            return p_result;
        }

        // decode common fields that are at same offsets accross long and short versions
        template <typename T2>
        static void decode_message_add_order_common(T2 begin, T2 end, T1 m)
        {
        }

        friend class pitch::decoder<T1>;
    };
}

#endif