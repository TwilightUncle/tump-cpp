#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_CONTAINERS_MONAD_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_CONTAINERS_MONAD_HPP

#include TUMP_COMMON_INCLUDE(containers/applicative.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        template <class T>
        using ret = pure<T>;

        template <class Monad, class F>
        struct bind;

        template <class Monad>
        struct bind<Monad, cbk<ret, 1>> : public std::type_identity<Monad> {};

        /**
         * ret を除いたメタ関数であるか判定
        */
        template <class T>
        concept InvocableNeReturen = is_callback_v<T> && !std::is_same_v<T, cbk<ret, 1>>;

        template <class T, InvocableNeReturen F>
        struct bind<ret<T>, F> : public fn::apply<F, T> {};

        // リストの実装
        template <TypeList List, InvocableNeReturen F>
        struct bind<List, F> : public fn::unnorm_li<
            List,
            bind<to_norm_li_t<List>, F>
        > {};

        template <InvocableNeReturen F, class... Types>
        struct bind<list<Types...>, F> : public fn::concat<
            apply_t<F, Types>...
        > {};
    }

    using ret = cbk<fn::ret, 1>;

    template <class T>
    using ret_t = typename fn::ret<T>::type;

    using bind = cbk<fn::bind, 2>;

    template <class Monad, Invocable F>
    using bind_t = typename fn::bind<Monad, F>::type;
}

#endif
