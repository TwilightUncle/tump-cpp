#ifndef TUMP_INCLUDE_GUARD_TUMP_EXPRESSION_EXPRESSION_HPP
#define TUMP_INCLUDE_GUARD_TUMP_EXPRESSION_EXPRESSION_HPP

#include <utility>
#include TUMP_COMMON_INCLUDE(expression/operator.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/reverse.hpp)

// TODO: invoke_result の特殊化を定義すること

namespace tump
{
    namespace fn
    {
        namespace impl
        {
            // 隣り合った 2 つの型における詳細処理
            // デフォルトは特に処理を行わず、評価対象を次の要素へ進めるだけ
            template <e_op_priority Priority, TypeList Result, class T>
            struct exp_2 : fn::push_front<Result, T> {};

            // 関数と、演算子を除く型が隣り合った場合
            // 関数適用を行う
            template <e_op_priority Priority, TypeList Result, class T>
            requires (!is_empty_v<Result> && !is_operator_v<T> && Invocable<get_front_t<Result>>)
            struct exp_2<Priority, Result, T> : fn::push_front<
                pop_front_t<Result>,
                apply_t<get_front_t<Result>, T>
            > {};

            // 演算子と演算子以外の型が隣り合った場合
            // 演算時の部分適用により、演算子を関数に変換する
            template <e_op_priority Priority, TypeList Result, class T>
            requires (!is_empty_v<Result> && is_operator_v<T> && eq_op_priority_v<T, Priority>)
            struct exp_2<Priority, Result, T> : fn::push_front<
                pop_front_t<Result>,
                std::conditional_t<
                    is_infixr_v<vwrap<Priority>>,
                    ::tump::sec<T, get_front_t<Result>>,
                    ::tump::sec<get_front_t<Result>, T>
                >
            > {};

            // foldl と foldr の違いを吸収
            // 役割は exp_2 と exp_n の橋渡しのみ
            template <class Acc, class Cur>
            struct exp_n_impl;

            // foldl用
            template <e_op_priority Priority, TypeList List, class Cur>
            struct exp_n_impl<list<List, vwrap<Priority>>, Cur> : public std::type_identity<list<
                typename exp_2<Priority, List, Cur>::type,
                vwrap<Priority>
            >> {};

            // foldr用
            template <e_op_priority Priority, TypeList List, class Cur>
            struct exp_n_impl<Cur, list<List, vwrap<Priority>>> : public exp_n_impl<list<List, vwrap<Priority>>, Cur> {};

            // 優先度毎の式の実装
            // 演算子の結合性による処理の方向切り替えもここで行う
            template <e_op_priority Priority>
            using exp_n = std::conditional_t<
                is_infixr_v<vwrap<Priority>>,
                compose_t<
                    ::tump::get_front,
                    partial_apply<
                        ::tump::foldr,
                        cbk<exp_n_impl, 2>,
                        list<list<>, vwrap<Priority>>
                    >
                >,
                compose_t<
                    ::tump::reverse,
                    ::tump::get_front,
                    partial_apply<
                        ::tump::foldl,
                        cbk<exp_n_impl, 2>,
                        list<list<>, vwrap<Priority>>
                    >
                >
            >;

            // 式の実装
            // 全ての演算子優先度における式の評価を合成する
            // Seq は全ての優先度を符号なし整数として列挙していること
            template <TypeList List, class Seq, e_op_priority FirstPriority>
            struct exp_impl;

            template <TypeList List, std::size_t... Priorities, e_op_priority FirstPriority>
            struct exp_impl<List, std::index_sequence<Priorities...>, FirstPriority> : public invoke<
                typename compose<
                    ::tump::get_front,
                    exp_n<static_cast<e_op_priority>(Priorities)>...,
                    exp_n<FirstPriority>
                >::type,
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
            std::make_index_sequence<static_cast<std::size_t>(e_op_priority::_9) + 1>,
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
