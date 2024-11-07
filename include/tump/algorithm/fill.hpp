#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_FILL_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_FILL_HPP

#include TUMP_V_1_0_0_COMMON_INCLUDE(algorithm/make_type_list.hpp)

namespace tump_1_0_0
{
    /**
     * fill の引数
     * 非型を型で包むため定義
    */
    template <class T, std::size_t N>
    struct fill_type_arg {};

    template <auto V, std::size_t N>
    struct fill_value_arg {};

    namespace fn
    {
        namespace impl
        {
            template <TypeList List, class FillType, class Seq>
            struct fill_impl;

            template <TypeList List, class FillType, std::size_t... Indices>
            struct fill_impl<List, FillType, std::index_sequence<Indices...>> : public make_type_list<
                List,
                type_value_t<FillType, Indices>...
            > {};
        }

        /**
         * 指定の型で、指定の長さのリストを生成する
        */
        template <TypeListOrValueList List, class FillArg>
        struct fill;

        template <TypeList List, template <class, auto> class FillArg, class FillType, std::integral auto N>
        requires (N > 0)
        struct fill<List, FillArg<FillType, N>>
            : public impl::fill_impl<List, FillType, std::make_index_sequence<std::size_t(N)>>
        {};
        
        template <class List, template <auto, auto> class FillArg, auto FillValue, std::integral auto N>
        struct fill<List, FillArg<FillValue, N>> : public unnorm_li<
            List,
            typename fill<list<>, fill_type_arg<vwrap<FillValue>, N>>::type
        > {};
    }

    /**
     * 指定の型で、指定の長さのリストを生成する
    */
    using fill = cbk<fn::fill, 2>;

    /**
     * 指定の型で、指定の長さのリストを生成する
    */
    template <TypeListOrValueList List, class FillArg>
    using fill_t = typename fn::fill<List, FillArg>::type;
}

#endif
