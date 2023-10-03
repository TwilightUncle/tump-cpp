#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REPLACE_IF_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_REPLACE_IF_HPP

#include <tump/algorithm/map.hpp>
#include <tump/algorithm/left_right.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * 条件に一意する要素を NewType に置き換える
        */
        template <InvocableArgN<1> Pred, class NewType, TypeList List>
        using replace_if = fn::map_if<Pred, bind<::tump::left, NewType>, List>;

        /**
         * リストに存在する OldType をすべて NewType に置き換える
        */
        template <class OldType, class NewType, TypeList List>
        using replace = replace_if<bind<::tump::is_same, OldType>, NewType, List>;
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
