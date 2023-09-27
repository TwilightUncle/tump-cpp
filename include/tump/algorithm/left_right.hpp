#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEFT_RIGHT_HPP

#include <tump/algorithm/len.hpp>
#include <tump/algorithm/exists.hpp>

namespace tump
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
     * 二つの型を受け取り、左側の型のみ返却
    */
    template <class... Types>
    using left_t = left<Types...>::type;

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

    /**
     * 二つの型を受け取り、右側の型のみ返却
    */
    template <class... Types>
    using right_t = right<Types...>::type;

    template <std::size_t ArgsSize, class L, class R>
    struct invoke_result<callback<left, ArgsSize>, L, R> : public constraint_or_types<L, R> {};

    template <unsigned int ArgsSize, TypeList List>
    struct invoke_result<callback<left, ArgsSize>, List> : public std::type_identity<
        bind<cbk<flip>, cbk<exists>, List>
    > {};

    template <std::size_t ArgsSize, class L, class R>
    struct invoke_result<callback<right, ArgsSize>, L, R> : public constraint_or_types<L, R> {};

    template <unsigned int ArgsSize, TypeList List>
    struct invoke_result<callback<right, ArgsSize>, List> : public std::type_identity<
        bind<cbk<flip>, cbk<exists>, List>
    > {};
}

#endif
