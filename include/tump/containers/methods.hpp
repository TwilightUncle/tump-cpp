#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP

#include <tump/null.hpp>
#include <tump/empty.hpp>
#include <tump/metafunction/invoke_result.hpp>

namespace tump
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
         * コンテナが持つ要素の制約を取得
        */
        template <class T>
        struct get_container_constraint;

        /**
         * 指定したリストの側だけ取り出し、空のリストを作成する
         * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
        */
        template <class List, class Constraint = typename get_container_constraint<List>::type>
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
     * コンテナが持つ要素の制約を取得
    */
    using get_container_constraint = cbk<fn::get_container_constraint, 1>;

    /**
     * コンテナが持つ要素の制約を取得
    */
    template <class T>
    using get_container_constraint_t = typename fn::get_container_constraint<T>::type;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
     * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
    */
    using make_empty = cbk<fn::make_empty, 2>;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
     * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
    */
    template <class List, class Constraint = get_container_constraint_t<List>>
    using make_empty_t = typename fn::make_empty<List, Constraint>::type;

    /**
     * 空のリストかどうか判定する
    */
    using is_empty = cbk<fn::is_empty, 1>;

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    constexpr auto is_empty_v = fn::is_empty<T>::value;

    template <class T>
    struct fn::mp_invoke_result<get_container_constraint, T> : public constraint_callback_arg1 {};
    template <class List, class Container>
    struct fn::mp_invoke_result<make_empty, List, Container> : public std::type_identity<::tump::is_empty> {};
    template <class T>
    struct fn::mp_invoke_result<is_empty, T> : public constraint_bool_constant {};
}

#endif
