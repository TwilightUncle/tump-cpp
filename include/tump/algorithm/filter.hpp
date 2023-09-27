#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FILTER_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FILTER_HPP

#include <tump/algorithm/push.hpp>


namespace tump
{
    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using filter = invoke_list<
        bind<
            cbk<push_back_if>,
            F,
            make_empty_t<List>
        >,
        to_norm_li_t<List>
    >;

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using filter_t = filter<F, List>::type;

    // TODO: Fによってリストの制約を変えるべきか考える
    template <std::size_t ArgsSize, InvocableArgN<1> F, TypeList List>
    struct invoke_result<callback<filter, ArgsSize>, F, List> : public constraint_st_type_list<List> {};
}

#endif
