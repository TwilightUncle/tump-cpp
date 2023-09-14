#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP

#include <tump/empty.hpp>

namespace tump {
    /**
     * 型のテンプレートパラメータを保持持つか判定
    */
    template <class T>
    struct has_type_parameters : public std::false_type {};

    template <template <class...> class Outer, class... Parameters>
    struct has_type_parameters<Outer<Parameters...>> : public std::true_type {};

    /**
     * 型のテンプレートパラメータを保持持つか判定
    */
    template <class T>
    constexpr auto has_type_parameters_v = has_type_parameters<T>::value;

    /**
     * テンプレートパラメータを持つ型
    */
    template <class T>
    concept TypeList = has_type_parameters_v<T> || is_empty_v<T>;
}

#endif
