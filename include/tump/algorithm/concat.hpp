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

    template <class... Types>
    struct concat<list<>, list<Types...>> : std::type_identity<list<Types...>> {};

    template <class... Types>
    struct concat<list<Types...>, list<>> : std::type_identity<list<Types...>> {};

    template <>
    struct concat<list<>, list<>> : std::type_identity<list<>> {};

    template <class... Types>
    struct concat<list<Types...>> : std::type_identity<list<Types...>> {};

    /**
     * 複数のリストを結合する
     * ただし、リストの側として利用されているテンプレート型は共通でなければいけない
    */
    template <TypeList... Lists>
    using concat_t = typename concat<Lists...>::type;

    template <std::size_t ArgsSize, TypeList List, TypeList... Lists>
    struct invoke_result<callback<concat, ArgsSize>, List, Lists...> : public constraint_st_type_list<List> {};
}

#endif
