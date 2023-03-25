#ifndef _LIBPITCH_PITCH_H
#define _LIBPITCH_PITCH_H
#include <memory>
#include <array>
#include <functional>
#include "messages/message.h"
namespace pitch
{

    /*
     * @param T1 output type to be initialized with raw pointer to pitch::messages::message*,
     * recommended choice is either std::unique_ptr<message> or std::shared_ptr<message>, but other
     * choices are available up to user. Using raw pointer is discouraged, as it can break
     * exception safety
     */
    template <typename T1 = std::unique_ptr<messages::message>>
    class decoder
    {
    public:

    
        /***
         * @param T2 input type of an iterator
         * @param begin begining of line to decode
         * @param end end of line to decode
         */
        template <typename T2>
        static T1 decode_message(T2 begin, T2 end)
        {
            T1 p_result;
            if (end - begin < 9)
                return p_result;
            // message type is always single character at offset 8
            switch (*(begin+8)) {
                case 'E': return messages::decode_message_order_executed<T1,T2>(begin, end);
                case 'A': return messages::decode_message_add_order_short<T1,T2>(begin, end);
                case 'd': return messages::decode_message_add_order_long<T1,T2>(begin, end);
                default: ;
            }
            return p_result;
        }





    };
}

#endif