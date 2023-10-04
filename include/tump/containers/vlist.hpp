#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_VLIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_VLIST_HPP

#include <tump/vwrap.hpp>
#include <tump/containers/list.hpp>

namespace tump
{
    /**
     * 非型テンプレートパラメータパックを保持する
    */
    template <auto... Values>
    struct vlist {};

    /**
     * value定数メンバを持つ型のみ保持するリスト
    */
    template <VFunctional... WrapedValues>
    struct wraped_vlist : _::base_list {};

    namespace fn
    {
        /**
         * 非型パラメータパックから wraped_vlist を作成する
        */
        template <auto... Values>
        struct make_wraped_vlist : public std::type_identity<wraped_vlist<vwrap<Values>...>> {};

        /**
         * vlist を wraped_vlist へ変換
        */
        template <class VList>
        struct wrap_vlist;

        template <auto... Values>
        struct wrap_vlist<vlist<Values...>> : public make_wraped_vlist<Values...> {};

        /**
         * wraped_vlist の持つ型をすべて値に変換する
        */
        template <class List>
        struct unwrap;

        template <VFunctional... WrapedValues>
        struct unwrap<wraped_vlist<WrapedValues...>> : public std::type_identity<vlist<(WrapedValues::value)...>> {};
    }

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    namespace fn
    {
        template <VFunctional... WrapedValues>
        struct to_norm_li<wraped_vlist<WrapedValues...>> : public std::type_identity<list<WrapedValues...>> {};

        template <VFunctional... OldValue, VFunctional... WrapedValues>
        struct unnorm_li<wraped_vlist<OldValue...>, list<WrapedValues...>> : public std::type_identity<wraped_vlist<WrapedValues...>> {};

        template <VFunctional... WrapedValues>
        struct get_container_constraint<wraped_vlist<WrapedValues...>> : public std::type_identity<::tump::to_true> {};

        template <VFunctional... WrapedValues, class NewConstraint>
        struct make_empty<wraped_vlist<WrapedValues...>, NewConstraint> : public std::type_identity<wraped_vlist<>> {};

        template <>
        struct is_empty<wraped_vlist<>> : public std::true_type {};
    }
}

#endif
