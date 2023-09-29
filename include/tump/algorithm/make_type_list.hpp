#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAKE_TYPE_LIST_HPP

#include <tump/algorithm/has_type_parameters.hpp>

namespace tump
{
    /**
     * リストの中身を指定の要素に置き換える
    */
    template <TypeList List, class... Types>
    struct make_type_list : public unnorm_li<List, list<Types...>> {};

    template <template <class...> class Outer, class... Types>
    struct make_type_list<empty<Outer>, Types...> : public std::type_identity<Outer<Types...>> {};

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using make_type_list_t = typename make_type_list<List, Types...>::type;

    template <std::size_t ArgsSize, TypeList List, class... Types>
    requires (ArgsSize > 0)
    struct mp_invoke_result<callback<make_type_list, ArgsSize>, List, Types...> : public constraint_st_type_list<List> {};

    template <TypeList List, class... Types>
    struct mp_invoke_result<callback<make_type_list>, List, Types...> : public constraint_st_type_list<List> {};
}

#endif
