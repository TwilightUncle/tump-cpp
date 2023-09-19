#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include <tump/metafunction/flip.hpp>
#include <tump/metafunction/apply_list.hpp>
#include <tump/algorithm/map.hpp>
#include <tump/algorithm/fold.hpp>

namespace tump
{
    template <class T, class OptionalArgs = optional_args_for_is_callback<0>>
    struct is_invocable_list : public std::false_type {};

    template <TypeList List, class OptionalArgs>
    struct is_invocable_list<List, OptionalArgs> : public apply_list<
        cbk<std::conjunction>,
        map_t<
            bind<
                cbk<flip, 3>,
                cbk<is_callback, 2>,
                OptionalArgs
            >,
            List
        >
    > {};

    template <class T, class OptionalArgs = optional_args_for_is_callback<0>>
    constexpr auto is_invocable_list_v = is_invocable_list<T, OptionalArgs>::value;

    /**
     * 型リストの要素がすべてInvocableの制約を満たしている
    */
    template <class T>
    concept InvocableList = is_invocable_list_v<T>;

    /**
     * 型リストの要素がすべてInvocableArgNの制約を満たしている
    */
    template <class T, unsigned int ArgsSize>
    concept InvocableArgNList = is_invocable_list_v<T, optional_args_for_is_callback<ArgsSize, true>>;

    /**
     * @fn
     * @brief T に対してFListで渡したメタ関数リストの関数を順番に適用していく
    */
    template <class T, InvocableArgNList<1> FList>
    struct relay : public foldl<
        bind<
            cbk<flip, 3>,
            cbk<apply, 2>
        >,
        T,
        FList
    > {};

    /**
     * @fn
     * @brief T に対してFListで渡したメタ関数リストの関数を順番に適用していく
    */
    template <class T, InvocableArgNList<1> FList>
    using relay_t = relay<T, FList>::type;
}

#endif
