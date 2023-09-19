#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_RELAY_HPP

#include <tump/algorithm/fold.hpp>
#include <tump/algorithm/copy.hpp>
#include <tump/algorithm/map.hpp>

namespace tump
{
    template <class T>
    struct is_invocable_list : public std::false_type {};

    template <TypeList List>
    struct is_invocable_list<List> : public apply_list<
        cbk<std::conjunction>,
        map_t<cbk<is_callback, 1>, List>
    > {};

    template <class T>
    constexpr auto is_invocable_list_v = is_invocable_list<T>::value;

    template <class T>
    concept InvocableList = is_invocable_list_v<T>;
}

#endif
