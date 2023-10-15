#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_OPERATOR_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_OPERATOR_HPP

#include TUMP_COMMON_INCLUDE(vwrap.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/push.hpp)
#include TUMP_COMMON_INCLUDE(containers/monad.hpp)

// TODO: invoke_result の特殊化を定義すること

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
        func = 31u,
    };

    inline constexpr e_op_priority decrement_op_priority(e_op_priority priority)
    {
        if (priority == e_op_priority::func) {
            return e_op_priority::_9;
        }
        return static_cast<e_op_priority>(
            static_cast<std::size_t>(priority) - 1
        );
    }

    /**
     * メタ関数を演算子のように扱う
    */
    template <InvocableArgN<2> F, e_op_priority Priority>
    struct _op {};

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
            struct check_infix_base<_op<F, Priority>, Rem> : public check_infix_base<vwrap<Priority>, Rem> {};

            template <e_op_priority Priority, std::size_t Rem>
            struct check_infix_base<vwrap<Priority>, Rem> : public std::bool_constant<
                static_cast<std::size_t>(Priority) % 3u == Rem
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

    // ----------------------------------------------------------------------------------
    // 演算子定義
    // ----------------------------------------------------------------------------------

    /**
     * haskell の $ 演算子と等価
    */
    using _apply = _op<cbk<fn::apply, 2>, e_op_priority::r_0>;

    /**
     * 関数合成を行う演算子
    */
    using _dot = _op<compose, e_op_priority::r_9>;

    /**
     * 論理和
    */
    using _or = _op<cbk<std::disjunction, 2>, e_op_priority::r_2>;

    /**
     * 論理積
    */
    using _and = _op<cbk<std::conjunction, 2>, e_op_priority::r_3>;

    /**
     * 等号
    */
    using _eq = _op<is_same, e_op_priority::_4>;

    /**
     * 不一致
    */
    using _ne = _op<is_not_same, e_op_priority::_4>;

    /**
     * リストに要素が含まれているか
     * expr _elem list
    */
    using _elem = _op<exists, e_op_priority::_4>;

    /**
     * リストに要素が含まれていないか
     * expr _not_elem list
    */
    using _not_elem = _op<not_exists, e_op_priority::_4>;

    /**
     * リストの結合
     * list1 _concat list2
    */
    using _concat = _op<cbk<fn::concat, 2>, e_op_priority::r_5>;

    /**
     * 先頭に要素を追加
     * type _cons list
    */
    using _cons = _op<partial_apply<flip, cbk<fn::push_front, 2>>, e_op_priority::r_5>;

    /**
     * fmap の演算子バージョン
    */
    using _fmap = _op<fmap, e_op_priority::l_4>;

    /**
     * アプリカティブの <*> 演算子
    */
    using _ap = _op<ap, e_op_priority::l_4>;

    /**
     * モナドの >>= 演算子に該当
    */
    using _bind = _op<bind, e_op_priority::l_1>;
}

#endif
