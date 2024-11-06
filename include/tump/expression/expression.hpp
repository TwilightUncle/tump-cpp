#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_EXPRESSION_EXPRESSION_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_EXPRESSION_EXPRESSION_HPP

#include <utility>
#include TUMP_COMMON_INCLUDE(expression/operator.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/reverse.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/unique.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/sort.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        namespace impl
        {
            // 隣り合った 2 つの型における詳細処理
            // デフォルトは特に処理を行わず、評価対象を次の要素へ進めるだけ
            template <class Priority, TypeList Result, class T>
            struct exp_2 : fn::push_front<Result, T> {};

            // 関数と、演算子を除く型が隣り合った場合
            // 関数適用を行う
            template <class Priority, TypeList Result, class T>
            requires (!is_empty_v<Result> && !is_operator_v<T> && Invocable<get_front_t<Result>>)
            struct exp_2<Priority, Result, T> : fn::push_front<
                pop_front_t<Result>,
                apply_t<get_front_t<Result>, T>
            > {};

            // 演算子と演算子以外の型が隣り合った場合
            // 演算時の部分適用により、演算子を関数に変換する
            template <class Priority, TypeList Result, TumpOperator T>
            requires (!is_empty_v<Result> && comparing_op_priority::eq_v<T, Priority>)
            struct exp_2<Priority, Result, T> : fn::push_front<
                pop_front_t<Result>,
                std::conditional_t<
                    is_infixr_v<Priority>,
                    ::tump_1_0_0::sec<T, get_front_t<Result>>,
                    ::tump_1_0_0::sec<get_front_t<Result>, T>
                >
            > {};

            // foldl と foldr の違いを吸収
            // 役割は exp_2 と exp_n の橋渡しのみ
            template <class Acc, class Cur>
            struct exp_n_impl;

            // foldl用
            template <e_op_priority Priority, TypeList List, class Cur>
            struct exp_n_impl<list<List, vwrap<Priority>>, Cur> : public std::type_identity<list<
                typename exp_2<vwrap<Priority>, List, Cur>::type,
                vwrap<Priority>
            >> {};

            // foldr用
            template <e_op_priority Priority, TypeList List, class Cur>
            struct exp_n_impl<Cur, list<List, vwrap<Priority>>> : public exp_n_impl<list<List, vwrap<Priority>>, Cur> {};

            // 優先度毎の式の実装
            // 演算子の結合性による処理の方向切り替えもここで行う
            template <class Priority>
            using exp_n = std::conditional_t<
                is_infixr_v<Priority>,
                compose_t<
                    ::tump_1_0_0::get_front,
                    partial_apply<
                        ::tump_1_0_0::foldr,
                        cbk<exp_n_impl, 2>,
                        list<list<>, Priority>
                    >
                >,
                compose_t<
                    ::tump_1_0_0::reverse,
                    ::tump_1_0_0::get_front,
                    partial_apply<
                        ::tump_1_0_0::foldl,
                        cbk<exp_n_impl, 2>,
                        list<list<>, Priority>
                    >
                >
            >;

            // 式の実装
            // 全ての演算子優先度における式の評価を合成する
            // Seq は全ての優先度を符号なし整数として列挙していること
            template <TypeList List, class Priorities, e_op_priority FirstPriority>
            struct exp_impl;

            template <TypeList List, class... Priorities, e_op_priority FirstPriority>
            struct exp_impl<List, list<Priorities...>, FirstPriority> : public invoke<
                typename compose<
                    ::tump_1_0_0::get_front,
                    exp_n<Priorities>...,
                    exp_n<vwrap<FirstPriority>>
                >::type,
                List
            > {};

            // 式から優先度順で整列済みの演算子優先度を抽出
            template <TypeList List>
            struct extract_sorted_op_priority : public invoke<
                compose_t<
                    partial_apply<
                        ::tump_1_0_0::flip,
                        ::tump_1_0_0::sort,
                        comparing_op_priority
                    >,
                    ::tump_1_0_0::unique,
                    tump::partial_apply<::tump_1_0_0::map, cbk<get_op_priority, 1>>,
                    tump::partial_apply<::tump_1_0_0::filter, cbk<is_operator, 1>>
                >,
                List
            > {};
        }

        /**
         * 式か判定
        */
        template <class T>
        struct is_exp : public std::false_type {};

        /**
         * 再帰的に式を評価する
        */
        template <class T>
        struct eval_exp : public std::conditional_t<
            is_exp<T>::value,
            T,
            std::type_identity<T>
        > {};

        template <class T>
        using eval_exp_t = typename eval_exp<T>::type;

        /**
         * 関数型言語っぽい式
        */
        template <class Head, class... Types>
        struct exp : public impl::exp_impl<
            list<eval_exp_t<Head>, eval_exp_t<Types>...>,
            typename impl::extract_sorted_op_priority<
                list<eval_exp_t<Head>, eval_exp_t<Types>...>
            >::type,
            e_op_priority::func
        > {};

        template <class Head, class... Types>
        struct is_exp<exp<Head, Types...>> : public std::true_type {};
    }

    /**
     * 式か判定
    */
    using is_exp = cbk<fn::is_exp, 1>;

    /**
     * 式か判定
    */
    template <class T>
    constexpr auto is_exp_v = fn::is_exp<T>::value;

    template <class T>
    concept TumpExpression = is_exp_v<T>;

    template <class T>
    concept MpCondition = VFunctional<T> || TumpExpression<T>;

    /**
     * 関数型言語っぽい式
    */
    template <class Head, class... Types>
    using exp = fn::exp<Head, Types...>;

    /**
     * 式を評価する
    */
    template <class Head, class... Types>
    using eval = typename exp<Head, Types...>::type;
}

#endif
