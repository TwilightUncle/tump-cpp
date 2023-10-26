#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FILL_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FILL_HPP 10

#include TUMP_COMMON_INCLUDE(type_value.hpp) // 0
#include TUMP_COMMON_INCLUDE(algorithm/make_type_list.hpp) // 9

namespace tump
{
    /**
     * fill の引数
     * 非型を型で包むため定義
    */
    template <class T, std::size_t N>
    struct fill_arg {};

    namespace fn
    {
        template <TypeList List, class FillType, class Seq>
        struct fill_impl;

        template <TypeList List, class FillType, std::size_t... Indices>
        struct fill_impl<List, FillType, std::index_sequence<Indices...>> : public make_type_list<
            List,
            type_value_t<FillType, Indices>...
        > {};

        /**
         * 指定の型で、指定の長さのリストを生成する
        */
        template <TypeList List, class FillArg>
        struct fill;

        template <TypeList List, template <class, auto> class FillArg, class FillType, std::integral auto N>
        requires (N > 0)
        struct fill<List, FillArg<FillType, N>>
            : public fill_impl<List, FillType, std::make_index_sequence<std::size_t(N)>>
        {};
    }

    /**
     * 指定の型で、指定の長さのリストを生成する
    */
    using fill = cbk<fn::fill, 2>;

    /**
     * 指定の型で、指定の長さのリストを生成する
    */
    template <TypeList List, class FillArg>
    using fill_t = typename fn::fill<List, FillArg>::type;
}

#endif
