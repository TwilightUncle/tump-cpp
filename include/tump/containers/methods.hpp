#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(metatype.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 処理を共通化するため、構造を一般化する
        */
        template <class T>
        struct to_norm_li : public std::type_identity<mp_null_t> {};

        /**
         * コンテナのガワを置き換える
        */
        template <class Container, class NormalizedList>
        struct unnorm_li;

        /**
         * 指定したリストの側だけ取り出し、空のリストを作成する
         * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
        */
        template <class List>
        struct make_empty;

        /**
         * 空のリストかどうか判定する
        */
        template <class T>
        struct is_empty : public std::false_type {};

        template <template <class...> class Outer>
        struct is_empty<empty<Outer>> : public std::true_type {};
    }

    /**
     * 処理を共通化するため、構造を一般化する
    */
    using to_norm_li = cbk<fn::to_norm_li, 1>;

    /**
     * 処理を共通化するため、構造を一般化する
    */
    template <class T>
    using to_norm_li_t = typename fn::to_norm_li<T>::type;

    /**
     * コンテナのガワを置き換える
    */
    using unnorm_li = cbk<fn::unnorm_li, 2>;

    /**
     * コンテナのガワを置き換える
    */
    template <class Container, class NormalizedList>
    using unnorm_li_t = typename fn::unnorm_li<Container, NormalizedList>::type;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
     * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
    */
    using make_empty = cbk<fn::make_empty, 1>;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
     * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
    */
    template <class List>
    using make_empty_t = typename fn::make_empty<List>::type;

    /**
     * 空のリストかどうか判定する
    */
    using is_empty = cbk<fn::is_empty, 1>;

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    constexpr auto is_empty_v = fn::is_empty<T>::value;
}

#endif
