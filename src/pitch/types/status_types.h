#ifndef _LIBPITCH_TYPES_SIDE_H
#define _LIBPITCH_TYPES_SIDE_H
#include <cstdint>
#include <stdexcept>
namespace pitch::types
{

    /// @brief enum to differentiate halt statuses
    enum halt_status_type
    {
        unknown_halt_status,
        accepting_orders,
        halted,
        quote_only,
        exchange_specific_suspension,
        trading
    };

    /**
     * convert halt status field in stream into halt_status_type, for usage in
     * trading status message.
     * @param begin iterator to character
     * @throw std::invalid_argument if character is not 'A'/'H'/'Q'/'S'/'T'
     */
    template <typename T>
    halt_status_type get_halt_status(T begin)
    {
        if (*begin == 'A')
            return halt_status_type::accepting_orders;
        else if (*begin == 'H')
            return halt_status_type::halted;
        else if (*begin == 'Q')
            return halt_status_type::quote_only;
        else if (*begin == 'S')
            return halt_status_type::exchange_specific_suspension;
        else if (*begin == 'T')
            return halt_status_type::trading;
        else
            throw std::invalid_argument("Valid side status is 'A'/'H'/'Q'/'S'/'T'");
    };
}
#endif
