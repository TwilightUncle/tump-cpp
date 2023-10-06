#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_IF_HPP

#include <tump/algorithm/len.hpp>
#include <tump/algorithm/exists.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * conditional の第一引数が型バージョン
         * (valueメンバ定数がboolへ変換可能であること)
        */
        template <VFunctional Cond, class... Types>
        struct mp_if;

        template <VFunctional Cond, class T, class F>
        requires std::convertible_to<decltype(Cond::value), bool>
        struct mp_if<Cond, T, F> : public std::conditional<Cond::value, T, F> {};

        /**
         * 二つの要素のリストを受け取るバージョン
        */
        template <VFunctional Cond, TypeList List>
        requires (len_v<List> == 2)
        struct mp_if<Cond, List> : public mp_if<Cond, to_norm_li_t<List>> {};

        template <VFunctional Cond, class T, class F>
        struct mp_if<Cond, list<T, F>> : public mp_if<Cond, T, F> {};
    }

    using mp_if = cbk<fn::mp_if>;

    /**
     * conditional の第一引数が型バージョン
     * (valueメンバ定数がboolへ変換可能であること)
    */
    template <VFunctional Cond, class... Types>
    using mp_if_t = typename fn::mp_if<Cond, Types...>::type;

    template <VFunctional Cond, class T, class F>
    struct fn::mp_invoke_result<mp_if, Cond, T, F> : public constraint_or_types<T, F> {};

    template <VFunctional Cond, TypeList List>
    requires (len_v<List> == 2)
    struct fn::mp_invoke_result<mp_if, Cond, List> : public std::type_identity<
        partial_apply<::tump::flip, ::tump::exists, List>
    > {};
}

#endif
