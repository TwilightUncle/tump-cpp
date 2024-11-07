#ifndef TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METATYPE_VWRAP_HPP
#define TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METATYPE_VWRAP_HPP

#include TUMP_V_0_1_1_COMMON_INCLUDE(metafunction/callback.hpp)

namespace tump_0_1_1
{
    /**
     * 定数式評価可能な値を型に持ち上げる
    */
    template <auto V>
    struct vwrap
    {
        using value_type = decltype(V);
        using type = vwrap<V>;
        static constexpr auto value = V;
    };

    namespace fn
    {
        /**
         * vwarpかどうか判定
        */
        template <class T>
        struct is_vwrap : public std::false_type {};

        template <auto V>
        struct is_vwrap<vwrap<V>> : public std::true_type {};
    }

    /**
     * vwarpかどうか判定
    */
    using is_wrap = cbk<fn::is_vwrap, 1>;

    /**
     * vwarpかどうか判定
    */
    template <class T>
    constexpr auto is_vwrap_v = fn::is_vwrap<T>::value;
}

#endif
