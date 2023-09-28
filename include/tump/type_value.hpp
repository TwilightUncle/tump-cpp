#ifndef TUMP_INCLUDE_GUARD_TUMP_TYPE_VALUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_TYPE_VALUE_HPP

#include <type_traits>

namespace tump
{
    /**
     * 受け取った型と値をそのままメンバとして保持する
    */
    template <class T, auto V>
    struct type_vlaue
    {
        using type = T;
        static constexpr auto value = V;
    };

    template <class T>
    struct is_type_value : public std::false_type {};

    template <class T, auto V>
    struct is_type_value<type_vlaue<T, V>> : public std::true_type {};

    template <class T>
    constexpr auto is_type_value_v = is_type_value<T>::value;
}

#endif
