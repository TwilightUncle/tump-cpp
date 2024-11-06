#ifndef TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_BTREE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_CONTAINERS_BTREE_HPP

#include TUMP_COMMON_INCLUDE(containers/list.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/through_if.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/compare.hpp)
#include TUMP_COMMON_INCLUDE(algorithm/push.hpp)

namespace tump_1_0_0
{
    /**
     * バイナリツリーの節
    */
    template <tump::NotSameAs<mp_null_t> T, class Grater = mp_null_t, class Less = mp_null_t>
    struct bnode {};

    /**
     * バイナリツリー
     * T には 任意の型を指定
     * Comparing には比較を行うクラスを指定
    */
    template <class T, TumpComparing Comparing = comparing_size>
    struct bintree : public _::base_list {};

    /**
     * 空のバイナリツリーを取得
    */
    template <TumpComparing Comparing = comparing_size>
    using empty_bintree = bintree<mp_null_t, Comparing>;

    namespace fn
    {
        /**
         * バイナリツリーかどうか判定
        */
        template <class T>
        struct is_bintree : public std::false_type {};

        template <class T, TumpComparing Comparing>
        struct is_bintree<bintree<T, Comparing>> : public std::true_type {};
    }

    /**
     * バイナリツリーかどうか判定
    */
    using is_bintree = cbk<fn::is_bintree, 1>;

    /**
     * バイナリツリーかどうか判定
    */
    template <class T>
    constexpr auto is_bintree_v = fn::is_bintree<T>::value;

    template <class T>
    concept BynaryTree = is_bintree_v<T>;

    namespace fn
    {
        namespace impl
        {
            // push の実装
            template <class T, class New, TumpComparing Comparing>
            struct push_impl : public std::type_identity<
                bnode<
                    T,
                    invoke_t<::tump_1_0_0::through_if, partial_apply<typename Comparing::lt, T>, New, mp_null_t>,
                    invoke_t<::tump_1_0_0::through_if, partial_apply<typename Comparing::ge, T>, New, mp_null_t>
                >
            > {};

            template <class New, TumpComparing Comparing>
            struct push_impl<mp_null_t, New, Comparing> : public std::type_identity<New> {};

            template <class T, class New, TumpComparing Comparing>
            struct push_impl<bnode<T, mp_null_t, mp_null_t>, New, Comparing> : public push_impl<T, New, Comparing> {};

            template <class T, class Grater, class Less, class New, TumpComparing Comparing>
            requires (Comparing::template lt_v<T, New>)
            struct push_impl<bnode<T, Grater, Less>, New, Comparing> : public std::type_identity<
                bnode<T, typename push_impl<Grater, New, Comparing>::type, Less>
            > {};

            template <class T, class Grater, class Less, class New, TumpComparing Comparing>
            requires (Comparing::template ge_v<T, New>)
            struct push_impl<bnode<T, Grater, Less>, New, Comparing> : public std::type_identity<
                bnode<T, Grater, typename push_impl<Less, New, Comparing>::type>
            > {};

            // 最小の要素を取得するメタ関数の実装
            template <class T, TumpComparing Comparing>
            struct get_min_impl : public std::type_identity<T> {};

            template <class T, class Grater, TumpComparing Comparing>
            struct get_min_impl<bnode<T, Grater, mp_null_t>, Comparing> : public std::type_identity<T> {};

            template <class T, class Grater, class Less, TumpComparing Comparing>
            struct get_min_impl<bnode<T, Grater, Less>, Comparing> : public get_min_impl<Less, Comparing> {};

            // 最大の要素を取得するメタ関数の実装
            template <class T, TumpComparing Comparing>
            struct get_max_impl : public std::type_identity<T> {};

            template <class T, class Less, TumpComparing Comparing>
            struct get_max_impl<bnode<T, mp_null_t, Less>, Comparing> : public std::type_identity<T> {};

