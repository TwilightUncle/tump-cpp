#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP

#include <tump/null.hpp>
#include <tump/empty.hpp>
#include <tump/metafunction/callback.hpp>
#include <tump/algorithm/to_true.hpp>

namespace tump
{
    /**
     * 処理を共通化するため、構造を一般化する
    */
    template <class T>
    struct to_norm_li : public std::type_identity<mp_null_t> {};

    template <class T>
    using to_norm_li_t = typename to_norm_li<T>::type;

    /**
     * コンテナのガワを置き換える
    */
    template <class Container, class NormalizedList>
    struct unnorm_li;

    template <class Container, class NormalizedList>
    using unnorm_li_t = typename unnorm_li<Container, NormalizedList>::type;

    /**
     * コンテナが持つ要素の制約を取得
    */
    template <class T>
    struct get_container_constraint;

    template <class T>
    using get_container_constraint_t = typename get_container_constraint<T>::type;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
     * 制約を持つコンテナに対して、任意の制約に置き換えることも可能
    */
    template <class List, class Constraint = get_container_constraint_t<List>>
    struct make_empty;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
    */
    template <class List, class Constraint = get_container_constraint_t<List>>
    using make_empty_t = typename make_empty<List, Constraint>::type;

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    struct is_empty : public std::false_type {};

    template <template <class...> class Outer>
    struct is_empty<empty<Outer>> : public std::true_type {};

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    constexpr auto is_empty_v = is_empty<T>::value;
}

#endif
