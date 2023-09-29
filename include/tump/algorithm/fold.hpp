#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP

#include <tump/algorithm/get.hpp>
#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * 左畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    struct foldl : public foldl<F, Init, to_norm_li_t<List>> {};

    template <InvocableArgN<2> F, class Init, class Head, class... Types>
    struct foldl<F, Init, list<Head, Types...>> : public foldl<F, invoke_t<F, Init, Head>, list<Types...>> {};

    template <InvocableArgN<2> F, class Init, TypeList List>
    requires (is_empty_v<List>)
    struct foldl<F, Init, List> : public std::type_identity<Init> {};

    /**
     * 左畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldl_t = typename foldl<F, Init, List>::type;

    /**
     * 右畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    struct foldr : public foldr<F, Init, to_norm_li_t<List>> {};

    template <InvocableArgN<2> F, class Init, class Head, class... Types>
    struct foldr<F, Init, list<Head, Types...>> : public invoke<F, Head, typename foldr<F, Init, list<Types...>>::type> {};

    template <InvocableArgN<2> F, class Init, TypeList List>
    requires (is_empty_v<List>)
    struct foldr<F, Init, List> : public std::type_identity<Init> {};

    /**
     * 右畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldr_t = typename foldr<F, Init, List>::type;

    template <unsigned int ArgsSize, InvocableArgN<2> F, class Init, TypeList List>
    struct mp_invoke_result<callback<foldl, ArgsSize>, F, Init, List> : public mp_invoke_result<F, Init, get_front_t<List>> {};

    template <unsigned int ArgsSize, InvocableArgN<2> F, class Init, TypeList List>
    struct mp_invoke_result<callback<foldr, ArgsSize>, F, Init, List> : public mp_invoke_result<F, get_back_t<List>, Init> {};
}

#endif