            template <class T, class Grater, class Less, TumpComparing Comparing>
            struct get_max_impl<bnode<T, Grater, Less>, Comparing> : public get_max_impl<Grater, Comparing> {};

            // 最小の要素を削除するメタ関数の実装
            template <class T, TumpComparing Comparing>
            struct pop_min_impl : public std::type_identity<mp_null_t> {};
            
            template <class T, TumpComparing Comparing>
            struct pop_min_impl<bnode<T, mp_null_t, mp_null_t>, Comparing> : public std::type_identity<mp_null_t> {};

            template <class T, class Grater, TumpComparing Comparing>
            struct pop_min_impl<bnode<T, Grater, mp_null_t>, Comparing> : public std::type_identity<Grater> {};

            template <class T, class Grater, class Less, TumpComparing Comparing>
            struct pop_min_impl<bnode<T, Grater, Less>, Comparing> : public std::type_identity<
                bnode<T, Grater, typename pop_min_impl<Less, Comparing>::type>
            > {};

            // 最大の要素を削除するメタ関数の実装
            template <class T, TumpComparing Comparing>
            struct pop_max_impl : public std::type_identity<mp_null_t> {};
            
            template <class T, TumpComparing Comparing>
            struct pop_max_impl<bnode<T, mp_null_t, mp_null_t>, Comparing> : public std::type_identity<mp_null_t> {};

            template <class T, class Less, TumpComparing Comparing>
            struct pop_max_impl<bnode<T, mp_null_t, Less>, Comparing> : public std::type_identity<Less> {};

            template <class T, class Grater, class Less, TumpComparing Comparing>
            struct pop_max_impl<bnode<T, Grater, Less>, Comparing> : public std::type_identity<
                bnode<T, typename pop_max_impl<Grater, Comparing>::type, Less>
            > {};

        }

        /**
         * バイナリツリーに要素を挿入
        */
        template <BynaryTree T, class... Types>
        struct push;

        template <class T, class Type, TumpComparing Comparing>
        struct push<bintree<T, Comparing>, Type> : public std::type_identity<
            bintree<
                typename impl::push_impl<T, Type, Comparing>::type,
                Comparing
            >
        > {};

        template <class T, class... Types, TumpComparing Comparing>
        struct push<bintree<T, Comparing>, Types...> : public foldl<
            cbk<push, 2>,
            bintree<T, Comparing>,
            list<Types...>
        > {};

        /**
         * バイナリツリーの一番小さい値を取得
        */
        template <BynaryTree T>
        struct get_min;

        template <class T, TumpComparing Comparing>
        struct get_min<bintree<T, Comparing>> : public impl::get_min_impl<T, Comparing> {};

        /**
         * バイナリツリーの一番大きい値を取得
        */
        template <BynaryTree T>
        struct get_max;

        template <class T, TumpComparing Comparing>
        struct get_max<bintree<T, Comparing>> : public impl::get_max_impl<T, Comparing> {};

        /**
         * バイナリツリーの一番小さい値を削除
        */
        template <BynaryTree T>
        struct pop_min;

        template <class T, TumpComparing Comparing>
        struct pop_min<bintree<T, Comparing>> : public std::type_identity<
            bintree<
                typename impl::pop_min_impl<T, Comparing>::type,
                Comparing
            >
        > {};

        /**
         * バイナリツリーの一番大きい値を削除
        */
        template <BynaryTree T>
        struct pop_max;

        template <class T, TumpComparing Comparing>
        struct pop_max<bintree<T, Comparing>> : public std::type_identity<
            bintree<
                typename impl::pop_max_impl<T, Comparing>::type,
                Comparing
            >
        > {};
    }

    /**
     * バイナリツリーに要素を挿入
    */
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using push = cbk<fn::push, ArgsSize>;

