#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/fold.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/apply.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/flip.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 関数の合成
        */
        template <Invocable F, Invocable... Funcs>
        struct compose : public std::type_identity<
            partial_apply<
                ::tump_0_1_2::flip,
                partial_apply<
                    ::tump_0_1_2::foldr,
                    ::tump_0_1_2::apply<>
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
}

#endif
