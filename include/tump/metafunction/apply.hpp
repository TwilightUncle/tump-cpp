#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_HPP

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
    struct apply;

    template <template <class...> class MetaFunc, unsigned int ArgsSize, class... Args>
    requires (
        (!ArgsSize || ArgsSize == sizeof...(Args))
        && Functional<MetaFunc<Args...>>
    )
    struct apply<callback<MetaFunc, ArgsSize>, Args...> : public MetaFunc<Args...> {};

    template <template <class...> class OuterF, Invocable InnerF, class... Args1, class... Args2>
    struct apply<OuterF<InnerF, Args1...>, Args2...> : public apply<InnerF, Args1..., Args2...> {};

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires TFunctional<apply<F, Args...>>
    using apply_t = apply<F, Args...>::type;

    /**
     * コールバック化したメタ関数を実行
    */
    template <Invocable F, class... Args>
    requires VFunctional<apply<F, Args...>>
    constexpr auto apply_v = apply<F, Args...>::value;
}

#endif
