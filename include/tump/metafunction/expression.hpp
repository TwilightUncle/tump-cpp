#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_EXPRESSION_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_EXPRESSION_HPP

#include <utility>
#include TUMP_COMMON_INCLUDE(metafunction/operator.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/reverse.hpp)

// TODO: invoke_result の特殊化を定義すること

namespace tump
{
    namespace fn
    {
        // 詳細処理
        template <e_op_priority Priority, TypeList Result, class T>
        struct exp_2;
    
        // 特に処理を行わず、次の要素へ進めるだけ
        template <e_op_priority Priority, TypeList Result, class T>
        requires (
            is_empty_v<Result> && !is_operator_v<T> ||
            !is_empty_v<Result> && is_operator_v<T> && !eq_op_priority_v<T, Priority> ||
            !is_empty_v<Result> && !is_operator_v<T> && is_operator_v<get_front_t<Result>>
        )
        struct exp_2<Priority, Result, T> : fn::push_front<Result, T> {};

        // 関数適用
        template <e_op_priority Priority, TypeList Result, class T>
        requires (!is_empty_v<Result> && !is_operator_v<T> && Invocable<get_front_t<Result>>)
        struct exp_2<Priority, Result, T> : fn::push_front<
            pop_front_t<Result>,
            apply_t<get_front_t<Result>, T>
        > {};

        // 右結合以外の場合の演算子の関数化
        template <e_op_priority Priority, TypeList Result, class T>
        requires (!is_empty_v<Result> && is_operator_v<T> && eq_op_priority_v<T, Priority> && !is_infixr_v<vwrap<Priority>>)
        struct exp_2<Priority, Result, T> : fn::push_front<
            pop_front_t<Result>,
            ::tump::sec<get_front_t<Result>, T>
        > {};

        // 右結合の場合の演算子の関数化
        template <e_op_priority Priority, TypeList Result, class T>
        requires (!is_empty_v<Result> && is_operator_v<T> && eq_op_priority_v<T, Priority> && is_infixr_v<vwrap<Priority>>)
        struct exp_2<Priority, Result, T> : fn::push_front<
            pop_front_t<Result>,
            ::tump::sec<T, get_front_t<Result>>
        > {};

        // fold用
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
        template <e_op_priority Priority>
        using exp_n = compose_t<
            std::conditional_t<
                is_infixr_v<vwrap<Priority>>,
                ::tump::type_identity,
                ::tump::reverse
            >,
            ::tump::get_front,
            partial_apply<
                std::conditional_t<
                    is_infixr_v<vwrap<Priority>>,
                    ::tump::foldr,
                    ::tump::foldl
                >,
                cbk<exp_n_impl, 2>,
                list<list<>, vwrap<Priority>>
            >
        >;

        // 式の実装
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

        /**
         * 関数型言語っぽい式
        */
        template <class Head, class... Types>
        struct exp : public exp_impl<
            list<Head, Types...>,
            std::make_index_sequence<static_cast<std::size_t>(e_op_priority::_9)>,
            e_op_priority::func
        > {};

        /**
         * 式か判定
        */
        template <class T>
        struct is_exp : public std::false_type {};

        template <class Head, class... Types>
        struct is_exp<exp<Head, Types...>> : public std::true_type {};

        /**
         * 再帰的に式を評価する
        */
        template <TypeList Expression>
        requires (is_exp<Expression>::value)
        struct eval_impl : public map_if_t<
            cbk<is_exp, 1>,
            cbk<eval_impl, 1>,
            Expression
        > {};
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

    /**
     * 関数型言語っぽい式
    */
    template <class Head, class... Types>
    using exp = fn::exp<Head, Types...>;

    /**
     * 再帰的に式を評価する
    */
    template <class Head, class... Types>
    using eval = typename fn::eval_impl<exp<Head, Types...>>::type;
}

#endif
