#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_EXPRESSION_OPERATOR_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_EXPRESSION_OPERATOR_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/push.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(algorithm/compare.hpp)
#include TUMP_V_0_1_2_COMMON_INCLUDE(containers/monad.hpp)

namespace tump_0_1_2
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

    /**
     * 演算子かどうか判定
    */
    template <class T>
    concept TumpOperator = is_operator_v<T>;

    namespace fn
    {
        /**
         * 演算子の優先度を比較可能な型かどうか判定
        */
        template <class T>
        struct is_compatible_op_priority : public std::false_type {};

        template <e_op_priority Priority>
        struct is_compatible_op_priority<vwrap<Priority>> : public std::true_type {};

        template <class F, e_op_priority Priority>
        struct is_compatible_op_priority<_op<F, Priority>> : public std::true_type {};
    }

    /**
     * 演算子の優先度を比較可能な型かどうか判定
    */
    template <class T>
    constexpr auto is_compatible_op_priority_v = fn::is_compatible_op_priority<T>::value;

    /**
     * 演算子の優先度を比較可能な型かどうか判定
    */
    template <class T>
    concept CompatibleOpPriority = is_compatible_op_priority_v<T>;

    namespace fn
    {
        /**
         * CompatibleOpPriority の制約を満たす型から、e_op_priority 型の値を取得する
        */
        template <CompatibleOpPriority T>
        struct get_op_priority;

        template <e_op_priority Priority>
        struct get_op_priority<vwrap<Priority>> : public vwrap<Priority> {};

        template <class F, e_op_priority Priority>
        struct get_op_priority<_op<F, Priority>> : public vwrap<Priority> {};
    }

    /**
     * CompatibleOpPriority の制約を満たす型から、e_op_priority 型の値を取得する
    */
    template <CompatibleOpPriority T>
    using get_op_priority_t = typename fn::get_op_priority<T>::type;

    /**
     * CompatibleOpPriority の制約を満たす型から、e_op_priority 型の値を取得する
    */
    template <CompatibleOpPriority T>
    constexpr auto get_op_priority_v = fn::get_op_priority<T>::value;
    
    namespace fn
    {
        /**
         * 演算子の優先度について、型を三方比較する
        */
        template <CompatibleOpPriority L, CompatibleOpPriority R>
        struct compare_op_priority : public vwrap<
            static_cast<int>(get_op_priority_v<L>) - static_cast<int>(get_op_priority_v<R>)
        > {};
    }

    /**
     * 演算子優先度についての比較メタ関数群
    */
    using comparing_op_priority = comparing_type<
        cbk<fn::compare_op_priority, 2>,
        cbk<fn::is_compatible_op_priority, 1>
    >;

    namespace fn
    {
        namespace impl
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
        using is_infixr = impl::check_infix_base<Op, 0u>;

        template <class Op>
        using is_infixl = impl::check_infix_base<Op, 1u>;

        template <class Op>
        using is_infix = impl::check_infix_base<Op, 2u>;
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
        struct sec<_op<F, Priority>, T> : public apply<::tump_0_1_2::flip, F, T> {};
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
    using _apply = _op<apply<>, e_op_priority::r_0>;

    /**
     * 関数合成を行う演算子
    */
    using _dot = _op<compose<>, e_op_priority::r_9>;

    /**
     * 論理和
    */
    using _or = _op<disjunction<>, e_op_priority::r_2>;

    /**
     * 論理積
    */
    using _and = _op<conjunction<>, e_op_priority::r_3>;

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
    using _concat = _op<concat<>, e_op_priority::r_5>;

    /**
     * 先頭に要素を追加
     * type _cons list
    */
    using _cons = _op<partial_apply<flip, push_front<>>, e_op_priority::r_5>;

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
