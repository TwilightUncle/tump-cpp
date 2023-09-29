#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP

#include <tump/algorithm/has_type_parameters.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * リストの中身を指定の要素に置き換える
        */
        template <TypeList List, class... Types>
        struct make_type_list : public unnorm_li<List, list<Types...>> {};

        template <template <class...> class Outer, class... Types>
        struct make_type_list<empty<Outer>, Types...> : public std::type_identity<Outer<Types...>> {};
    }

    /**
     * リストの中身を指定の要素に置き換える
    */
    using make_type_list = cbk<fn::make_type_list>;

    template <TypeList List, class... Types>
    using make_type_list_t = typename fn::make_type_list<List, Types...>::type;

    template <TypeList List, class... Types>
    struct mp_invoke_result<make_type_list, List, Types...> : public constraint_st_type_list<List> {};
}

#endif
