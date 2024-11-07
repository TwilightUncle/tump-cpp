#ifndef TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_HPP
#define TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_HPP

#include TUMP_V_0_1_1_COMMON_INCLUDE(metafunction/partial_apply.hpp)

namespace tump_0_1_1
{
    template <class F>
    concept VFunctional = requires {
        F::value;
    };

    template <class F>
    concept TFunctional = requires {
        typename F::type;
    };

    template <class F>
    concept Functional = VFunctional<F> || TFunctional<F>;

    namespace fn
    {
        /**
         * コールバック化したメタ関数を実行
        */
        template <Invocable F, class... Args>
        requires (is_allowed_args_size<sizeof...(Args), F>::value)
        struct invoke;

        template <template <class...> class MetaFunc, unsigned int ArgsSize, class... Args>
        requires (
            (!ArgsSize || ArgsSize == sizeof...(Args))
            && Functional<MetaFunc<Args...>>
        )
        struct invoke<callback<MetaFunc, ArgsSize>, Args...> : public MetaFunc<Args...> {};

        template <Invocable InnerF, class... Args1, class... Args2>
        struct invoke<partial_apply<InnerF, Args1...>, Args2...> : public invoke<InnerF, Args1..., Args2...> {};

        template <class F>
        struct is_vfunctional : public std::bool_constant<VFunctional<F>> {};
        template <class F>
        struct is_tfunctional : public std::bool_constant<TFunctional<F>> {};
        template <class F>
        struct is_functional : public std::disjunction<is_vfunctional<F>, is_tfunctional<F>> {};
    }

    /**
     * コールバック化したメタ関数を実行
    */
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using invoke = cbk<fn::invoke, ArgsSize>;

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires TFunctional<fn::invoke<F, Args...>>
    using invoke_t = typename fn::invoke<F, Args...>::type;

    using is_vfunctional = cbk<fn::is_vfunctional, 1>;
    using is_tfunctional = cbk<fn::is_tfunctional, 1>;
    using is_functional = cbk<fn::is_functional, 1>;

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires VFunctional<fn::invoke<F, Args...>>
    constexpr auto invoke_v = fn::invoke<F, Args...>::value;

    template <class F>
    constexpr auto is_vfunctional_v = fn::is_vfunctional<F>::value;
    template <class F>
    constexpr auto is_tfunctional_v = fn::is_tfunctional<F>::value;
    template <class F>
    constexpr auto is_functional_v = fn::is_functional<F>::value;

    namespace fn
    {
        template <Invocable F, class... Args, unsigned int CheckArgsSize, bool IsCheckArgsSize>
        struct is_callback<invoke<F, Args...>, optional_args_for_is_callback<CheckArgsSize, IsCheckArgsSize>>
            : public std::false_type
        {};
    }
}

#endif
