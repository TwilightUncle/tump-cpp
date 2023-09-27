#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_TO_TRUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_TO_TRUE_HPP

#include <type_traits>

namespace tump
{
    /**
     * あらゆる型を std::true_typeに変換する
    */
    template <class T>
    using to_true = std::true_type;

    /**
     * あらゆる型を渡しても真
    */
    template <class T>
    constexpr auto to_true_v = to_true<T>::value;
}

#endif
