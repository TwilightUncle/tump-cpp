#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_TO_TRUE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_TO_TRUE_HPP

#include <tump/metafunction/callback.hpp>

namespace tump
{
    namespace fn
    {
        /**
         * あらゆる型を std::true_typeに変換する
        */
        template <class T>
        using to_true = std::true_type;
    }

    using to_true = cbk<fn::to_true, 1>;

    /**
     * あらゆる型を渡しても真
    */
    template <class T>
    constexpr auto to_true_v = fn::to_true<T>::value;
}

#endif
