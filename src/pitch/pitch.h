#ifndef _LIBPITCH_PITCH_H
#define _LIBPITCH_PITCH_H
#include <memory>
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
        T1 decode_message(T2 begin, T2 end)
        {
            T1 p_result;

            p_result.reset(new pitch::messages::message);

            return p_result;
        }
    };
}

#endif