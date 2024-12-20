#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/get.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/apply.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 型リストに含まれるすべての要素に対して、メタ関数を適用する
        */
        template <Invocable F, TypeList List>
        struct map : public fn::unnorm_li<
            make_empty_t<List>,
            typename map<F, to_norm_li_t<List>>::type
        > {};
        
        template <Invocable F, TypeList List>
        requires (is_empty_v<List>)
        struct map<F, List> : public std::type_identity<List> {};

        template <Invocable F, class... Types>
        struct map<F, list<Types...>> : public std::type_identity<list<apply_t<F, Types>...>> {};

        /**
         * 型リストに含まれる条件に合致するすべての要素に対して、メタ関数を適用する
        */
        template <InvocableArgN<1> Pred, Invocable F, TypeList List>
        struct map_if : public fn::unnorm_li<
            make_empty_t<List>,
            typename map_if<Pred, F, to_norm_li_t<List>>::type
        > {};

        template <InvocableArgN<1> Pred, Invocable F, TypeList List>
        requires (is_empty_v<List>)
        struct map_if<Pred, F, List> : public std::type_identity<List> {};

        template <InvocableArgN<1> Pred, Invocable F, class... Types>
        struct map_if<Pred, F, list<Types...>> : public std::type_identity<list<
            apply_t<
                std::conditional_t<
                    invoke_v<Pred, Types>,
                    F,
                    ::tump_0_1_2::type_identity
                >,
                Types
            >...
        >> {};
    }

    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    using map = cbk<fn::map, 2>;

    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    template <Invocable F, TypeList List>
    using map_t = typename fn::map<F, List>::type;

    /**
     * 型リストに含まれる条件に合致するすべての要素に対して、メタ関数を適用する
    */
    using map_if = cbk<fn::map_if, 3>;

    /**
     * 型リストに含まれる条件に合致するすべての要素に対して、メタ関数を適用する
    */
    template <InvocableArgN<1> Pred, Invocable F, TypeList List>
    using map_if_t = typename fn::map_if<Pred, F, List>::type;
}

#endif
