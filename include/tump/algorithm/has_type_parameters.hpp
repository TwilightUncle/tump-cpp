#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_HAS_TYPE_PARAMETERS_HPP

#include TUMP_COMMON_INCLUDE(containers/vlist.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/std.hpp)

namespace tump_1_0_0
{
    namespace fn
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
    }

    /**
     * 型のテンプレートパラメータを保持持つか判定
    */
    using has_type_parameters = cbk<fn::has_type_parameters, 1>;

    /**
     * 型のテンプレートパラメータを保持持つか判定
    */
    template <class T>
    constexpr auto has_type_parameters_v = fn::has_type_parameters<T>::value;

    /**
     * 型テンプレートパラメータを持つ型ことのできる型のリストか判定
    */
    template <class T>
    concept TypeList = (has_type_parameters_v<T> || is_empty_v<T>) && !is_vlist_v<T>;

    /**
     * 非型テンプレートパラメータを持つ型ことのできる型のリストか判定
    */
    template <class T>
    concept ValueList = (is_vlist_v<T> || is_empty_v<T>) && !has_type_parameters_v<T>;

    /**
     * 型/非型テンプレートパラメータを持つ型ことのできる型のリストか判定
     * 混在はNG
    */
    template <class T>
    concept TypeListOrValueList = (has_type_parameters_v<T> || is_vlist_v<T> || is_empty_v<T>);

    namespace fn
    {
        /**
         * テンプレートパラメータを持つ型ことのできる型のリストか判定
        */
        template <class T>
        using is_type_list = std::bool_constant<TypeList<T>>;
    }

    /**
     * テンプレートパラメータを持つ型ことのできる型のリストか判定
    */
    using is_type_list = cbk<fn::is_type_list, 1>;

    /**
     * テンプレートパラメータを持つ型ことのできる型のリストか判定
    */
    template <class T>
    constexpr auto is_type_list_v = fn::is_type_list<T>::value;

    namespace fn
    {
        /**
         * 二つのリストのコンテナが等しいか判定
        */
        template <class T1, class T2>
        struct is_same_container : public std::false_type {};

        template <TypeList List1, TypeList List2>
        struct is_same_container<List1, List2> : public std::is_same<
            make_empty_t<List1>,
            make_empty_t<List2>
        >::type {};
    }

    /**
     * 二つのリストのコンテナが等しいか判定
    */
    using is_same_container = cbk<fn::is_same_container, 2>;

    /**
     * 二つのリストのコンテナが等しいか判定
    */
    template <class T1, class T2>
    constexpr auto is_same_container_v = fn::is_same_container<T1, T2>::value;
}

#endif
