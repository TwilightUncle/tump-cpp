#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP

#include <tump/containers/list.hpp>

namespace tump
{
    /**
     * 型のテンプレートパラメータを保持持つか判定
    */
    template <class T>
    struct has_type_parameters : public has_type_parameters<to_norm_li_t<T>> {};

    template <class... Parameters>
    struct has_type_parameters<list<Parameters...>> : public std::true_type {};

    template <>
    struct has_type_parameters<mp_null_t> : public std::false_type {};

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

    template <class T>
    using _constraint_type_list_impl = std::bool_constant<TypeList<T>>;

    using constraint_type_list = std::type_identity<cbk<_constraint_type_list_impl, 1>>;

    template <TypeList T>
    using constraint_st_type_list = std::type_identity<bind<cbk<std::is_same, 2>, make_empty_t<T>>>;

    template <unsigned int ArgsSize>
    struct invoke_result<callback<has_type_parameters, ArgsSize>> : public constraint_bool_constant {};
}

#endif
