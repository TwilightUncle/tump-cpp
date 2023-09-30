#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_UNIQUE_HPP

#include <tump/algorithm/filter.hpp>
#include <tump/metafunction/compose.hpp>

namespace tump
{
    namespace fn
    {
        namespace _
        {
            template <TypeList Acc, class Cur>
            using unique_impl = push_back_if<
                compose_t<
                    negation,
                    bind<::tump::flip, ::tump::exists, Acc>
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
    }

    /**
     * リストの重複を除去する
    */
    using unique = cbk<fn::unique, 1>;

    /**
     * リストの重複を除去する
    */
    template <TypeList List>
    using unique_t = typename fn::unique<List>::type;

    namespace fn
    {
        /**
         * リストの内容が一意であるか判定
        */
        template <TypeList List>
        using is_unique = std::is_same<to_norm_li_t<List>, unique_t<to_norm_li_t<List>>>;
    }

    /**
     * リストの内容が一意であるか判定
    */
    using is_unique = cbk<fn::is_unique, 1>;

    /**
     * リストの内容が一意であるか判定
    */
    template <TypeList List>
    constexpr auto is_unique_v = fn::is_unique<List>::value;

    template <TypeList List>
    struct fn::mp_invoke_result<unique, List> : public constraint_st_type_list<List> {};

    template <TypeList List>
    struct fn::mp_invoke_result<is_unique, List> : public constraint_bool_constant {};
}

#endif
