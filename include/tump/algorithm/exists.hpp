#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP

#include <tump/algorithm/has_type_parameters.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 任意の型が、型リストの中に存在するか判定
        */
        template <class Search, TypeList List>
        struct exists : public exists<Search, to_norm_li_t<List>>::type {};

        template <class Search, TypeList List>
        requires (is_empty_v<List>)
        struct exists<Search, List> : public std::false_type {};

        template <class Search, class... Types>
        struct exists<Search, list<Types...>> : public std::disjunction<
            std::is_same<Search, Types>...
        >::type {};
    }

    /**
     * 任意の型が、型リストの中に存在するか判定
    */
    using exists = cbk<fn::exists, 2>;

    /**
     * 任意の型が、型リストの中に存在するか判定
    */
    template <class Search, TypeList List>
    constexpr auto exists_v = fn::exists<Search, List>::value;

    template <class... Types>
    using constraint_or_types = std::type_identity<
        bind<cbk<flip, 3>, exists, list<Types...>>
    >;

    template <class Search, TypeList List>
    struct fn::mp_invoke_result<exists, Search, List> : public constraint_bool_constant {}; 
}

#endif
