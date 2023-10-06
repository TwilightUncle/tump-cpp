#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP

#include <tump/algorithm/len.hpp>
#include <tump/algorithm/exists.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 二つの型を受け取り、左側の型のみ返却
        */
        template <class... Types>
        struct left;

        template <class L, class R>
        struct left<L, R> : public std::type_identity<L> {};

        template <TypeList List>
        requires (len_v<List> == 2)
        struct left<List> : public left<to_norm_li_t<List>> {};

        template <class L, class R>
        struct left<list<L, R>> : public left<L, R> {};

        /**
         * 二つの型を受け取り、右側の型のみ返却
        */
        template <class... Types>
        struct right;

        template <class L, class R>
        struct right<L, R> : public std::type_identity<R> {};

        template <TypeList List>
        requires (len_v<List> == 2)
        struct right<List> : public right<to_norm_li_t<List>> {};

        template <class L, class R>
        struct right<list<L, R>> : public right<L, R> {};
    }

    /**
     * 二つの型を受け取り、左側の型のみ返却
    */
    using left = cbk<fn::left>;

    /**
     * 二つの型を受け取り、左側の型のみ返却
    */
    template <class... Types>
    using left_t = typename fn::left<Types...>::type;

    /**
     * 二つの型を受け取り、右側の型のみ返却
    */
    using right = cbk<fn::right>;

    /**
     * 二つの型を受け取り、右側の型のみ返却
    */
    template <class... Types>
    using right_t = typename fn::right<Types...>::type;

    template <class L, class R>
    struct fn::mp_invoke_result<left, L, R> : public constraint_or_types<L, R> {};

    template <TypeList List>
    requires (len_v<List> == 2)
    struct fn::mp_invoke_result<left, List> : public std::type_identity<
        partial_apply<::tump::flip, ::tump::exists, List>
    > {};

    template <class L, class R>
    struct fn::mp_invoke_result<right, L, R> : public constraint_or_types<L, R> {};

    template <TypeList List>
    requires (len_v<List> == 2)
    struct fn::mp_invoke_result<right, List> : public std::type_identity<
        partial_apply<::tump::flip, ::tump::exists, List>
    > {};
}

#endif
