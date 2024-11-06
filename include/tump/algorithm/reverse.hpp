#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_REVERSE_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_REVERSE_HPP

#include TUMP_V_1_0_0_COMMON_INCLUDE(algorithm/push.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        /**
         * リスト要素の並び順を反転
        */
        template <TypeListOrValueList List>
        struct reverse : public fn::unnorm_li<List, foldl_t<
            ::tump_1_0_0::push_front<>,
            list<>,
            to_norm_li_t<List>
        >> {};

        template <TypeListOrValueList List>
        requires (is_empty_v<List>)
        struct reverse<List> : public std::type_identity<List> {};
    }

    /**
     * リスト要素の並び順を反転
    */
    using reverse = cbk<fn::reverse, 1>;

    /**
     * リスト要素の並び順を反転
    */
    template <TypeListOrValueList List>
    using reverse_t = typename fn::reverse<List>::type;
}

#endif
