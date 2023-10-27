#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP

#include TUMP_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * @class
         * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
        */
        template <Invocable F, class... Args>
        requires (is_allowed_args_size<sizeof...(Args), F>::value)
        struct apply : public std::conditional_t<
            eq_args_size<sizeof...(Args), F>::value,
            invoke<F, Args...>,
            std::type_identity<partial_apply<F, Args...>>
        > {};
    }

    /**
     * @class
     * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
    */
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using apply = cbk<fn::apply, ArgsSize>;

    /**
     * @class
     * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
    */
    template <Invocable F, class... Args>
    using apply_t = typename fn::apply<F, Args...>::type;
}

#endif
