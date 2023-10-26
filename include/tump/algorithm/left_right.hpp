#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP 10

#include TUMP_COMMON_INCLUDE(algorithm/len.hpp) // 9
#include TUMP_COMMON_INCLUDE(algorithm/exists.hpp) // 9

namespace tump
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

    template <class L, class R>
    struct fn::mp_invoke_result<left, L, R> : public constraint_or_types<L, R> {};

    template <class L, class R>
    struct fn::mp_invoke_result<right, L, R> : public constraint_or_types<L, R> {};
}

#endif
