#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_EXPRESSION_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_EXPRESSION_HPP

#include <tump/metafunction/operator.hpp>
#include <tump/algorithm/pop.hpp>
#include <tump/algorithm/reverse.hpp>

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
        template <e_op_priority Priority, TypeList List>
        using exp_n = invoke_t<
            compose_t<
                std::conditional_t<
                    is_infixr_v<vwrap<Priority>>,
                    ::tump::type_identity,
                    ::tump::reverse
                >,
                ::tump::get_front
            >,
            apply_t<
                std::conditional_t<
                    is_infixr_v<vwrap<Priority>>,
                    ::tump::foldr,
                    ::tump::foldl
                >,
                cbk<exp_n_impl, 2>,
                list<list<>, vwrap<Priority>>,
                List
            >
        >;

        // 式の実装
        template <e_op_priority Priority, TypeList List>
        struct exp_impl : exp_impl<decrement_op_priority(Priority), exp_n<Priority, List>> {};

        template <TypeList List>
        struct exp_impl<e_op_priority::r_0, List> : get_front<exp_n<e_op_priority::r_0, List>> {};

        /**
         * 関数型言語っぽい式
        */
        template <class Head, class... Types>
        using exp = exp_impl<e_op_priority::func, list<Head, Types...>>;
    }

    /**
     * 関数型言語っぽい式
    */
    template <class Head, class... Types>
    using exp = typename fn::exp<Head, Types...>::type;

}

#endif
