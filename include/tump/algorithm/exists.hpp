#ifndef TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP
#define TUMP_V_0_1_0_INCLUDE_GUARD_TUMP_ALGORITHM_EXISTS_HPP

#include TUMP_V_0_1_0_COMMON_INCLUDE(algorithm/has_type_parameters.hpp)

namespace tump_0_1_0
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

        /**
         * 任意の型が、リストの中に存在していないか判定
        */
        template <class Search, TypeList List>
        using not_exists = typename std::negation<exists<Search, List>>::type;
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

    using not_exists = cbk<fn::not_exists, 2>;

    template <class Search, TypeList List>
    constexpr auto not_exists_v = fn::not_exists<Search, List>::value;
}

#endif
