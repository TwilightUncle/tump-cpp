#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include <tump/metafunction/flip.hpp>
#include <tump/metafunction/invoke_list.hpp>
#include <tump/metafunction/invoke_result.hpp>
#include <tump/algorithm/map.hpp>
#include <tump/algorithm/fold.hpp>

// TODO: 関数合成も関数として定義する。断じて構造ではない
namespace tump
{
    /**
     * 関数の合成
    */
    template <InvocableArgN<1>... Funcs>
    requires (sizeof...(Funcs) > 0)
    struct compose : public _args_size_members<1, true> {};

    template <class T>
    struct is_compose : public std::false_type {};

    template <InvocableArgN<1>... Funcs>
    struct is_compose<compose<Funcs...>> : public std::true_type {};

    template <class T>
    constexpr auto is_compose_v = is_compose<T>::value;
    
    template <class F, unsigned int CheckArgsSize, bool IsCheckArgsSize>
    requires (is_compose_v<F>)
    struct is_callback<F, optional_args_for_is_callback<CheckArgsSize, IsCheckArgsSize>>
        : public _is_callback_impl<F, CheckArgsSize, IsCheckArgsSize>
    {};

    /**
     * @fn
     * @brief 合成済み関数用のオーバーロード
    */
    template <InvocableArgN<1>... Funcs, class Arg>
    struct invoke<compose<Funcs...>, Arg> : public foldr<
        cbk<invoke, 2>,
        Arg,
        compose<Funcs...>
    > {};

    template <InvocableArgN<1> F, InvocableArgN<1>... Funcs, class... Args>
    struct mp_invoke_result<compose<F, Funcs...>, Args...> : public mp_invoke_result<F, Args...> {};
}

#endif
