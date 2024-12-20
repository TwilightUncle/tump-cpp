#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/has_type_parameters.hpp)

namespace tump_0_1_2
{
    namespace fn
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
         * 右畳み込みを実施
        */
        template <InvocableArgN<2> F, class Init, TypeList List>
        struct foldr : public foldr<F, Init, to_norm_li_t<List>> {};

        template <InvocableArgN<2> F, class Init, class Head, class... Types>
        struct foldr<F, Init, list<Head, Types...>> : public invoke<F, Head, typename foldr<F, Init, list<Types...>>::type> {};

        template <InvocableArgN<2> F, class Init, TypeList List>
        requires (is_empty_v<List>)
        struct foldr<F, Init, List> : public std::type_identity<Init> {};
    }

    /**
     * 左畳み込みを実施
    */
    using foldl = cbk<fn::foldl, 3>;

    /**
     * 左畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldl_t = typename fn::foldl<F, Init, List>::type;

    /**
     * 右畳み込みを実施
    */
    using foldr = cbk<fn::foldr, 3>;

    /**
     * 右畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldr_t = typename fn::foldr<F, Init, List>::type;
}

#endif
