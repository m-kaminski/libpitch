#ifndef _LIBPITCH_PITCH_MESSAGES_H
#define _LIBPITCH_PITCH_MESSAGES_H

namespace pitch::messages
{
    /**
     * base class of a message
     */
    class message
    {
    public:
        /**
         * Enumerate types of messages
         */
        enum message_type
        {
            /// parse error or failed construction
            unknown_message = 0,
            /// defined on page 6 of spec.
            symbol_clear = 1,
            /// add pending order, page 7
            add_order = 2,
            /// long version of add order, to accommodate longer symbold, see page 8
            add_order_long = 3,
            /// order fully or partially executed, page 9
            order_executed = 4,
            /// page 10
            order_cancel = 5,
            /// trade on symbol that was not part of add_order page 10
            trade = 6,
            /// long version of trade, see page 11
            trade_long = 7,
            /// page 12
            trade_break = 8,
            /// page 13
            trading_status = 9,
            /// auction update, pages 14-15, there are separate versions of this message for BYX and BZX
            auction_update = 10
        };
        virtual message_type get_type() { return message_type::unknown_message; }
    };


}
#include "add_order.h"
#include "order_execute.h"

#endif