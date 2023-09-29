#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP

#include <tump/algorithm/make_type_list.hpp>
#include <tump/metafunction/invoke_list.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * リストの中身をDestにコピーする
        */
        template <TypeList Src, TypeList Dest>
        requires (!is_empty_v<Src>)
        using copy = invoke_list<bind<::tump::make_type_list, Dest>, Src>;
    }

    using copy = cbk<fn::copy, 2>;

    /**
     * リストの中身をDestにコピーする
    */
    template <TypeList Src, TypeList Dest>
    using copy_t = typename fn::copy<Src, Dest>::type;

    template <TypeList Src, TypeList Dest>
    struct mp_invoke_result<copy, Src, Dest> : public constraint_st_type_list<Dest> {};
}

#endif
