#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_POP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_POP_HPP 14

#include TUMP_COMMON_INCLUDE(algorithm/push.hpp) // 13

namespace tump
{
    namespace fn
    {
        /**
         * リストの先頭要素を除去
        */
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        struct pop_front : public fn::unnorm_li<
            List,
            typename pop_front<to_norm_li_t<List>>::type
        > {};

        template <class Head, class... Types>
        struct pop_front<list<Head, Types...>> : public std::conditional<
            sizeof...(Types) != 0,
            list<Types...>,
            list<>
        > {};

        namespace _
        {
            template <TypeList List, TypeList Result, std::size_t N>
            struct pop_back_impl : public pop_back_impl<
                List,
                push_back_t<Result, get_t<N, List>>,
                N + 1
            > {};

            template <TypeList List, TypeList Result, std::size_t N>
            requires (len_v<List> == 1)
            struct pop_back_impl<List, Result, N> : public fn::make_empty<List> {};

            template <TypeList List, TypeList Result, std::size_t N>
            requires (len_v<List> - 1 == N && N > 0)
            struct pop_back_impl<List, Result, N> : public std::type_identity<Result> {};
        }

        /**
         * リストの末尾要素を除去
        */
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        using pop_back = unnorm_li<
            List,
            typename _::pop_back_impl<
                to_norm_li_t<List>,
                list<>,
                0
            >::type
        >;
    }

    /**
     * リストの先頭要素を除去
    */
    using pop_front = cbk<fn::pop_front, 1>;

    /**
     * リストの先頭要素を除去
    */
    template <TypeListOrValueList List>
    using pop_front_t = typename fn::pop_front<List>::type;

    /**
     * リストの末尾要素を除去
    */
    using pop_back = cbk<fn::pop_back, 1>;

    /**
     * リストの末尾要素を除去
    */
    template <TypeListOrValueList List>
    using pop_back_t = typename fn::pop_back<List>::type;

    template <TypeListOrValueList List>
    struct fn::mp_invoke_result<pop_front, List> : public constraint_st_type_list<List> {};

    template <TypeListOrValueList List>
    struct fn::mp_invoke_result<pop_back, List> : public constraint_st_type_list<List> {};
}

#endif
