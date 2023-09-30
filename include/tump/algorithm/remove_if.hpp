#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REMOVE_IF_HPP

#include <tump/algorithm/filter.hpp>
#include <tump/metafunction/compose.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 指定条件に合致する要素のみ抽出する
        */
        template <InvocableArgN<1> F, TypeList List>
        using remove_if = filter<
            compose_t<tump::negation, F>,
            List
        >;
    }

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    using remove_if = cbk<fn::remove_if, 2>;

    /**
     * 指定条件に合致する要素のみ抽出する
    */
    template <InvocableArgN<1> F, TypeList List>
    using remove_if_t = typename fn::remove_if<F, List>::type;

    // TODO: Fによってリストの制約を変えるべきか考える
    template <InvocableArgN<1> F, TypeList List>
    struct fn::mp_invoke_result<remove_if, F, List> : public constraint_st_type_list<List> {};
}

#endif
