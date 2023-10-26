#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REPLACE_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REPLACE_IF_HPP 12

#include TUMP_COMMON_INCLUDE(algorithm/map.hpp) // 11
#include TUMP_COMMON_INCLUDE(algorithm/left_right.hpp) // 10

namespace tump
{
    namespace fn
    {
        /**
         * 条件に一意する要素を NewType に置き換える
        */
        template <InvocableArgN<1> Pred, class NewType, TypeList List>
        using replace_if = fn::map_if<Pred, partial_apply<::tump::left, NewType>, List>;

        /**
         * リストに存在する OldType をすべて NewType に置き換える
        */
        template <class OldType, class NewType, TypeList List>
        using replace = replace_if<partial_apply<::tump::is_same, OldType>, NewType, List>;
    }

    /**
     * 条件に一意する要素を NewType に置き換える
    */
    using replace_if = cbk<fn::replace_if, 3>;

    /**
     * 条件に一意する要素を NewType に置き換える
    */
    template <InvocableArgN<1> Pred, class NewType, TypeList List>
    using replace_if_t = typename fn::replace_if<Pred, NewType, List>::type;

    /**
     * リストに存在する OldType をすべて NewType に置き換える
    */
    using replace = cbk<fn::replace, 3>;

    /**
     * リストに存在する OldType をすべて NewType に置き換える
    */
    template <class OldType, class NewType, TypeList List>
    using replace_t = typename fn::replace<OldType, NewType, List>::type;

    template <InvocableArgN<1> Pred, class NewType, TypeList List>
    struct fn::mp_invoke_result<replace_if, Pred, NewType, List> : public constraint_st_type_list<List> {};

    template <class OldType, class NewType, TypeList List>
    struct fn::mp_invoke_result<replace, OldType, NewType, List> : public constraint_st_type_list<List> {};
}

#endif
