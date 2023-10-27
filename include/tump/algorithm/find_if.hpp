#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FIND_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FIND_IF_HPP

#include TUMP_COMMON_INCLUDE(type_value.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)

namespace tump
{
    namespace fn {
        namespace _
        {
            template <InvocableArgN<1> F, int N, TypeList List>
            struct find_if_impl : public find_if_impl<F, N + 1, pop_front_t<to_norm_li_t<List>>> {};

            template <InvocableArgN<1> F, int N, TypeList List>
            requires (bool(invoke_v<F, get_front_t<List>>))
            struct find_if_impl<F, N, List> : public type_value<get_front_t<List>, N> {};

            template <InvocableArgN<1> F, int N, TypeList List>
            requires (is_empty_v<List>)
            struct find_if_impl<F, N, List> : public type_value<mp_null_t, int(-1)> {};
        }

        /**
         * 条件に合致する一番最初の型および型の位置を取得
         * 見つからなかった場合、type = mp_null_t, value = -1 となる
        */
        template <InvocableArgN<1> F, TypeList List>
        using find_if = _::find_if_impl<F, 0, List>;
        
        /**
         * 一致する型および、位置をListの中から検索する
         * 見つからなかった場合、type = mp_null_t, value = -1 となる
        */
        template <class Search, TypeList List>
        using find = find_if<partial_apply<is_same, Search>, List>;
    }

    /**
     * 条件に合致する一番最初の型および型の位置を取得
     * 見つからなかった場合、type = mp_null_t, value = -1 となる
    */
    using find_if = cbk<fn::find_if, 2>;

    /**
     * 条件に合致する一番最初の型を取得
     * 見つからなかった場合、mp_null_t を返却
    */
    template <InvocableArgN<1> F, TypeList List>
    using find_if_t = typename fn::find_if<F, List>::type;

    /**
     * 条件に合致する一番最初の型の位置を取得
     * 見つからなかった場合、-1 を返却
    */
    template <InvocableArgN<1> F, TypeList List>
    constexpr auto find_if_v = fn::find_if<F, List>::value;

    /**
     * 一致する型および、位置をListの中から検索する
     * 見つからなかった場合、type = mp_null_t, value = -1 となる
    */
    using find = cbk<fn::find, 2>;

    /**
     * Listの中にSearchと一致する型が存在した場合、Searchをそのまま返す
     * 存在しなかった場合、mp_null_tを返す
    */
    template <class Search, TypeList List>
    using find_t = typename fn::find<Search, List>::type;

    /**
     * 一致する型の位置をListの中から検索する
     * 見つからなかった場合、-1 を返却
    */
    template <class Search, TypeList List>
    constexpr auto find_v = fn::find<Search, List>::value;
}

#endif
