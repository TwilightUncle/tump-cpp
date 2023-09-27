#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP

#include <tump/metafunction/invoke_result.hpp>

namespace tump
{
    /**
     * 任意の型を任意の個数要素として保持できるリスト
    */
    template <class... Types>
    struct list {};

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    template <template <class...> class Outer, class... Types>
    struct to_norm_li<Outer<Types...>> : public std::type_identity<list<Types...>> {};

    template <template <class...> class Outer>
    struct to_norm_li<empty<Outer>> : public std::type_identity<list<>> {};

    template <template <class...> class Outer, class... OldTypes, class... Types>
    struct unnorm_li<Outer<OldTypes...>, list<Types...>> : public std::type_identity<Outer<Types...>> {};

    template <template <class...> class Outer, class... Types>
    struct unnorm_li<empty<Outer>, list<Types...>> : public std::type_identity<Outer<Types...>> {};

    template <class... Types, class Constraint>
    struct make_empty<list<Types...>, Constraint> : public std::type_identity<list<>> {};

    template <>
    struct is_empty<list<>> : public std::true_type {};
}

#endif
