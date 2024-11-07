#ifndef TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_ALGORITHM_MP_MAXMIN_HPP
#define TUMP_V_0_1_1_INCLUDE_GUARD_TUMP_ALGORITHM_MP_MAXMIN_HPP

#include TUMP_V_0_1_1_COMMON_INCLUDE(algorithm/pop.hpp)
#include TUMP_V_0_1_1_COMMON_INCLUDE(algorithm/compare.hpp)

namespace tump_0_1_1
{
    namespace fn
    {
        /**
         * 最大と判定される型を取得する
        */
        template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
        requires (len_v<List> > 1)
        struct mp_max : public foldl<
            typename Comparing::get_grater,
            get_front_t<List>,
            pop_front_t<List>
        > {};

        template <template <auto...> class Outer, auto... Values, TumpComparing Comparing>
        struct mp_max<Outer<Values...>, Comparing> : public mp_max<to_norm_li_t<Outer<Values...>>, Comparing>::type {};

        /**
         * 最小と判定される型を取得する
        */
        template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
        requires (len_v<List> > 1)
        struct mp_min : public foldl<
            typename Comparing::get_less,
            get_front_t<List>,
            pop_front_t<List>
        > {};

        template <template <auto...> class Outer, auto... Values, TumpComparing Comparing>
        struct mp_min<Outer<Values...>, Comparing> : public mp_min<to_norm_li_t<Outer<Values...>>, Comparing>::type {};
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
    using mp_size_max = partial_apply<flip, mp_max, comparing_size>;

    /**
     * メモリ上のサイズが最小の型を取得
    */
    using mp_size_min = partial_apply<flip, mp_min, comparing_size>;

    /**
     * 最大と判定される型を取得する
    */
    template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
    using mp_max_t = typename fn::mp_max<List, Comparing>::type;

    /**
     * 最小と判定される型を取得する
    */
    template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
    using mp_min_t = typename fn::mp_min<List, Comparing>::type;

    /**
     * 最大と判定される値を取得する
    */
    template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
    constexpr auto mp_max_v = fn::mp_max<List, Comparing>::value;
    
    /**
     * 最小と判定される値を取得する
    */
    template <TypeListOrValueList List, TumpComparing Comparing = comparing_size>
    constexpr auto mp_min_v = fn::mp_min<List, Comparing>::value;
}

#endif
