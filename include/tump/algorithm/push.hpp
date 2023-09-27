#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP

#include <tump/algorithm/make_type_list.hpp>
#include <tump/algorithm/left_right.hpp>
#include <tump/algorithm/concat.hpp>

namespace tump
{
    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_back = concat<List, make_type_list_t<List, Types...>>;

    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_back_t = push_back<List, Types...>::type;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_front = concat<make_type_list_t<List, Types...>, List>;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_front_t = push_front<List, Types...>::type;

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの最後尾に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    struct push_back_if : public foldl<
        bind<cbk<push_back_if, 3>, F>,
        List,
        list<Types...>
    > {};

    template <InvocableArgN<1> F, TypeList List, class T>
    struct push_back_if<F, List, T> : public invoke<
        std::conditional_t<
            invoke_v<F, T>,
            cbk<push_back, 2>,
            cbk<left, 2>
        >,
        List,
        T
    > {};

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの最後尾に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    using push_back_if_t = push_back_if<F, List, Types...>::type;

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの先頭に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    struct push_front_if : public foldr<
        bind<
            cbk<flip, 3>,
            bind<cbk<push_front_if, 3>, F>
        >,
        List,
        list<Types...>
    > {};

    template <InvocableArgN<1> F, TypeList List, class T>
    struct push_front_if<F, List, T> : public invoke<
        std::conditional_t<
            invoke_v<F, T>,
            cbk<push_front, 2>,
            cbk<left, 2>
        >,
        List,
        T
    > {};

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの先頭に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    using push_front_if_t = push_front_if<F, List, Types...>::type;

    template <std::size_t ArgsSize, TypeList List, class... Types>
    struct invoke_result<callback<push_back, ArgsSize>, List, Types...> : public constraint_st_type_list<List> {};

    template <std::size_t ArgsSize, TypeList List, class... Types>
    struct invoke_result<callback<push_front, ArgsSize>, List, Types...> : public constraint_st_type_list<List> {};

    template <std::size_t ArgsSize, InvocableArgN<1> F, TypeList List, class... Types>
    struct invoke_result<callback<push_back_if, ArgsSize>, F, List, Types...> : public constraint_st_type_list<List> {};

    template <std::size_t ArgsSize, InvocableArgN<1> F, TypeList List, class... Types>
    struct invoke_result<callback<push_front_if, ArgsSize>, F, List, Types...> : public constraint_st_type_list<List> {};
}

#endif
