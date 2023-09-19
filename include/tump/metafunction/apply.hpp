#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP

#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * @class
     * @brief 引数に対して、コールバック化したメタ関数の適用を行う。引数がすべて埋まっている or 引数の数が不明な場合はメタ関数を実行し、少ない場合は部分適用をする
    */
    template <Invocable F, class... Args>
    requires (_is_allowed_args_size<sizeof...(Args), F>::value)
    struct apply : public invoke_t<F, Args...> {};

    template <Invocable F, class... Args>
    requires (!_eq_args_size<sizeof...(Args), F>::value)
    struct apply<F, Args...> : public bind<F, Args...> {};

    template <Invocable F, class... Args, unsigned int CheckArgsSize, bool IsCheckArgsSize>
    requires (std::is_base_of_v<bind<F, Args...>, apply<F, Args...>>)
    struct is_callback<apply<F, Args...>, optional_args_for_is_callback<CheckArgsSize, IsCheckArgsSize>>
        : public is_callback<bind<F, Args...>>
    {};
}

#endif
