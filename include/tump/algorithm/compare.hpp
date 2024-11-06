#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_COMPARE_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_COMPARE_HPP

#include TUMP_COMMON_INCLUDE(vwrap.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/to_true.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        // 2 引数メタ関数と、制約による比較関数生成クラス
        // Compare は メンバ定数 value で 符号付き整数 を返却しなければいけない
        template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint = ::tump_1_0_0::to_true>
        struct comparing_type;

        template <class Ord, class L, class R>
        struct is_fn_comparing_type : public std::false_type {};

        template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint, class L, class R>
        requires (invoke_v<Constraint, L> && invoke_v<Constraint, R>)
        struct is_fn_comparing_type<comparing_type<Compare, Constraint>, L, R> : public std::is_signed<
            decltype(invoke_v<Compare, L, R>)
        > {};

        template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint>
        struct comparing_type
        {
            template <class L, class R>
            requires (fn::is_fn_comparing_type<comparing_type<Compare, Constraint>, L, R>::value)
            static constexpr int compare_base_v = invoke_v<Compare, L, R>;

            template <class L, class R>
            struct lt : public std::bool_constant<
                (compare_base_v<L, R> < 0)
            > {};

            template <class L, class R>
            struct gt : public std::bool_constant<
                (compare_base_v<L, R> > 0)
            > {};

            template <class L, class R>
            struct le : public std::negation<gt<L, R>> {};

            template <class L, class R>
            struct ge : public std::negation<lt<L, R>> {};

            template <class L, class R>
            struct eq : public std::bool_constant<
                (compare_base_v<L, R> == 0)
            > {};

            template <class L, class R>
            struct ne : public std::negation<eq<L, R>> {};

            template <class L, class R>
            struct get_grater : public std::conditional<
                lt<L, R>::value, R, L
            > {};

            template <class L, class R>
            struct get_less : public std::conditional<
                lt<L, R>::value, L, R
            > {};
        };
    }

    // 2 引数メタ関数と、制約による比較関数生成クラス
    // Compare は メンバ定数 value で 符号付き整数 を返却しなければいけない
    template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint = to_true>
    struct comparing_type
    {
        using fn = fn::comparing_type<Compare, Constraint>;

        using lt = cbk<fn::template lt, 2>;
        using gt = cbk<fn::template gt, 2>;
        using le = cbk<fn::template le, 2>;
        using ge = cbk<fn::template ge, 2>;
        using eq = cbk<fn::template eq, 2>;
        using ne = cbk<fn::template ne, 2>;

        template <class L, class R>
        static constexpr bool lt_v = fn::template lt<L, R>::value;
        template <class L, class R>
        static constexpr bool gt_v = fn::template gt<L, R>::value;
        template <class L, class R>
        static constexpr bool le_v = fn::template le<L, R>::value;
        template <class L, class R>
        static constexpr bool ge_v = fn::template ge<L, R>::value;
        template <class L, class R>
        static constexpr bool eq_v = fn::template eq<L, R>::value;
        template <class L, class R>
        static constexpr bool ne_v = fn::template ne<L, R>::value;

        using get_grater = cbk<fn::template get_grater, 2>;
        using get_less = cbk<fn::template get_less, 2>;

        template <class L, class R>
        using get_grater_t = typename fn::template get_grater<L, R>::type;
        template <class L, class R>
        using get_less_t = typename fn::template get_less<L, R>::type;
    };

    namespace fn
    {
        /**
         * comparing_type かどうか比較
        */
        template <class T>
        struct is_comparing_type : public std::false_type {};

        template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint>
        struct is_comparing_type<::tump_1_0_0::comparing_type<Compare, Constraint>> : public std::true_type {};

        /**
         * size_of の 結果による比較
        */
        template <class L, class R>
        struct compare_size : public vwrap<
            static_cast<int>(sizeof(L)) - static_cast<int>(sizeof(R))
        > {};

        // void は sizeof できないので、別途特殊化定義
        template <class L>
        struct compare_size<L, void> : public vwrap<int(1)> {};

        template <class R>
        struct compare_size<void, R> : public vwrap<int(-1)> {};

        template <>
        struct compare_size<void, void> : public vwrap<int(0)> {};

        /**
         * value メンバを持つ型同士での比較
        */
        template <VFunctional L, VFunctional R>
        requires (std::totally_ordered_with<decltype(L::value), decltype(R::value)>)
        struct compare_value_member : public vwrap<
            L::value == R::value
                ? int(0)
                : (L::value < R::value
                    ? int(-1)
                    : int(1)
                )
        > {};
    }

    /**
     * comparing_type かどうか比較
    */
    using is_comparing_type = cbk<fn::is_comparing_type, 1>;

    /**
     * comparing_type かどうか比較
    */
    template <class T>
    constexpr auto is_comparing_type_v = fn::is_comparing_type<T>::value;

    /**
     * comparing_type かどうか比較
    */
    template <class T>
    concept TumpComparing = is_comparing_type_v<T>;

    /**
     * size_of の 結果による比較
    */
    using compare_size = cbk<fn::compare_size, 2>;

    /**
     * size_of の 結果による比較
    */
    using comparing_size = comparing_type<compare_size>;

    /**
     * value メンバを持つもの同士での比較
    */
    using compare_value_member = cbk<fn::compare_value_member, 2>;

    /**
     * value メンバを持つもの同士での比較
    */
    using comparing_value_member = comparing_type<compare_value_member, is_vfunctional>;
}

#endif
