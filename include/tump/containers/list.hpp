#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_CONTAINERS_LIST_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(containers/methods.hpp)

namespace tump_0_1_2
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
        struct make_empty<list<Types...>> : public std::type_identity<list<>> {};

        template <template <class...> class Outer, class... Types>
        requires (!std::is_base_of_v<::tump_0_1_2::_::base_list, Outer<Types...>>)
        struct make_empty<Outer<Types...>> : public std::type_identity<empty<Outer>> {};

        template <template <class...> class Outer>
        struct make_empty<empty<Outer>> : public std::type_identity<empty<Outer>> {};

        template <>
        struct is_empty<list<>> : public std::true_type {};
    }
}

#endif
