#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_HPP

#include <tump/metafunction/bind.hpp>

namespace tump
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

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires (_is_allowed_args_size<sizeof...(Args), F>::value)
    struct invoke;

    template <template <class...> class MetaFunc, unsigned int ArgsSize, class... Args>
    requires (
        (!ArgsSize || ArgsSize == sizeof...(Args))
        && Functional<MetaFunc<Args...>>
    )
    struct invoke<callback<MetaFunc, ArgsSize>, Args...> : public MetaFunc<Args...> {};

    template <template <class...> class OuterF, Invocable InnerF, class... Args1, class... Args2>
    struct invoke<OuterF<InnerF, Args1...>, Args2...> : public invoke<InnerF, Args1..., Args2...> {};

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires TFunctional<invoke<F, Args...>>
    using invoke_t = invoke<F, Args...>::type;

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires VFunctional<invoke<F, Args...>>
    constexpr auto invoke_v = invoke<F, Args...>::value;
}

#endif
