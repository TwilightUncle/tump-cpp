#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COUNT_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COUNT_IF_HPP

#include TUMP_COMMON_INCLUDE(algorithm/filter.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        /**
         * 条件に一致する要素の数を数える
        */
        template <InvocableArgN<1> Pred, TypeList List>
        using count_if = len<filter_t<Pred, List>>;
    }

    /**
     * 条件に一致する要素の数を数える
    */
    using count_if = cbk<fn::count_if, 2>;

    /**
     * 条件に一致する要素の数を数える
    */
    template <InvocableArgN<1> Pred, TypeList List>
    constexpr auto count_if_v = fn::count_if<Pred, List>::value;
}

#endif
