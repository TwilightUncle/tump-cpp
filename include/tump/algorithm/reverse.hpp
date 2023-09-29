#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REVERSE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REVERSE_HPP

#include <tump/algorithm/push.hpp>

namespace tump
{
    /**
     * リスト要素の並び順を反転
    */
    template <TypeList List>
    struct reverse : public unnorm_li<List, foldl_t<
        cbk<push_front, 2>,
        list<>,
        to_norm_li_t<List>
    >> {};

    /**
     * リスト要素の並び順を反転
    */
    template <TypeList List>
    requires (is_empty_v<List>)
    struct reverse<List> : public std::type_identity<List> {};

    /**
     * リストの先頭要素を除去
    */
    template <TypeList List>
    using reverse_t = typename reverse<List>::type;

    template <unsigned int ArgsSize, TypeList List>
    struct mp_invoke_result<callback<reverse, ArgsSize>, List> : public constraint_st_type_list<List> {};
}

#endif
