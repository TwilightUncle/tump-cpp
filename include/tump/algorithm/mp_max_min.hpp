#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_MAXMIN_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_MAXMIN_HPP

#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/compare.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * 最大と判定される型を取得する
        */
        template <TypeList List, TumpComparing Comparing = comparing_size>
        requires (len_v<List> > 1)
        struct mp_max : public foldl<
            typename Comparing::get_grater,
            get_front_t<List>,
            pop_front_t<List>
        > {};

        /**
         * 最小と判定される型を取得する
        */
        template <TypeList List, TumpComparing Comparing = comparing_size>
        requires (len_v<List> > 1)
        struct mp_min : public foldl<
            typename Comparing::get_less,
            get_front_t<List>,
            pop_front_t<List>
        > {};
    }

    /**
     * 最大と判定される型を取得する
    */
    using mp_max = cbk<fn::mp_max, 2>;

    /**
     * 最小と判定される型を取得する
    */
    using mp_min = cbk<fn::mp_min, 2>;

    /**
     * メモリ上のサイズが最大の型を取得
    */
    using mp_size_max = partial_apply<flip, mp_max, compare_size>;

    /**
     * メモリ上のサイズが最小の型を取得
    */
    using mp_size_min = partial_apply<flip, mp_min, compare_size>;

    /**
     * 最大と判定される型を取得する
    */
    template <TypeList List, TumpComparing Comparing = comparing_size>
    using mp_max_t = typename fn::mp_max<List, Comparing>::type;

    /**
     * 最小と判定される型を取得する
    */
    template <TypeList List, TumpComparing Comparing = comparing_size>
    using mp_min_t = typename fn::mp_min<List, Comparing>::type;
}

#endif
