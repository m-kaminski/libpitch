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


    /// @brief enum track reg SHO actions
    enum reg_sho_action_type
    {
        unknown_reg_sho_action,
        no_price_test,
        price_test
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

    /**
     * convert reg SHO actions field in stream into reg_sho_action_type, 
     * for usage in trade and add_order messages.
     * @param begin iterator to character
     * @throw std::invalid_argument if character is not 'S' or 'B'
     */
    template <typename T>
    reg_sho_action_type get_reg_sho_action(T begin)
    {
        if (*begin == '0')
            return reg_sho_action_type::no_price_test;
        else if (*begin == '1')
            return reg_sho_action_type::price_test;
        else
            throw std::invalid_argument("Valid reg SHO action status is either '0' or '1'");
    };
}
#endif