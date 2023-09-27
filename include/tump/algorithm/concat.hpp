#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_CONCAT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_CONCAT_HPP

#include <tump/algorithm/fold.hpp>

namespace tump
{
    /**
     * 複数のリストを結合する
     * ただし、リストの側として利用されているテンプレート型は共通でなければいけない
    */
    template <TypeList List1, TypeList... Lists>
    requires (std::is_same_v<make_empty_t<List1>, make_empty_t<Lists>> && ...)
    struct concat : public unnorm_li<
        List1,
        typename foldl<
            callback<concat, 2>,
            list<>,
            list<to_norm_li_t<List1>, to_norm_li_t<Lists>...>
        >::type
    > {};

    template <class... Inner1, class... Inner2>
    struct concat<list<Inner1...>, list<Inner2...>> : public std::type_identity<list<Inner1..., Inner2...>> {};

    template <TypeList List>
    requires (!is_empty_v<List>)
    struct concat<make_empty_t<List>, List> : std::type_identity<List> {};

    template <TypeList List>
    struct concat<List, make_empty_t<List>> : std::type_identity<List> {};

    template <TypeList List>
    struct concat<List> : std::type_identity<List> {};

    /**
     * 複数のリストを結合する
     * ただし、リストの側として利用されているテンプレート型は共通でなければいけない
    */
    template <TypeList... Lists>
    using concat_t = concat<Lists...>::type;

    template <std::size_t ArgsSize, TypeList List, TypeList... Lists>
    struct invoke_result<callback<concat, ArgsSize>, List, Lists...> : public constraint_st_type_list<List> {};
}

#endif
