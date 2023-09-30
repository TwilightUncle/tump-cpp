#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP

#include <tump/containers/methods.hpp>

namespace tump
{
    namespace _
    {
        /**
         * 本プロジェクトで定義するコンテナの識別用
        */
        struct base_list {};
    }

    /**
     * 任意の型を任意の個数要素として保持できるリスト
    */
    template <class... Types>
    struct list : public _::base_list {};

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    namespace fn
    {
        template <template <class...> class Outer, class... Types>
        struct to_norm_li<Outer<Types...>> : public std::type_identity<list<Types...>> {};

        template <template <class...> class Outer>
        struct to_norm_li<empty<Outer>> : public std::type_identity<list<>> {};

        template <template <class...> class Outer, class... OldTypes, class... Types>
        struct unnorm_li<Outer<OldTypes...>, list<Types...>> : public std::type_identity<Outer<Types...>> {};

        template <template <class...> class Outer, class... Types>
        struct unnorm_li<empty<Outer>, list<Types...>> : public std::type_identity<Outer<Types...>> {};

        template <class... Types>
        struct get_container_constraint<list<Types...>> : public std::type_identity<cbk<to_true, 1>> {};

        template <class T>
        requires (!std::is_base_of_v<::tump::_::base_list, T>)
        struct get_container_constraint<T> : public std::type_identity<cbk<to_true, 1>> {};

        template <class... Types, class Constraint>
        struct make_empty<list<Types...>, Constraint> : public std::type_identity<list<>> {};

        template <template <class...> class Outer, class... Types, class Constraint>
        requires (!std::is_base_of_v<::tump::_::base_list, Outer<Types...>>)
        struct make_empty<Outer<Types...>, Constraint> : public std::type_identity<empty<Outer>> {};

        template <template <class...> class Outer, class Constraint>
        struct make_empty<empty<Outer>, Constraint> : public std::type_identity<empty<Outer>> {};

        template <>
        struct is_empty<list<>> : public std::true_type {};
    }
}

#endif