    /**
     * バイナリツリーに要素を挿入
    */
    template <BynaryTree T, class... Types>
    using push_t = typename fn::push<T, Types...>::type;

    
    /**
     * バイナリツリーの一番小さい値を取得
    */
    using get_min = cbk<fn::get_min, 1>;
    
    /**
     * バイナリツリーの一番小さい値を取得
    */
    template <BynaryTree T>
    using get_min_t = typename fn::get_min<T>::type;

    /**
     * バイナリツリーの一番大きい値を取得
    */
    using get_max = cbk<fn::get_max, 1>;

    /**
     * バイナリツリーの一番大きい値を取得
    */
    template <BynaryTree T>
    using get_max_t = typename fn::get_max<T>::type;

    /**
     * バイナリツリーの一番小さい値を削除
    */
    using pop_min = cbk<fn::pop_min, 1>;

    /**
     * バイナリツリーの一番小さい値を削除
    */
    template <BynaryTree T>
    using pop_min_t = typename fn::pop_min<T>::type;

    /**
     * バイナリツリーの一番大きい値を削除
    */
    using pop_max = cbk<fn::pop_max, 1>;

    /**
     * バイナリツリーの一番大きい値を削除
    */
    template <BynaryTree T>
    using pop_max_t = typename fn::pop_max<T>::type;

    namespace fn
    {
        /**
         * リストをバイナリツリーに変換
        */
        template <TypeList List, TumpComparing Comparing = comparing_size>
        struct to_bintree : public foldl<
            ::tump_1_0_0::push<>,
            empty_bintree<Comparing>,
            List
        > {};

        template <class T, TumpComparing Comparing, TumpComparing _NotUse>
        struct to_bintree<bintree<T, Comparing>, _NotUse> : public std::type_identity<bintree<T, Comparing>> {};

        namespace impl
        {
            template <TypeList List, BynaryTree Btree>
            struct flatten_impl : public std::conditional_t<
                is_empty_v<Btree>,
                std::type_identity<List>,
                invoke<
                    cbk<flatten_impl, 2>,
                    push_back_t<List, get_min_t<Btree>>,
                    pop_min_t<Btree>
                >
            > {};
        }

        /**
         * バイナリツリーを一次元のリストに変換する
        */
        template <BynaryTree T>
        using flatten = impl::flatten_impl<list<>, T>;
    }

    /**
     * リストをバイナリツリーに変換
    */
    using to_bintree = cbk<fn::to_bintree, 2>;

    /**
     * sizeof した時の値を基準としたバイナリツリーにリストを変換する
    */
    using to_size_bintree = partial_apply<flip, to_bintree, comparing_size>;

    /**
     * リストをバイナリツリーに変換
    */
    template <TypeList List, TumpComparing Comparing = comparing_size>
    using to_bintree_t = typename fn::to_bintree<List, Comparing>::type;

    /**
     * バイナリツリーを一次元のリストに変換する
    */
    using flatten = cbk<fn::flatten, 1>;

    /**
     * バイナリツリーを一次元のリストに変換する
    */
    template <BynaryTree T>
    using flatten_t = typename fn::flatten<T>::type;

    // ---------------------------------------------------------
    // 下記メソッドの実装定義
    // 宣言については tump/containers/methods.hpp を参照されたし
    // ---------------------------------------------------------

    namespace fn
    {
        template <class T, TumpComparing Comparing>
        struct to_norm_li<bintree<T, Comparing>> : public flatten<bintree<T, Comparing>> {};

        template <class Old, TumpComparing Comparing, class... Types>
        struct unnorm_li<bintree<Old, Comparing>, list<Types...>> : public to_bintree<list<Types...>, Comparing> {};

        template <class T, TumpComparing Comparing>
        struct make_empty<bintree<T, Comparing>> : public std::type_identity<empty_bintree<Comparing>> {};

        template <TumpComparing Comparing>
        struct is_empty<empty_bintree<Comparing>> : public std::true_type {};
    }
}

#endif
