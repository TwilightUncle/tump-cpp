#ifndef TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP
#define TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP

#include TUMP_V_0_1_0_COMMON_INCLUDE(algorithm/make_type_list.hpp)
#include TUMP_V_0_1_0_COMMON_INCLUDE(metafunction/invoke_list.hpp)

namespace tump_0_1_0
{
    namespace fn
    {
        /**
         * リストの中身をDestにコピーする
        */
        template <TypeList Src, TypeList Dest>
        requires (!is_empty_v<Src>)
        using copy = invoke_list<partial_apply<cbk<make_type_list>, Dest>, Src>;
    }

    /**
     * リストの中身をDestにコピーする
    */
    using copy = cbk<fn::copy, 2>;

    /**
     * リストの中身をDestにコピーする
    */
    template <TypeList Src, TypeList Dest>
    using copy_t = typename fn::copy<Src, Dest>::type;
}

#endif
