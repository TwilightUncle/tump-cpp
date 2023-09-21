#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GET_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GET_HPP

#include <tump/algorithm/len.hpp>

namespace tump
{
    /**
     * リストの先頭要素を取得
    */
    template <TypeList List>
    requires (!is_empty_v<List>)
    struct get_front;

    template <template <class...> class Outer, class Head, class... Types>
    struct get_front<Outer<Head, Types...>> : public std::type_identity<Head> {};

    /**
     * リストの先頭要素を取得
    */
    template <TypeList List>
    using get_front_t = get_front<List>::type;

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeList List>
    requires (N < len_v<List>)
    struct get;

    template <TypeList List>
    struct get<0, List> : public get_front<List> {};

    template <std::size_t N, template <class...> class Outer, class Head, class... Types>
    struct get<N, Outer<Head, Types...>> : public get<N - 1, Outer<Types...>> {};

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeList List>
    using get_t = get<N, List>::type;

    /**
     * リストの末尾要素を取得
    */
    template <TypeList List>
    requires (!is_empty_v<List>)
    using get_back = get<len_v<List> - 1, List>;

    /**
     * リストの末尾要素を取得
    */
    template <TypeList List>
    using get_back_t = get_back<List>::type;
}

#endif
