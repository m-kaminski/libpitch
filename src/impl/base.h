#ifndef _LIBPITCH_IMPL_TYPES_BASE36_H
#define _LIBPITCH_IMPL_TYPES_BASE36_H
#include <cstdint>
#include <stdexcept>
namespace pitch::types {


    template <int base, typename T>
    std::uint64_t read_base(T begin, const T &end)
    {
        std::uint64_t result = 0;
        while (begin != end)
        {
            int d;
            if (*begin >= '0' && *begin <= '9')
                d = *begin - '0';
            else if (*begin >= 'A' && *begin <= 'Z')
                d = *begin - 'A' + 10;
            else
                throw std::invalid_argument("Not a base36 digit");
            result *= base;
            result += d;

            begin++;
        }

        return result;
    };

    template <int base, typename T>
    std::uint64_t read_base(T s)
    {
        return read_base<base>(s.begin(), s.end());
    }

    /***
     * Convert a range of characters into base36 number. Accepts 0-9 and A-Z as digits
     * type is a forward iterator to a char
     * @param begin iterator to a begining of number to convert
     * @param end iterator to an ending of number to convert
     * @throw std::invalid_argument if more than 12 base36 digits or incorrect digit
     */
    template <typename T>
    std::uint64_t read_base36(T begin, const T &end) {
        return read_base<36>(begin, end);
    }

    /***
     * Convert a string-equivalent to base36 number
     * @param s string-equivalent input, at most 12-characters long
     * @throw std::invalid_argument if more than 12 base36 digits or incorrect digit
     */
    template <typename T>
    std::uint64_t read_base36(T s)
    {
        return read_base36(s.begin(), s.end());
    }

}
#endif
