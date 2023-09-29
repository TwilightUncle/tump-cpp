#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP

#include <tump/algorithm/has_type_parameters.hpp>
#include <tump/metafunction/invoke_result.hpp>

namespace tump
{
    /**
     * 任意の型が、型リストの中に存在するか判定
    */
    template <class Search, TypeList List>
    struct exists : public exists<Search, to_norm_li_t<List>> {};

    template <class Search, TypeList List>
    requires (is_empty_v<List>)
    struct exists<Search, List> : public std::false_type {};

    template <class Search, class... Types>
    struct exists<Search, list<Types...>> : public std::disjunction<
        std::is_same<Search, Types>...
    > {};

    /**
     * 任意の型が、型リストの中に存在するか判定
    */
    template <class Search, TypeList List>
    constexpr auto exists_v = exists<Search, List>::value;

    template <class... Types>
    using constraint_or_types = std::type_identity<
        bind<cbk<flip, 3>, cbk<exists, 2>, list<Types...>>
    >;

    template <std::size_t ArgsSize, class Search, TypeList List>
    struct mp_invoke_result<callback<exists, ArgsSize>, Search, List> : public constraint_bool_constant {}; 
}

#endif
