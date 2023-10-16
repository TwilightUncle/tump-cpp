#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GET_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GET_HPP

#include <tuple>
#include TUMP_COMMON_INCLUDE(algorithm/len.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * リストの N 番目の要素を取得
        */
        template <std::size_t N, TypeListOrValueList List>
        requires (N < len_v<List>)
        struct get : public get<N, to_norm_li_t<List>> {};

        template <std::size_t N, auto... Values>
        struct get<N, vlist<Values...>> : public get<N, to_norm_li_t<vlist<Values...>>>::type {};

        template <std::size_t N, class Head, class... Types>
        struct get<N, list<Head, Types...>> : public std::tuple_element<N, std::tuple<Head, Types...>>{};

        /**
         * リストの先頭要素を取得
        */
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        using get_front = get<0, List>;

        /**
         * リストの末尾要素を取得
        */
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        using get_back = get<len_v<List> - 1, List>;
    }

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeListOrValueList List>
    using get_t = typename fn::get<N, List>::type;

    /**
     * リストの N 番目の要素を取得
    */
    template <std::size_t N, TypeListOrValueList List>
    constexpr auto get_v = fn::get<N, List>::value;

    /**
     * リストの先頭要素を取得
    */
    using get_front = cbk<fn::get_front, 1>;

    /**
     * リストの先頭要素を取得
    */
    template <TypeListOrValueList List>
    using get_front_t = typename fn::get_front<List>::type;

    /**
     * リストの先頭要素を取得
    */
    template <TypeListOrValueList List>
    constexpr auto get_front_v = fn::get_front<List>::value;

    /**
     * リストの末尾要素を取得
    */
    using get_back = cbk<fn::get_back, 1>;

    /**
     * リストの末尾要素を取得
    */
    template <TypeListOrValueList List>
    constexpr auto get_back_v = fn::get_back<List>::value;

    /**
     * リストの末尾要素を取得
    */
    template <TypeListOrValueList List>
    using get_back_t = typename fn::get_back<List>::type;

    template <TypeListOrValueList List>
    struct fn::mp_invoke_result<get_front, List> : public fn::get_container_constraint<List> {};

    // TODO: get の戻り値制約についても考える(本メタ関数を格納可能なcallbackを定義か？)

    template <TypeListOrValueList List>
    struct fn::mp_invoke_result<get_back, List> : public fn::get_container_constraint<List> {}; 
}

#endif
