#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include TUMP_COMMON_INCLUDE(algorithm/fold.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/apply.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * 関数の合成
        */
        template <Invocable F, Invocable... Funcs>
        struct compose : public std::type_identity<
            partial_apply<
                ::tump::flip,
                partial_apply<
                    ::tump::foldr,
                    ::tump::apply<>
                >,
                list<F, Funcs...>
            >
        > {};
    }

    /**
     * 関数の合成
    */
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using compose = cbk<fn::compose, ArgsSize>;

    /**
     * 関数の合成
    */
    template <Invocable F, Invocable... Funcs>
    using compose_t = typename fn::compose<F, Funcs...>::type;

    template <std::size_t ArgsSize, Invocable F, Invocable... Funcs>
    struct fn::mp_invoke_result<compose<ArgsSize>, F, Funcs...> : public constraint_callback_arg1 {};
}

#endif
