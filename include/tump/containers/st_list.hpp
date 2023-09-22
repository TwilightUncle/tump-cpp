#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_ST_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_ST_LIST_HPP

#include <tump/containers/list.hpp>
#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * 制約に合致する型しか要素として保持できないリスト
    */
    template <InvocableArgN<1> Constraint, class... Types>
    requires (bool(invoke_v<Constraint, Types>) && ...)
    struct st_list {};

    template <InvocableArgN<1> Constraint, class... Types>
    struct to_norm_li<st_list<Constraint, Types...>> : public std::type_identity<list<Types...>> {};

    template <InvocableArgN<1> Constraint, class... OldTypes, class... Types>
    struct unnorm_li<st_list<Constraint, OldTypes...>, list<Types...>> : public std::type_identity<st_list<Constraint, Types...>> {};

    template <InvocableArgN<1> Constraint, class... Types>
    struct make_empty<st_list<Constraint, Types...>> : public std::type_identity<st_list<Constraint>> {};

    template <InvocableArgN<1> Constraint>
    struct is_empty<st_list<Constraint>> : public std::true_type {};
}

#endif
