#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SORT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SORT_HPP

#include TUMP_COMMON_INCLUDE(containers/btree.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * 昇順でソート。
         * 実装はヒープソートもどき。
        */
        template <TypeList List, TumpComparing Comparing = comparing_size>
        struct sort : public invoke<
            compose_t<
                partial_apply<::tump::unnorm_li, List>,
                ::tump::flatten,
                partial_apply<
                    ::tump::flip,
                    ::tump::to_btree,
                    Comparing
                >
            >,
            List
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
    template <TypeList List, TumpComparing Comparing = comparing_size>
    using sort_t = typename fn::sort<List, Comparing>::type;
}

#endif
