#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_FOLD_HPP

#include <tump/algorithm/has_type_parameters.hpp>
#include <tump/metafunction/invoke.hpp>

namespace tump {
    /**
     * 左畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    struct foldl;

    template <InvocableArgN<2> F, class Init, template <class...> class Outer, class Head, class... Types>
    struct foldl<F, Init, Outer<Head, Types...>> : public foldl<F, invoke_t<F, Init, Head>, Outer<Types...>> {};

    template <InvocableArgN<2> F, class Init, template <class...> class Outer, class Head>
    struct foldl<F, Init, Outer<Head>> : public std::type_identity<invoke_t<F, Init, Head>> {};

    /**
     * 左畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldl_t = foldl<F, Init, List>::type;

    /**
     * 右畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    struct foldr;

    template <InvocableArgN<2> F, class Init, template <class...> class Outer, class Head, class... Types>
    struct foldr<F, Init, Outer<Head, Types...>> : public invoke<F, Head, typename foldr<F, Init, Outer<Types...>>::type> {};

    template <InvocableArgN<2> F, class Init, template <class...> class Outer, class Head>
    struct foldr<F, Init, Outer<Head>> : public std::type_identity<invoke_t<F, Head, Init>> {};

    /**
     * 右畳み込みを実施
    */
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldr_t = foldr<F, Init, List>::type;
}

#endif
