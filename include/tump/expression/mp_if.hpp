#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_EXPRESSION_MP_IF_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_EXPRESSION_MP_IF_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(expression/expression.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * conditional の第一引数が型バージョン
         * (valueメンバ定数がboolへ変換可能であること)
        */
        template <MpCondition Cond, class... Types>
        struct mp_if;

        template <MpCondition Cond, class T, class F>
        requires std::convertible_to<decltype(eval_exp_t<Cond>::value), bool>
        struct mp_if<Cond, T, F> : public std::conditional<
            eval_exp_t<Cond>::value,
            eval_exp_t<T>,
            eval_exp_t<F>
        > {};

        /**
         * 二つの要素のリストを受け取るバージョン
        */
        template <MpCondition Cond, TypeList List>
        requires (len_v<List> == 2)
        struct mp_if<Cond, List> : public mp_if<Cond, to_norm_li_t<List>> {};

        template <MpCondition Cond, class T, class F>
        struct mp_if<Cond, list<T, F>> : public mp_if<Cond, T, F> {};
    }

    using mp_if = cbk<fn::mp_if, 3>;
    using mp_if_li = cbk<fn::mp_if, 2>;

    /**
     * conditional の第一引数が型バージョン
     * (valueメンバ定数がboolへ変換可能であること)
    */
    template <MpCondition Cond, class... Types>
    using mp_if_t = typename fn::mp_if<Cond, Types...>::type;
}

#endif
