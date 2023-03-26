#ifndef _LIBPITCH_PITCH_AUCTION_UPDATE_H
#define _LIBPITCH_PITCH_AUCTION_UPDATE_H

#include "message.h"
#include "common_macros.h"
#include "../types/padded_string.h"
#include "../types/auction.h"

namespace pitch::messages
{

    /**
     * Class representing Auction Update message
     *
     *   --------------------------- AUCTION UPDATE ---------------------------
     *   FIELD           OFFSET    LENGTH    DATA TYPE (cboe)   DATA TYPE (C++)
     *   timestamp       0         8         decimal            uint64_t
     *   type            8         1         alpha ("I")        message_type
     *   stock_symbol    9         8         printable ascii    std::string
     *   auction_type    17        1         alpha (enum)       auction_type
     *   reference_price 18        10        decimal (price)    uint64_t
     *   buy_shares      28        10        decimal            uint64_t
     *   sell_shares     38        10        decimal            uint64_t
     *   indicative_price 48       10        decimal (price)    uint64_t
     *   LF              58
     *
     * Note: there is no long and short version here, and length of symbol corresponds to
     * lopng version of add_order and trade. There are different sets of auction types for
     * BZX and BYX exchanges, but overall structure (lengths and offsets of fields) of message
     * is the same for every US CBOE equities exchange, so no need to differentiate at code
     * level
     * 
     * Source specification:
     * https://cdn.cboe.com/resources/membership/Cboe_US_Equities_TCP_PITCH_Specification.pdf
     * As of: March 25, 2022 (pages 14-15)
     */
    class auction_update : public message
    {
    public:
        auction_update(uint64_t timestamp, std::string _symbol) : message(timestamp),
                                                                symbol(_symbol) {}
        message_type get_type() { return message_type::auction_update; }

        /**
         * stock symbol
         */
        const std::string &get_symbol() { return symbol; }

    private:
        std::string symbol;
    };

    /**
     * Class implementing builder pattern for auction_update. All methods and data fields are private
     * as it is only meant to be called by friend pitch::decoder<T1>
     */
    template <typename T1>
    class _auction_update_decoder
    {
    private:
        template <typename T2>
        static T1 decode_message(T2 begin, T2 end, uint64_t timestamp)
        {
            if (end - begin != length)
                throw std::invalid_argument("expected length of " + std::to_string(length) + " for auction update message");
            std::string symbol = pitch::types::get_padded_string(_OFFSET_PAIR(symbol_offset, symbol_length));

            return T1(new auction_update(timestamp, symbol));
        }

        static const off_t symbol_offset = 9;
        static const off_t symbol_length = 8;
        static const off_t length = 58;

        friend class pitch::decoder<T1>;
    };
}

#endif