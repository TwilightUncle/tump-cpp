#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP

#include TUMP_COMMON_INCLUDE(algorithm/filter.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/compose.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        namespace impl
        {
            template <TypeList Acc, class Cur>
            using unique = push_back_if<
                compose_t<
                    negation,
                    partial_apply<::tump_1_0_0::flip, ::tump_1_0_0::exists, Acc>
                >,
                Acc,
                Cur
            >;
        }

        /**
         * リストの重複を除去する
        */
        template <TypeListOrValueList List>
        using unique = unnorm_li<
            List,
            foldl_t<
                cbk<impl::unique, 2>,
                list<>,
                to_norm_li_t<List>>
            >;
    }

    /**
     * リストの重複を除去する
    */
    using unique = cbk<fn::unique, 1>;

    /**
     * リストの重複を除去する
    */
    template <TypeListOrValueList List>
    using unique_t = typename fn::unique<List>::type;

    namespace fn
    {
        /**
         * リストの内容が一意であるか判定
        */
        template <TypeListOrValueList List>
        using is_unique = std::is_same<to_norm_li_t<List>, unique_t<to_norm_li_t<List>>>;
    }

    /**
     * リストの内容が一意であるか判定
    */
    using is_unique = cbk<fn::is_unique, 1>;

    /**
     * リストの内容が一意であるか判定
    */
    template <TypeListOrValueList List>
    constexpr auto is_unique_v = fn::is_unique<List>::value;
}

#endif
