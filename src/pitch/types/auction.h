#ifndef _LIBPITCH_TYPES_AUCTION_H
#define _LIBPITCH_TYPES_AUCTION_H
#include <cstdint>
#include <stdexcept>
namespace pitch::types
{

    /// @brief auction types
    enum auction_type
    {
        unknown_auction_type,
        opening_auction,
        closing_auction,
        halt_auction,
        ipo_auction,
        cboe_market_close,
        periodic_auction
    };


    /**
     * convert auction type field in stream into auction_type, for usage in
     * auction_summary and auction_update messages.
     * @param begin iterator to character
     * @throw std::invalid_argument if character is not 'A'/'H'/'Q'/'S'/'T'
     */
    template <typename T>
    auction_type get_auction_type(T begin)
    {
        if (*begin == 'O')
            return auction_type::opening_auction;
        else if (*begin == 'C')
            return auction_type::closing_auction;
        else if (*begin == 'H')
            return auction_type::halt_auction;
        else if (*begin == 'I')
            return auction_type::ipo_auction;
        else if (*begin == 'M')
            return auction_type::cboe_market_close;
        else if (*begin == 'P')
            return auction_type::periodic_auction;
        else
            throw std::invalid_argument("Valid auction type is 'O'/'C'/'H'/'I'/'M'/'P'");
    };
}
#endif
