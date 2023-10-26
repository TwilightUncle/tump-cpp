#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_VLIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_VLIST_HPP 7

#include TUMP_COMMON_INCLUDE(vwrap.hpp) // 1
#include TUMP_COMMON_INCLUDE(containers/list.hpp) // 6

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
        struct unwrap_vlist;

        template <VFunctional... WrapedValues>
        struct unwrap_vlist<wraped_vlist<WrapedValues...>> : public std::type_identity<vlist<(WrapedValues::value)...>> {};
    
        /**
         * vlist であるか判定
        */
        template <class T>
        struct is_vlist : public std::false_type {};

        template <auto... Values>
        struct is_vlist<vlist<Values...>> : public std::true_type {};
    }

    /**
     * vlist を wraped_vlist へ変換
    */
    using wrap_vlist = cbk<fn::wrap_vlist, 1>;

    /**
     * wraped_vlist の持つ型をすべて値に変換する
    */
    using unwrap_vlist = cbk<fn::unwrap_vlist, 1>;

    /**
     * vlist であるか判定
    */
    using is_vlist = cbk<fn::is_vlist, 1>;

    /**
     * 非型パラメータパックから wraped_vlist を作成する
    */
    template <auto... Values>
    using make_wraped_vlist_t = typename fn::make_wraped_vlist<Values...>::type;
    
    /**
     * vlist を wraped_vlist へ変換
    */
    template <class VList>
    using wrap_vlist_t = typename fn::wrap_vlist<VList>::type;
    
    /**
     * 非型パラメータパックから wraped_vlist を作成する
    */
    template <class WrpedVList>
    using unwrap_vlist_t = typename fn::unwrap_vlist<WrpedVList>::type;

    /**
     * vlist であるか判定
    */
    template <class T>
    constexpr auto is_vlist_v = fn::is_vlist<T>::value;

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    namespace fn
    {
        template <auto... Values>
        struct to_norm_li<vlist<Values...>> : public to_norm_li<make_wraped_vlist_t<Values...>> {};

        template <VFunctional... WrapedValues>
        struct to_norm_li<wraped_vlist<WrapedValues...>> : public std::type_identity<list<WrapedValues...>> {};

        template <auto... OldValue, VFunctional... WrapedValues>
        struct unnorm_li<vlist<OldValue...>, list<WrapedValues...>> : public std::type_identity<vlist<(WrapedValues::value)...>> {};

        template <VFunctional... OldValue, VFunctional... WrapedValues>
        struct unnorm_li<wraped_vlist<OldValue...>, list<WrapedValues...>> : public std::type_identity<wraped_vlist<WrapedValues...>> {};

        template <auto... Values>
        struct get_container_constraint<vlist<Values...>> : public std::type_identity<::tump::to_true> {};

        template <VFunctional... WrapedValues>
        struct get_container_constraint<wraped_vlist<WrapedValues...>> : public std::type_identity<::tump::to_true> {};

        template <auto... Values, class _>
        struct make_empty<vlist<Values...>, _> : public std::type_identity<vlist<>> {};

        template <VFunctional... WrapedValues, class _>
        struct make_empty<wraped_vlist<WrapedValues...>, _> : public std::type_identity<wraped_vlist<>> {};

        template <>
        struct is_empty<vlist<>> : public std::true_type {};

        template <>
        struct is_empty<wraped_vlist<>> : public std::true_type {};
    }
}

#endif
