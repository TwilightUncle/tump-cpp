#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP

#include <tump/algorithm/filter.hpp>
#include <tump/metafunction/compose.hpp>

namespace tump
{
    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using remove_if = filter<
        compose<
            cbk<std::negation, 1>,
            F
        >,
        List
    >;

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using remove_if_t = remove_if<F, List>::type;

    // TODO: Fによってリストの制約を変えるべきか考える
    template <std::size_t ArgsSize, InvocableArgN<1> F, TypeList List>
    struct invoke_result<callback<remove_if, ArgsSize>, F, List> : public constraint_st_type_list<List> {};
}

#endif
