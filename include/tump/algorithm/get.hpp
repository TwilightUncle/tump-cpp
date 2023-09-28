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
    struct get_front : public get_front<to_norm_li_t<List>> {};

    template <class Head, class... Types>
    struct get_front<list<Head, Types...>> : public std::type_identity<Head> {};

    /**
     * リストの先頭要素を取得
    */
    template <TypeList List>
    using get_front_t = typename get_front<List>::type;

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeList List>
    requires (N < len_v<List>)
    struct get : public get<N, to_norm_li_t<List>> {};

    template <class... Types>
    struct get<0, list<Types...>> : public get_front<list<Types...>> {};

    template <std::size_t N, class Head, class... Types>
    requires (N != 0)
    struct get<N, list<Head, Types...>> : public get<N - 1, list<Types...>> {};

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeList List>
    using get_t = typename get<N, List>::type;

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
    using get_back_t = typename get_back<List>::type;

    template <unsigned int ArgsSize, TypeList List>
    struct invoke_result<callback<get_front, ArgsSize>, List> : public get_container_constraint<List> {};

    // TODO: get の戻り値制約についても考える(本メタ関数を格納可能なcallbackを定義か？)

    template <unsigned int ArgsSize, TypeList List>
    struct invoke_result<callback<get_back, ArgsSize>, List> : public get_container_constraint<List> {}; 
}

#endif
