#ifndef _LIBPITCH_TYPES_SIDE_H
#define _LIBPITCH_TYPES_SIDE_H
#include <cstdint>
#include <stdexcept>
namespace pitch::types
{

    /// @brief enum to differentiate buy from sell orders
    enum side_type
    {
        unknown_side,
        sell,
        buy
    };

    template <typename T>
    side_type get_side(T begin)
    {
        if (*begin == 'S')
            return side_type::sell;
        else if (*begin == 'B')
            return side_type::buy;
        else
            throw std::invalid_argument("Valid side is either 'S' or 'B'");
    };
}
#endif
