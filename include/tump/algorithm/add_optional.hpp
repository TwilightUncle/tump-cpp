#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_ADD_OPTIONAL_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_ALGORITHM_ADD_OPTIONAL_HPP

#include <optional>
#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/callback.hpp)

namespace tump_0_1_2
{
    namespace fn
    {
        /**
         * 任意の型にoptionalを付与する
        */
        template <class T>
        struct add_optional : public std::type_identity<
            std::optional<T>
        > {};

        template <class T>
        struct add_optional<std::optional<T>> : public add_optional<T> {};

        /**
         * optional がついていたら取り除く
        */
        template <class T>
        struct remove_optional : public std::type_identity<T> {};

        template <class T>
        struct remove_optional<std::optional<T>> : public remove_optional<T> {};
    }

    /**
     * 任意の型にoptionalを付与する
    */
    using add_optional = cbk<fn::add_optional, 1>;

    /**
     * optional がついていたら取り除く
    */
    using remove_optional = cbk<fn::remove_optional, 1>;

    /**
     * 任意の型にoptionalを付与する
    */
    template <class T>
    using add_optional_t = typename fn::add_optional<T>::type;

    /**
     * optional がついていたら取り除く
    */
    template <class T>
    using remove_optional_t = typename fn::remove_optional<T>::type;
}

#endif
