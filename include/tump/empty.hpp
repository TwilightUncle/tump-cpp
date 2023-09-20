#ifndef TUMP_INCLUDE_GUARD_TUMP_EMPTY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_EMPTY_HPP

#include <type_traits>

namespace tump
{
    /**
     * 空のリスト
    */
    template <template <class...> class Outer>
    struct empty {};

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
