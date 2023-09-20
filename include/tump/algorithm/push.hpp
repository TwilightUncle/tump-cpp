#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_PUSH_HPP

#include <tump/algorithm/make_type_list.hpp>
#include <tump/algorithm/concat.hpp>

namespace tump
{
    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_back = concat<List, make_type_list_t<List, Types...>>;

    /**
     * 型リストの最後尾に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_back_t = push_back<List, Types...>::type;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_front = concat<make_type_list_t<List, Types...>, List>;

    /**
     * 型リストの先頭に指定されたパラメータパックを挿入する
    */
    template <TypeList List, class... Types>
    using push_front_t = push_front<List, Types...>::type;
}

#endif
