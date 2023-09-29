#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include <tump/metafunction/invoke_list.hpp>
#include <tump/algorithm/fold.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 関数の合成
        */
        template <InvocableArgN<1> F, InvocableArgN<1>... Funcs>
        struct compose : public std::type_identity<
            bind<
                cbk<flip, 3>,
                bind<
                    ::tump::foldr,
                    cbk<invoke, 2>
                >,
                list<F, Funcs...>
            >
        > {};
    }

    /**
     * 関数の合成
    */
    using compose = cbk<fn::compose>;

    /**
     * 関数の合成
    */
    template <InvocableArgN<1> F, InvocableArgN<1>... Funcs>
    using compose_t = typename fn::compose<F, Funcs...>::type;

    template <InvocableArgN<1> F, InvocableArgN<1>... Funcs>
    struct mp_invoke_result<compose, F, Funcs...> : public constraint_callback_arg1 {};
}

#endif
