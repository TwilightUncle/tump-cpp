#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_ARRAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_ARRAY_HPP

#include <tump/containers/st_list.hpp>

namespace tump
{
    /**
     * 要素数固定で、制約に合致する型しか要素として保持できないコンテナ
     * 現在、要素数を変更するようなalgorithm配下の関数は未実装(制約エラーとなる)
    */
    template <InvocableArgN<1> Constraint, std::size_t N, class... Types>
    requires (sizeof...(Types) == N || sizeof...(Types) == 0)
    struct array : public st_list<Constraint, Types...> {};

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    template <InvocableArgN<1> Constraint, std::size_t N, class... Types>
    struct to_norm_li<array<Constraint, N, Types...>> : public std::type_identity<list<Types...>> {};

    template <InvocableArgN<1> Constraint, std::size_t N, class... OldTypes, class... Types>
    struct unnorm_li<array<Constraint, N, OldTypes...>, list<Types...>> : public std::type_identity<array<Constraint, N, Types...>> {};

    template <InvocableArgN<1> Constraint, std::size_t N, class... Types>
    struct get_container_constraint<array<Constraint, N, Types...>> : public std::type_identity<Constraint> {};

    template <InvocableArgN<1> Constraint, std::size_t N, class... Types, InvocableArgN<1> NewConstraint>
    struct make_empty<array<Constraint, N, Types...>, NewConstraint> : public std::type_identity<array<NewConstraint, N>> {};

    template <InvocableArgN<1> Constraint, std::size_t N>
    struct is_empty<array<Constraint, N>> : public std::true_type {};
}

#endif
