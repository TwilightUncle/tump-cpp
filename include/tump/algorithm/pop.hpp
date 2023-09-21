#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_POP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_POP_HPP

#include <tump/algorithm/get.hpp>
#include <tump/algorithm/push.hpp>

namespace tump
{
    /**
     * リストの先頭要素を除去
    */
    template <TypeList List>
    requires (!is_empty_v<List>)
    struct pop_front;

    template <TypeList List>
    requires (len_v<List> == 1)
    struct pop_front<List> : public make_empty<List> {};

    template <template <class...> class Outer, class Head, class... Types>
    requires (sizeof...(Types) > 0)
    struct pop_front<Outer<Head, Types...>> : public std::type_identity<Outer<Types...>> {};

    /**
     * リストの先頭要素を除去
    */
    template <TypeList List>
    using pop_front_t = pop_front<List>::type;

    template <TypeList List, TypeList Result, std::size_t N>
    struct pop_back_impl : public pop_back_impl<
        List,
        push_back_t<Result, get_t<N, List>>,
        N + 1
    > {};

    template <TypeList List, TypeList Result, std::size_t N>
    requires (len_v<List> == 1)
    struct pop_back_impl<List, Result, N> : public make_empty<List> {};

    template <TypeList List, TypeList Result, std::size_t N>
    requires (len_v<List> - 1 == N && N > 0)
    struct pop_back_impl<List, Result, N> : public std::type_identity<Result> {};

    /**
     * リストの末尾要素を除去
    */
    template <TypeList List>
    requires (!is_empty_v<List>)
    using pop_back = pop_back_impl<List, make_empty_t<List>, 0>;

    /**
     * リストの末尾要素を除去
    */
    template <TypeList List>
    using pop_back_t = pop_back<List>::type;
}

#endif
