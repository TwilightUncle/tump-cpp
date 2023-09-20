#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_CONCAT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_CONCAT_HPP

#include <tump/list.hpp>
#include <tump/algorithm/fold.hpp>

namespace tump
{
    /**
     * 複数のリストを結合する
     * ただし、リストの側として利用されているテンプレート型は共通でなければいけない
    */
    template <TypeList List1, TypeList... Lists>
    struct concat : public foldl<callback<concat, 2>, make_empty_t<List1>, list<List1, Lists...>> {};

    template <template <class...> class Outer, class... Inner1, class... Inner2>
    struct concat<Outer<Inner1...>, Outer<Inner2...>> : public std::type_identity<Outer<Inner1..., Inner2...>> {};

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
}

#endif
