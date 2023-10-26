#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_FUNCTOR_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_FUNCTOR_HPP 13

#include TUMP_COMMON_INCLUDE(metafunction/compose.hpp) // 12
#include TUMP_COMMON_INCLUDE(algorithm/map.hpp) // 11

namespace tump
{
    namespace fn
    {
        /**
         * haskellを参考に、ファンクタ
        */
        template <Invocable F, class Functor>
        struct fmap;

        // リスト用の実装
        template <Invocable F, TypeList List>
        requires (!Invocable<List>)
        struct fmap<F, List> : public fn::map<F, List> {};

        // 関数用の実装
        template <Invocable F, Invocable F2>
        struct fmap<F, F2> : public std::type_identity<compose_t<F, F2>> {};
    }

    /**
     * haskellを参考に、ファンクタ
    */
    using fmap = cbk<fn::fmap, 2>;

    /**
     * haskellを参考に、ファンクタ
    */
    template <Invocable F, class Functor>
    using fmap_t = typename fn::fmap<F, Functor>::type;
}

#endif
