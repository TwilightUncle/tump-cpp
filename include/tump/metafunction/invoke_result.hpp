#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP

#include <tump/null.hpp>
#include <tump/containers/methods.hpp>
#include <tump/metafunction/flip.hpp>
#include <tump/algorithm/to_true.hpp>

namespace tump
{
    /**
     * 戻り型の制約を返す。
     * 未定義の場合、nullを返却
     * 引数の型によって結果の制約が変わる場合、Argsを指定
    */
    template <Invocable F, class... Args>
    struct invoke_result : public std::type_identity<cbk<to_true, 1>> {};

    template <Invocable F, class... Args>
    using invoke_result_t = invoke_result<F, Args...>::type;

    template <template <class...> class OuterF, Invocable InnerF, class... Args1, class... Args>
    struct invoke_result<OuterF<InnerF, Args1...>, Args...> : public invoke_result<InnerF, Args1..., Args...> {};

    using constraint_callback_arg1 = std::type_identity<bind<cbk<flip, 3>, cbk<is_callback, 2>, optional_args_for_is_callback<1>>>;

    template <unsigned int ArgsSize, class... Args>
    struct invoke_result<callback<invoke_result, ArgsSize>, Args...> : public constraint_callback_arg1 {};

    /**
     * invoke_result定義用
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
     * 標準ライブラリの結果型指定
    */
    template <unsigned int ArgsSize, class L, class R>
    struct invoke_result<callback<std::is_same, ArgsSize>, L, R> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class T>
    struct invoke_result<callback<std::is_arithmetic, ArgsSize>, T> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class T>
    struct invoke_result<callback<std::is_integral, ArgsSize>, T> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class T>
    struct invoke_result<callback<std::is_floating_point, ArgsSize>, T> : public constraint_bool_constant {};

    /**
     * tump内の結果型について指定
    */
    template <unsigned int ArgsSize, class T>
    struct invoke_result<callback<is_empty, ArgsSize>, T> : public constraint_bool_constant {};
}

#endif
