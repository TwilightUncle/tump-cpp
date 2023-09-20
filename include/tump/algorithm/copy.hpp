#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COPY_HPP

#include <tump/algorithm/make_type_list.hpp>
#include <tump/metafunction/invoke_list.hpp>

namespace tump
{
    /**
     * リストの中身をDestにコピーする
    */
    template <TypeList Src, TypeList Dest>
    requires (!is_empty_v<Src>)
    using copy = invoke_list<bind<callback<make_type_list>, Dest>, Src>;

    /**
     * リストの中身をDestにコピーする
    */
    template <TypeList Src, TypeList Dest>
    using copy_t = copy<Src, Dest>::type;
}

#endif
