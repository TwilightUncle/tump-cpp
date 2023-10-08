#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_APPLICATIVE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_APPLICATIVE_HPP

#include TUMP_COMMON_INCLUDE(containers/functor.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/apply.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/concat.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/left_right.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/make_type_list.hpp)

namespace tump
{
    namespace fn
    {
        /**
         * 任意の型の持ち上げ
        */
        template <class T>
        struct pure : public std::type_identity<pure<T>> {};

        /**
         * コンテナに持ち上げた関数をコンテナに適用
        */
        template <class WrappedF, class Applicative>
        struct ap;

        // pure 同士の実装
        template <Invocable F, class T>
        struct ap<pure<F>, pure<T>> : public std::type_identity<
            pure<apply_t<F, T>>
        > {};

        // pure とアプリカティブクラスの実装
        template <Invocable F, class Applicative>
        struct ap<pure<F>, Applicative> : public fmap<
            partial_apply<::tump::apply, F>, Applicative
        > {};

        // リストの実装
        template <TypeList FList, class T>
        struct ap<FList, pure<T>> : public ap<
            FList,
            make_type_list_t<FList, T>
        > {};

        template <TypeList FList, TypeList List>
        struct ap<FList, List> : public fn::unnorm_li<
            make_empty_t<
                List,
                mp_invoke_result_t<::tump::apply, get_front_t<FList>, get_front_t<List>>
            >,
            ap<to_norm_li_t<FList>, to_norm_li_t<List>>
        > {};

        template <Invocable... Funcs, class... Types>
        struct ap<list<Funcs...>, list<Types...>> : public fn::concat<
            fmap_t<
                partial_apply<::tump::apply, Funcs>,
                list<Types...>
            >...
        > {};
    }

    using pure = cbk<fn::pure, 1>;

    using ap = cbk<fn::ap, 2>;

    template <class T>
    using pure_t = typename fn::pure<T>::type;

    template <class WrappedF, class Applicative>
    using ap_t = typename fn::ap<WrappedF, Applicative>::type;
}

#endif
