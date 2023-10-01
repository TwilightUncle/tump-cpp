#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_OPERATOR_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_OPERATOR_HPP

#include <tump/metafunction/apply.hpp>
#include <tump/metafunction/compose.hpp>

namespace tump
{
    /**
     * 演算子の優先度定義。
     * 数値が大きいものほど先に評価される。
     * とりあえず10段階。
     * r, l は結合の向き。rもlもないものは非結合
    */
    enum class e_op_priority : std::size_t
    {
        r_0, l_0, _0,
        r_1, l_1, _1,
        r_2, l_2, _2,
        r_3, l_3, _3,
        r_4, l_4, _4,
        r_5, l_5, _5,
        r_6, l_6, _6,
        r_7, l_7, _7,
        r_8, l_8, _8,
        r_9, l_9, _9,
        func,
    };

    inline constexpr e_op_priority decrement_op_priority(e_op_priority priority)
    {
        return static_cast<e_op_priority>(
            static_cast<std::size_t>(priority) - 1
        );
    }

    /**
     * メタ関数を演算子のように扱う
    */
    template <InvocableArgN<2> F, e_op_priority Priority>
    struct _op {};

    /**
     * haskell の $ 演算子と等価
    */
    using _doll = _op<cbk<fn::invoke, 2>, e_op_priority::r_0>;

    /**
     * 関数合成を行う演算子
    */
    using _dot = _op<cbk<fn::compose, 2>, e_op_priority::r_9>;

    namespace fn
    {
        template <class T>
        struct is_operator : public std::false_type {};

        template <class F, e_op_priority Priority>
        struct is_operator<_op<F, Priority>> : public std::true_type {};
    }

    /**
     * 演算子かどうか判定
    */
    template <class T>
    constexpr auto is_operator_v = fn::is_operator<T>::value;

    namespace fn
    {
        template <class T, e_op_priority Priority>
        struct eq_op_priority : public std::false_type {};

        template <InvocableArgN<2> F, e_op_priority OpPriority, e_op_priority CompPriority>
        struct eq_op_priority<_op<F, OpPriority>, CompPriority> : public std::bool_constant<OpPriority == CompPriority> {};
    }

    /**
     * 演算子の優先度が指定のものと一致しているか確認
    */
    template <class T, e_op_priority Priority>
    constexpr auto eq_op_priority_v = fn::eq_op_priority<T, Priority>::value;

    namespace fn
    {
        namespace _
        {
            // 剰余で結合性チェック
            template <class T, std::size_t Rem>
            requires (Rem < 3u)
            struct check_infix_base : public std::false_type {};

            template <InvocableArgN<2> F, e_op_priority Priority, std::size_t Rem>
            struct check_infix_base<_op<F, Priority>, Rem> : public std::bool_constant<
                static_case<std::size_t>(Priority) % 3u == Rem
            > {};
        }

        template <class Op>
        using is_infixr = _::check_infix_base<Op, 0u>;

        template <class Op>
        using is_infixl = _::check_infix_base<Op, 1u>;

        template <class Op>
        using is_infix = _::check_infix_base<Op, 2u>;
    }

    /**
     * 右結合か判定
    */
    template <class Op>
    constexpr auto is_infixr_v = fn::is_infixr<Op>::value;

    /**
     * 左結合か判定
    */
    template <class Op>
    constexpr auto is_infixl_v = fn::is_infixl<Op>::value;

    /**
     * 非結合か判定
    */
    template <class Op>
    constexpr auto is_infix_v = fn::is_infix<Op>::value;

    namespace fn
    {
        /**
         * 演算子に部分適用を行う
        */
        template <class T1, class T2>
        struct sec;

        template <InvocableArgN<2> F, e_op_priority Priority, class T>
        struct sec<T, _op<F, Priority>> : public apply<F, T> {};

        template <InvocableArgN<2> F, e_op_priority Priority, class T>
        struct sec<_op<F, Priority>, T> : public apply<::tump::flip, F, T> {};
    }

    /**
     * 演算子に部分適用を行う
    */
    template <class T1, class T2>
    using sec = typename fn::sec<T1, T2>::type;
}

#endif
