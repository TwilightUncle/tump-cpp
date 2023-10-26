#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GUARD_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_GUARD_HPP 16

#include TUMP_COMMON_INCLUDE(algorithm/find_if.hpp) // 15
#include TUMP_COMMON_INCLUDE(metafunction/expression.hpp) // 11

namespace tump
{
    template <class T>
    concept GuardCondition = VFunctional<T> || TumpExpression<T>;

    /**
     * ガードにおける条件分岐節
    */
    template <GuardCondition Cond, class Expression>
    struct if_clause {};

    /**
     * 全ての条件に合致しなかった場合に走る式を書く
    */
    template <class Expression>
    using otherwise = if_clause<std::true_type, Expression>;

    namespace fn
    {
        template <class T>
        struct is_guard_clause : public std::false_type {};

        template <GuardCondition Cond, class Expression>
        struct is_guard_clause<if_clause<Cond, Expression>> : public std::true_type {};
    }

    template <class T>
    constexpr auto is_guard_clause_v = fn::is_guard_clause<T>::value;
    
    template <class T>
    concept GuardClause = is_guard_clause_v<T>;

    namespace fn
    {
        /**
         * if-else みたいなのを再現した関数
        */
        template <GuardClause... Clauses>
        struct guard : public invoke<
            compose_t<
                cbk<eval_exp, 1>,
                ::tump::get_back,
                partial_apply<
                    ::tump::flip,
                    ::tump::find_if,
                    list<Clauses...>
                >
            >,
            compose_t<
                partial_apply<
                    ::tump::is_base_of,
                    std::true_type
                >,
                cbk<eval_exp, 1>,
                ::tump::get_front
            >
        > {};
    }

    /**
     * if-else みたいなのを再現した関数
    */
    template <std::size_t ArgsSize = 2>
    using guard = cbk<fn::guard, ArgsSize>;

    /**
     * if-else みたいなのを再現した関数
    */
    template <GuardClause... Clauses>
    using guard_t = typename fn::guard<Clauses...>::type;
}

#endif
