#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP

#include TUMP_COMMON_INCLUDE(algorithm/len.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/exists.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        /**
         * 二つの型を受け取り、左側の型のみ返却
        */
        template <class L, class R>
        struct left : public std::type_identity<L> {};

        /**
         * 二つの型を受け取り、右側の型のみ返却
        */
        template <class L, class R>
        struct right : public std::type_identity<R> {};
    }

    /**
     * 二つの型を受け取り、左側の型のみ返却
    */
    using left = cbk<fn::left, 2>;

    /**
     * 二つの型を受け取り、左側の型のみ返却
    */
    template <class L, class R>
    using left_t = typename fn::left<L, R>::type;

    /**
     * 二つの型を受け取り、右側の型のみ返却
    */
    using right = cbk<fn::right, 2>;

    /**
     * 二つの型を受け取り、右側の型のみ返却
    */
    template <class L, class R>
    using right_t = typename fn::right<L, R>::type;
}

#endif
