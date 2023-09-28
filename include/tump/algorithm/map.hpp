#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_MAP_HPP

#include <tump/algorithm/get.hpp>
#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    template <InvocableArgN<1> F, TypeList List>
    struct map : public unnorm_li<
        make_empty_t<List, invoke_result_t<F, get_front_t<List>>>,
        typename map<F, to_norm_li_t<List>>::type
    > {};
    
    template <InvocableArgN<1> F, TypeList List>
    requires (is_empty_v<List>)
    struct map<F, List> : public std::type_identity<List> {};

    template <InvocableArgN<1> F, class... Types>
    struct map<F, list<Types...>> : public std::type_identity<list<invoke_t<F, Types>...>> {};

    /**
     * 型リストに含まれるすべての要素に対して、メタ関数を適用する
    */
    template <InvocableArgN<1> F, TypeList List>
    using map_t = typename map<F, List>::type;

    namespace _ {
        template <class F, class List, class Target>
        struct map_result_impl : public std::false_type {};

        template <InvocableArgN<1> F, TypeList List, TypeList Target>
        requires (!is_empty_v<List>)
        struct map_result_impl<F, List, Target> : public std::is_same<
            make_empty_t<List, invoke_result_t<F, get_front_t<List>>>,
            make_empty_t<Target>
        > {}; 

        template <InvocableArgN<1> F, TypeList List, TypeList Target>
        requires (is_empty_v<List>)
        struct map_result_impl<F, List, Target> : public std::is_same<
            make_empty_t<List>,
            make_empty_t<Target>
        > {};
    }

    template <unsigned int ArgsSize, InvocableArgN<1> F, TypeList List>
    struct invoke_result<callback<map, ArgsSize>, F, List> : public std::type_identity<
        bind<cbk<_::map_result_impl, 3>, F, List>
    > {};
}

#endif
