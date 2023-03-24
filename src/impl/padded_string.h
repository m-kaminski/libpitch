#ifndef _LIBPITCH_IMPL_TYPES_PADDED_STRING_H
#define _LIBPITCH_IMPL_TYPES_PADDED_STRING_H
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>
namespace pitch::types {
    
    template <typename T1, typename T2>
    void copy_padded_string(T1 begin, const T1 &end, T2 out_begin)
    {
        while (begin != end) {
            if (*begin == ' ') {
                break;
            }
            *out_begin = *begin;
            out_begin++;
            begin++;
        }
        if (!std::all_of(begin, end, std::bind(std::equal_to<char>(), ' ', std::placeholders::_1))) {
            throw std::invalid_argument("Invalid space padded string");
        }
    };

    template <typename T>
    std::string get_padded_string(T begin, const T &end)
    {
        std::string result;
        copy_padded_string(begin,end,back_inserter(result));
        return result;
    };
}
#endif