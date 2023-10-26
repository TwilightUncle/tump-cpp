#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP 10

#include TUMP_COMMON_INCLUDE(algorithm/make_type_list.hpp) // 9
#include TUMP_COMMON_INCLUDE(metafunction/invoke_list.hpp) // 3

namespace tump
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

    template <TypeList Src, TypeList Dest>
    struct fn::mp_invoke_result<copy, Src, Dest> : public constraint_st_type_list<Dest> {};
}

#endif
