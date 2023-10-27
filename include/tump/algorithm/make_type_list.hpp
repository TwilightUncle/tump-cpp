#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP

#include TUMP_COMMON_INCLUDE(algorithm/has_type_parameters.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * リストの中身を指定の要素に置き換える
        */
        template <TypeList List, class... Types>
        struct make_type_list : public fn::unnorm_li<List, list<Types...>> {};

        template <template <class...> class Outer, class... Types>
        struct make_type_list<empty<Outer>, Types...> : public std::type_identity<Outer<Types...>> {};
    }

    /**
     * リストの中身を指定の要素に置き換える
    */
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using make_type_list = cbk<fn::make_type_list, ArgsSize>;

    /**
     * リストの中身を指定の要素に置き換える
    */
    template <TypeList List, class... Types>
    using make_type_list_t = typename fn::make_type_list<List, Types...>::type;
}

#endif
