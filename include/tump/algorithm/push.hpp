#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP

#include <tump/algorithm/make_type_list.hpp>
#include <tump/algorithm/left_right.hpp>
#include <tump/algorithm/concat.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 型リストの最後尾に指定されたパラメータパックを挿入する
        */
        template <TypeList List, class... Types>
        using push_back = concat<List, make_type_list_t<List, Types...>>;

        /**
         * 型リストの先頭に指定されたパラメータパックを挿入する
        */
        template <TypeList List, class... Types>
        using push_front = concat<make_type_list_t<List, Types...>, List>;
    }

    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    using push_back = cbk<fn::push_back>;

    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_back_t = typename fn::push_back<List, Types...>::type;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    using push_front = cbk<fn::push_front>;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_front_t = typename fn::push_front<List, Types...>::type;

    namespace fn
    {
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
                ::tump::push_back,
                ::tump::left
            >,
            List,
            T
        > {};


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
                ::tump::push_front,
                ::tump::left
            >,
            List,
            T
        > {};
    }

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの最後尾に追加
    */
    using push_back_if = cbk<fn::push_back_if>;

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの最後尾に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    using push_back_if_t = typename fn::push_back_if<F, List, Types...>::type;

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの先頭に追加
    */
    using push_front_if = cbk<fn::push_front_if>;

    /**
     * 指定さ入れたパラメータパックのうち、条件に合致する要素のみ型リストの先頭に追加
    */
    template <InvocableArgN<1> F, TypeList List, class... Types>
    using push_front_if_t = typename fn::push_front_if<F, List, Types...>::type;

    template <TypeList List, class... Types>
    struct fn::mp_invoke_result<push_back, List, Types...> : public constraint_st_type_list<List> {};

    template <TypeList List, class... Types>
    struct fn::mp_invoke_result<push_front, List, Types...> : public constraint_st_type_list<List> {};

    template <InvocableArgN<1> F, TypeList List, class... Types>
    struct fn::mp_invoke_result<push_back_if, F, List, Types...> : public constraint_st_type_list<List> {};

    template <InvocableArgN<1> F, TypeList List, class... Types>
    struct fn::mp_invoke_result<push_front_if, F, List, Types...> : public constraint_st_type_list<List> {};
}

#endif
