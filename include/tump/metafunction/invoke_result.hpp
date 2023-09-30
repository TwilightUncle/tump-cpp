#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_RESULT_HPP

#include <tump/algorithm/to_true.hpp>
#include <tump/metafunction/flip.hpp>
// TODO: 制約の合成と式からの制約の推論
namespace tump
{
    namespace fn
    {
        /**
         * 戻り型の制約を返す。
         * 未定義の場合、nullを返却
         * 引数の型によって結果の制約が変わる場合、Argsを指定
        */
        template <Invocable F, class... Args>
        struct mp_invoke_result : public std::type_identity<cbk<to_true, 1>> {};

        template <template <class...> class OuterF, Invocable InnerF, class... Args1, class... Args>
        struct mp_invoke_result<OuterF<InnerF, Args1...>, Args...> : public mp_invoke_result<InnerF, Args1..., Args...> {};
    }

    using mp_invoke_result = cbk<fn::mp_invoke_result>;

    /**
     * 戻り型の制約を返す。
     * 未定義の場合、nullを返却
     * 引数の型によって結果の制約が変わる場合、Argsを指定
    */
    template <class F, class... Args>
    using mp_invoke_result_t = typename fn::mp_invoke_result<F, Args...>::type;

    using constraint_callback_arg1 = std::type_identity<bind<cbk<flip, 3>, cbk<is_callback, 2>, optional_args_for_is_callback<1>>>;

    namespace fn
    {
        /**
         * bool_constantの型のインスタンスの場合真
        */
        template <class T>
        struct is_bool_constant : public std::false_type {};

        template <bool B>
        struct is_bool_constant<std::bool_constant<B>> : public std::true_type {};
    }

    /**
     * bool_constantの型のインスタンスの場合真
    */
    using is_bool_constant = cbk<fn::is_bool_constant, 1>;

    /**
     * bool_constantの型のインスタンスの場合真
    */
    template <class T>
    constexpr auto is_bool_constant_v = fn::is_bool_constant<T>::value;

    using constraint_bool_constant = std::type_identity<is_bool_constant>;

    namespace fn
    {
        /**
         * size_tのintegral_constantの型のインスタンスの場合真
        */
        template <class T>
        struct is_size_constant : public std::false_type {};

        template <std::size_t Size>
        struct is_size_constant<std::integral_constant<std::size_t, Size>> : public std::true_type {};
    }

    /**
     * size_tのintegral_constantの型のインスタンスの場合真
    */
    using is_size_constant = cbk<fn::is_size_constant, 1>;

    /**
     * size_tのintegral_constantの型のインスタンスの場合真
    */
    template <class T>
    constexpr auto is_size_constant_v = fn::is_size_constant<T>::value;

    using constraint_size_constant = std::type_identity<is_size_constant>;

    template <class... Args>
    struct fn::mp_invoke_result<mp_invoke_result, Args...> : public constraint_callback_arg1 {};

    template <class T>
    struct fn::mp_invoke_result<is_bool_constant, T> : public constraint_bool_constant {};

    template <class T>
    struct fn::mp_invoke_result<is_size_constant, T> : public constraint_bool_constant {};
}

#endif
