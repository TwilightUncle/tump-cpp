#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COMPARE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_COMPARE_HPP

#include TUMP_COMMON_INCLUDE(vwrap.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/to_true.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump
{
    // 2 引数メタ関数と、制約による比較関数生成クラス
    // Compare は メンバ定数 value で 符号付き整数 を返却しなければいけない
    template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint = to_true>
    struct type_comparing;

    namespace fn
    {
        template <class Ord, class L, class R>
        struct is_type_comparing : public std::false_type {};

        template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint, class L, class R>
        requires (invoke_v<Constraint, L> && invoke_v<Constraint, R>)
        struct is_type_comparing<type_comparing<Compare, Constraint>, L, R> : public std::is_signed<
            decltype(invoke_v<Compare, L, R>)
        > {};
    }

    using is_type_comparing = cbk<fn::is_type_comparing, 3>;

    template <class Ord, class L, class R>
    constexpr auto is_type_comparing_v = fn::is_type_comparing<Ord, L, R>::value;

    template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint>
    struct type_comparing
    {
        template <class L, class R>
        requires (is_type_comparing_v<type_comparing<Compare, Constraint>, L, R>)
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
    };

    namespace fn
    {
        // size_of の 結果による比較
        template <class L, class R>
        struct compare_size : public vwrap<
            static_cast<int>(sizeof(L)) - static_cast<int>(sizeof(R))
        > {};
    }

    // size_of の 結果による比較
    using compare_size = cbk<fn::compare_size, 2>;

    // size_of の 結果による比較メタ関数の導出
    using comparing_size = type_comparing<compare_size>;
}

#endif
