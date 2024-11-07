#ifndef TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METAFUNCTION_FLIP_HPP
#define TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METAFUNCTION_FLIP_HPP

#include TUMP_V_0_1_1_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump_0_1_1
{
    namespace fn
    {
        /**
         * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
        */
        template <InvocableArgN<2> F, class L, class R>
        using flip = invoke<F, R, L>;
    }

    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    using flip = cbk<fn::flip, 3>;

    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    template <InvocableArgN<2> F, class L, class R>
    using flip_t = typename fn::flip<F, L, R>::type;

    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    template <InvocableArgN<2> F, class L, class R>
    constexpr auto flip_v = fn::flip<F, L, R>::value;
}

#endif
