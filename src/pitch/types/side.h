#ifndef _LIBPITCH_TYPES_SIDE_H
#define _LIBPITCH_TYPES_SIDE_H
#include <cstdint>
#include <stdexcept>
namespace pitch::types {


        /// @brief enum to differentiate buy from sell orders
        enum side_type
        {
            unknown_side,
            sell,
            buy
        };
}
#endif
