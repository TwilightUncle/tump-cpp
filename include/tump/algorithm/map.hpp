#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP

#include <tump/algorithm/has_type_parameters.hpp>
#include <tump/metafunction/apply.hpp>

namespace tump {
    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    template <InvocableArg1 F, TypeList List>
    struct map;
    
    template <InvocableArg1 F, TypeList List>
    requires (is_empty_v<List>)
    struct map<F, List> : public std::type_identity<List> {};

    template <InvocableArg1 F, template <class...> class Outer, class... Types>
    struct map<F, Outer<Types...>> : public std::type_identity<Outer<apply_t<F, Types>...>> {};

    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    template <InvocableArg1 F, TypeList List>
    using map_t = map<F, List>::type;
}

#endif
