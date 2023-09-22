#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_METHODS_HPP

#include <tump/null.hpp>
#include <tump/empty.hpp>

namespace tump
{
    template <class T>
    struct to_norm_li : public std::type_identity<mp_null_t> {};

    template <class T>
    using to_norm_li_t = to_norm_li<T>::type;

    template <class Container, class NormalizedList>
    struct unnorm_li;

    template <class Container, class NormalizedList>
    using unnorm_li_t = unnorm_li<Container, NormalizedList>::type;

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
    */
    template <class List>
    struct make_empty;

    template <template <class...> class Outer, class... Types>
    struct make_empty<Outer<Types...>> : public std::type_identity<empty<Outer>> {};

    template <template <class...> class Outer>
    struct make_empty<empty<Outer>> : public std::type_identity<empty<Outer>> {};

    /**
     * 指定したリストの側だけ取り出し、空のリストを作成する
    */
    template <class List>
    using make_empty_t = make_empty<List>::type;

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    struct is_empty : public std::false_type {};

    template <template <class...> class Outer>
    struct is_empty<empty<Outer>> : public std::true_type {};

    /**
     * 空のリストかどうか判定する
    */
    template <class T>
    constexpr auto is_empty_v = is_empty<T>::value;
}

#endif
