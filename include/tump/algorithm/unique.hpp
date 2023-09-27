#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP

#include <tump/algorithm/filter.hpp>
#include <tump/algorithm/mp_if.hpp>
#include <tump/metafunction/compose.hpp>

namespace tump
{
    namespace _
    {
        template <TypeList Acc, class Cur>
        using unique_impl = push_back_if<
            compose<
                cbk<std::negation, 1>,
                bind<cbk<flip, 3>, cbk<exists, 2>, Acc>
            >,
            Acc,
            Cur
        >;
    }

    /**
     * リストの重複を除去する
    */
    template <TypeList List>
    using unique = foldl<
        cbk<_::unique_impl, 2>,
        make_empty_t<List>,
        to_norm_li_t<List>
    >;

    /**
     * リストの重複を除去する
    */
    template <TypeList List>
    using unique_t = unique<List>::type;

    /**
     * リストの内容が一意であるか判定
    */
    template <TypeList List>
    using is_unique = std::is_same<to_norm_li_t<List>, unique_t<to_norm_li_t<List>>>;

    /**
     * リストの内容が一意であるか判定
    */
    template <TypeList List>
    constexpr auto is_unique_v = is_unique<List>::value;

    template <std::size_t ArgsSize, TypeList List>
    struct invoke_result<callback<unique, ArgsSize>, List> : public constraint_st_type_list<List> {};

    template <std::size_t ArgsSize, TypeList List>
    struct invoke_result<callback<is_unique, ArgsSize>, List> : public constraint_bool_constant {};
}

#endif
