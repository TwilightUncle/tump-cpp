#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_FILTER_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_FILTER_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/invoke_list.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/push.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 指定条件に合致する要素のみ抽出する
        */
        template <InvocableArgN<1> F, TypeList List>
        using filter = invoke_list<
            partial_apply<
                cbk<push_back_if>,
                F,
                make_empty_t<List>
            >,
            to_norm_li_t<List>
        >;
    }

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    using filter = cbk<fn::filter, 2>;

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using filter_t = typename fn::filter<F, List>::type;
}

#endif
