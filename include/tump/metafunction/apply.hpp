#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP

#include <tump/metafunction/invoke_result.hpp>

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
            std::type_identity<bind<F, Args...>>
        > {};
    }

    /**
     * @class
     * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
    */
    using apply = cbk<fn::apply>;

    /**
     * @class
     * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
    */
    template <Invocable F, class... Args>
    using apply_t = typename fn::apply<F, Args...>::type;

    // TODO: mp_invoke_result 定義
}

#endif
