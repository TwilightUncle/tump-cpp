#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP

#include <tump/null.hpp>
#include <tump/containers/methods.hpp>
#include <tump/metafunction/flip.hpp>
#include <tump/algorithm/to_true.hpp>
// TODO: 制約の合成と式からの制約の推論
namespace tump
{
    /**
     * 戻り型の制約を返す。
     * 未定義の場合、nullを返却
     * 引数の型によって結果の制約が変わる場合、Argsを指定
    */
    template <Invocable F, class... Args>
    struct mp_invoke_result : public std::type_identity<cbk<to_true, 1>> {};

    template <class F, class... Args>
    using mp_invoke_result_t = typename mp_invoke_result<F, Args...>::type;

    template <template <class...> class OuterF, Invocable InnerF, class... Args1, class... Args>
    struct mp_invoke_result<OuterF<InnerF, Args1...>, Args...> : public mp_invoke_result<InnerF, Args1..., Args...> {};

    using constraint_callback_arg1 = std::type_identity<bind<cbk<flip, 3>, cbk<is_callback, 2>, optional_args_for_is_callback<1>>>;

    template <unsigned int ArgsSize, class... Args>
    struct mp_invoke_result<callback<mp_invoke_result, ArgsSize>, Args...> : public constraint_callback_arg1 {};

    /**
     * mp_invoke_result定義用
    */
    template <class T>
    struct is_bool_constant : public std::false_type {};

    template <bool B>
    struct is_bool_constant<std::bool_constant<B>> : public std::true_type {};

    using constraint_bool_constant = std::type_identity<cbk<is_bool_constant, 1>>;

    template <class T>
    struct is_size_constant : public std::false_type {};

    template <std::size_t Size>
    struct is_size_constant<std::integral_constant<std::size_t, Size>> : public std::true_type {};

    using constraint_size_constant = std::type_identity<cbk<is_size_constant, 1>>;

    /**
     * tump内の結果型について指定
    */
    template <unsigned int ArgsSize, class T>
    struct mp_invoke_result<callback<is_empty, ArgsSize>, T> : public constraint_bool_constant {};
}

#endif
