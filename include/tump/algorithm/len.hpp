#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEN_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_LEN_HPP

#include <tump/algorithm/has_type_parameters.hpp>

namespace tump
{
    /**
     * リストの長さを取得
    */
    template <TypeList List>
    struct len : public len<to_norm_li_t<List>> {};

    template <class... Types>
    struct len<list<Types...>>
        : public std::integral_constant<std::size_t, sizeof...(Types)>
    {};

    template <TypeList List>
    requires (is_empty_v<List>)
    struct len<List>
        : public std::integral_constant<std::size_t, 0>
    {};

    template <TypeList List>
    constexpr auto len_v = len<List>::value;

    template <unsigned int ArgsSize, class T>
    struct mp_invoke_result<callback<len, ArgsSize>, T> : public constraint_size_constant {};
}

#endif
