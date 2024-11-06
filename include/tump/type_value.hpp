#ifndef TUMP_INCLUDE_GUARD_TUMP_TYPE_VALUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_TYPE_VALUE_HPP

#include <type_traits>

namespace tump_1_0_0
{
    /**
     * 受け取った型と値をそのままメンバとして保持する
    */
    template <class T, auto V>
    struct type_value
    {
        using type = T;
        static constexpr auto value = V;
    };

    template <class T, auto V>
    using type_value_t = typename type_value<T, V>::type;

    template <class T, auto V>
    constexpr auto type_value_v = type_value<T, V>::value;

    template <class T>
    struct is_type_value : public std::false_type {};

    template <class T, auto V>
    struct is_type_value<type_value<T, V>> : public std::true_type {};

    template <class T>
    constexpr auto is_type_value_v = is_type_value<T>::value;
}

#endif
