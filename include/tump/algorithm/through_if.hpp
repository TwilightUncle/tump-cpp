#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_THROUGH_IF_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_THROUGH_IF_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 条件に合致する型をそのまま、返し、条件に合致しない場合はデフォルトの型を返す
        */
        template <InvocableArgN<1> Pred, class T, class Default>
        struct through_if : public std::conditional<invoke_v<Pred, T>, T, Default> {};

        /**
         * 条件に合致する型の場合はブロックし、デフォルトの値を返却
        */
        template <InvocableArgN<1> Pred, class T, class Default>
        struct block_if : public std::conditional<invoke_v<Pred, T>, Default, T> {};
    }

    /**
     * 条件に合致する型をそのまま、返し、条件に合致しない場合はデフォルトの型を返す
    */
    using through_if = cbk<fn::through_if, 3>;

    /**
     * 条件に合致する型をそのまま、返し、条件に合致しない場合はデフォルトの型を返す
    */
    template <InvocableArgN<1> Pred, class T, class Default>
    using through_if_t = typename fn::through_if<Pred, T, Default>::type;

    /**
     * 条件に合致する型の場合はブロックし、デフォルトの値を返却
    */
    using block_if = cbk<fn::block_if, 3>;

    /**
     * 条件に合致する型の場合はブロックし、デフォルトの値を返却
    */
    template <InvocableArgN<1> Pred, class T, class Default>
    using block_if_t = typename fn::block_if<Pred, T, Default>::type;
}

#endif
