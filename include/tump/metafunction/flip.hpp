#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_FLIP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_FLIP_HPP

#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    template <Invocable F, class L, class R>
    using flip = invoke<F, R, L>;

    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    template <Invocable F, class L, class R>
    using flip_t = invoke_t<F, R, L>;

    /**
     * 2引数を受け取るコールバック化したメタ関数に対し、引数の順序を入れ替えた上で実行  
    */
    template <Invocable F, class L, class R>
    constexpr auto flip_v = invoke_v<F, R, L>;
}

#endif
