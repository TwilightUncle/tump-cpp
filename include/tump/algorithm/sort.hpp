#ifndef TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_ALGORITHM_SORT_HPP
#define TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_ALGORITHM_SORT_HPP

#include TUMP_V_0_1_1_COMMON_INCLUDE(containers/bintree.hpp)

namespace tump_0_1_1
{
    namespace fn
    {
        /**
         * 昇順でソート。
         * 実装はヒープソートもどき。
        */
        template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
        struct sort : public invoke<
            compose_t<
                partial_apply<::tump_0_1_1::unnorm_li, List>,
                ::tump_0_1_1::flatten,
                partial_apply<
                    ::tump_0_1_1::flip,
                    ::tump_0_1_1::to_bintree,
                    Comparing
                >
            >,
            List
        > {};

        template <template <auto...> class Outer, auto... Values, TumpComparing Comparing>
        struct sort<Outer<Values...>, Comparing> : public unnorm_li<
            Outer<Values...>,
            typename sort<
                to_norm_li_t<Outer<Values...>>,
                Comparing
            >::type
        > {};
    }

    /**
     * 昇順でソート。
     * 実装はヒープソートもどき。
    */
    using sort = cbk<fn::sort, 2>;

    /**
     * 型が占有するメモリのサイズにおける昇順でソート。
    */
    using sort_size = partial_apply<flip, sort, comparing_size>;

    /**
     * 昇順でソート。
     * 実装はヒープソートもどき。
    */
    template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
    using sort_t = typename fn::sort<List, Comparing>::type;
}

#endif
