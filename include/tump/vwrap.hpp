#ifndef TUMP_INCLUDE_GUARD_TUMP_VWRAP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_VWRAP_HPP

#include <type_traits>

namespace tump
{
    /**
     * 定数式評価可能な値を型に持ち上げる
    */
    template <auto V>
    struct vwrap
    {
        using type = decltype(V);
        static constexpr auto value = V;
    };

    /**
     * vwarpかどうか判定
    */
    template <class T>
    struct is_vwrap : public std::false_type {};

    template <auto V>
    struct is_vwrap<vwrap<V>> : public std::true_type {};

    /**
     * vwarpかどうか判定
    */
    template <class T>
    constexpr auto is_vwrap_v = is_vwrap<T>::value;
}

#endif
