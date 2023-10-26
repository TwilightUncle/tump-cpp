#ifndef TUMP_INCLUDE_GUARD_TUMP_EMPTY_HPP
#define TUMP_INCLUDE_GUARD_TUMP_EMPTY_HPP 0

#include <type_traits>

namespace tump
{
    /**
     * 空のリスト
    */
    template <template <class...> class Outer>
    struct empty {};
}

#endif
