#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include TUMP_COMMON_INCLUDE(algorithm/fold.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * 関数の合成
        */
        template <InvocableArgN<1> F, InvocableArgN<1>... Funcs>
        struct compose : public std::type_identity<
            partial_apply<
                ::tump::flip,
                partial_apply<
                    ::tump::foldr,
                    ::tump::invoke
                >,
                list<F, Funcs...>
            >
        > {};
    }

    /**
     * 関数の合成
    */
    using compose = cbk<fn::compose, 2>;

    /**
     * 関数の合成
    */
    template <InvocableArgN<1> F, InvocableArgN<1>... Funcs>
    using compose_t = typename fn::compose<F, Funcs...>::type;

    template <std::size_t ArgsSize, InvocableArgN<1> F, InvocableArgN<1>... Funcs>
    struct fn::mp_invoke_result<cbk<fn::compose, ArgsSize>, F, Funcs...> : public constraint_callback_arg1 {};
}

#endif
