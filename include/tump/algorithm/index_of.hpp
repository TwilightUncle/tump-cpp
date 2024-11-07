#ifndef TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_INDEX_OF_HPP
#define TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_INDEX_OF_HPP

#include TUMP_V_0_1_0_COMMON_INCLUDE(algorithm/find_if.hpp)

namespace tump_0_1_0
{
    namespace fn
    {
        /**
         * 一致する型の位置をListの中から検索する
         * 見つからなかった場合、value = -1 となる
        */
        template <class Search, TypeList List>
        using index_of = std::integral_constant<int, find_v<Search, List>>;

        /**
         * 条件に合致する一番最初の型および型の位置を取得
         * 見つからなかった場合、value = -1 となる
        */
        template <InvocableArgN<1> F, TypeList List>
        using index_of_if = std::integral_constant<int, find_if_v<F, List>>;
    }

    /**
     * 一致する型の位置をListの中から検索する
     * 見つからなかった場合、value = -1 となる
    */
    using index_of = cbk<fn::index_of, 2>;

    /**
     * 条件に合致する一番最初の型および型の位置を取得
     * 見つからなかった場合、value = -1 となる
    */
    using index_of_if = cbk<fn::index_of_if, 2>;

    /**
     * 一致する型の位置をListの中から検索する
     * 見つからなかった場合、 -1 となる
    */
    template <class Search, TypeList List>
    constexpr auto index_of_v = fn::index_of<Search, List>::value;

    /**
     * 条件に合致する一番最初の型および型の位置を取得
     * 見つからなかった場合、value = -1 となる
    */
    template <InvocableArgN<1> F, TypeList List>
    constexpr auto index_of_if_v = fn::index_of_if<F, List>::value;
}

#endif
