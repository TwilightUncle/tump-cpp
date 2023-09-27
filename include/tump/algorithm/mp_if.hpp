#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MP_IF_HPP

#include <tump/algorithm/exists.hpp>

namespace tump
{
    /**
     * conditional の第一引数が型バージョン
     * (valueメンバ定数がboolへ変換可能であること)
    */
    template <VFunctional Cond, class T, class F>
    requires std::convertible_to<decltype(Cond::value), bool>
    using mp_if = std::conditional<Cond::value, T, F>;

    /**
     * conditional の第一引数が型バージョン
     * (valueメンバ定数がboolへ変換可能であること)
    */
    template <VFunctional Cond, class T, class F>
    using mp_if_t = mp_if<Cond, T, F>::type;

    template <unsigned int ArgsSize, VFunctional Cond, class T, class F>
    struct invoke_result<callback<mp_if, ArgsSize>, Cond, T, F> : public std::type_identity<
        bind<cbk<flip, 3>, cbk<exists, 2>, list<T, F>>
    > {};
}

#endif
