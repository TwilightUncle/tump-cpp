#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_LEN_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_ALGORITHM_LEN_HPP

#include TUMP_V_1_0_0_COMMON_INCLUDE(algorithm/has_type_parameters.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        /**
         * リストの長さを取得
        */
        template <TypeListOrValueList List>
        struct len : public len<to_norm_li_t<List>>::type {};

        template <class... Types>
        struct len<list<Types...>>
            : public std::integral_constant<std::size_t, sizeof...(Types)>
        {};

        template <TypeListOrValueList List>
        requires (is_empty_v<List>)
        struct len<List>
            : public std::integral_constant<std::size_t, 0>
        {};
    }

    /**
     * リストの長さを取得
    */
    using len = cbk<fn::len, 1>;

    /**
     * リストの長さを取得
    */
    template <TypeListOrValueList List>
    constexpr auto len_v = fn::len<List>::value;
}

#endif
