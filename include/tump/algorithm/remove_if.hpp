#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP 15

#include TUMP_COMMON_INCLUDE(algorithm/filter.hpp) // 14
#include TUMP_COMMON_INCLUDE(metafunction/compose.hpp) // 12

namespace tump
{
    namespace fn
    {
        /**
         * 指定条件に合致する要素のみ抽出する
        */
        template <InvocableArgN<1> F, TypeList List>
        using remove_if = filter<
            compose_t<tump::negation, F>,
            List
        >;

        /**
         * 指定の型をリストから削除する
        */
        template <class Search, TypeList List>
        using remove = unnorm_li<
            List,
            typename remove_if<partial_apply<::tump::is_same, Search>, to_norm_li_t<List>>::type
        >;
    }

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    using remove_if = cbk<fn::remove_if, 2>;

    /**
     * 指定の型をリストから削除する
    */
    using remove = cbk<fn::remove, 2>;

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using remove_if_t = typename fn::remove_if<F, List>::type;

    /**
     * 指定の型をリストから削除する
    */
    template <class Search, TypeList List>
    using remove_t = typename fn::remove<Search, List>::type;

    // TODO: Fによってリストの制約を変えるべきか考える
    template <InvocableArgN<1> F, TypeList List>
    struct fn::mp_invoke_result<remove_if, F, List> : public constraint_st_type_list<List> {};
    template <class Search, TypeList List>
    struct fn::mp_invoke_result<remove, Search, List> : public constraint_st_type_list<List> {};
}

#endif
