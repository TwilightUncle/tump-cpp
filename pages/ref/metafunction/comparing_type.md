---
title: comparing_type - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <InvocableArgN<2> Compare, InvocableArgN<1> Constraint = to_true>
    struct comparing_type
    {
        struct fn
        {
            template <class L, class R>
            struct lt {};
            template <class L, class R>
            struct gt {};
            template <class L, class R>
            struct le {};
            template <class L, class R>
            struct ge {};
            template <class L, class R>
            struct eq {};
            template <class L, class R>
            struct ne {};
            
            template <class L, class R>
            struct get_grater {};
            template <class L, class R>
            struct get_less {};
        };

        using lt = cbk<fn::lt, 2>;
        using gt = cbk<fn::gt, 2>;
        using le = cbk<fn::le, 2>;
        using ge = cbk<fn::ge, 2>;
        using eq = cbk<fn::eq, 2>;
        using ne = cbk<fn::ne, 2>;

        template <class L, class R>
        static constexpr bool lt_v = fn::lt<L, R>::value;
        template <class L, class R>
        static constexpr bool gt_v = fn::gt<L, R>::value;
        template <class L, class R>
        static constexpr bool le_v = fn::le<L, R>::value;
        template <class L, class R>
        static constexpr bool ge_v = fn::ge<L, R>::value;
        template <class L, class R>
        static constexpr bool eq_v = fn::eq<L, R>::value;
        template <class L, class R>
        static constexpr bool ne_v = fn::ne<L, R>::value;

        using get_grater = cbk<fn::get_grater, 2>;
        using get_less = cbk<fn::get_less, 2>;

        template <class L, class R>
        using get_grater_t = typename fn::get_grater<L, R>::type;
        template <class L, class R>
        using get_less_t = typename fn::get_less<L, R>::type;
    };
    
    // sizeof の結果による型の比較を行う
    using comparing_size = comparing_type<...>;
}
```

### パラメータ

- Compare - 2 つの型を受け取り、三方比較を行うメタ関数
- Constraint - 比較可能な型の制約を行うメタ関数
- L - 任意の型
- R - 任意の型

## 概要

`tump::comparing_type`は、三方比較のメタ関数`Compare`を受け取り、2 つの型を比較するメタ関数を生成するテンプレートクラスです。

下記のメタ関数が`tump::comparing_type`のテンプレートメンバ型として使用できます。

| メンバ関数名 | 概要 |
| --- | --- |
| `lt` | 型`L`と`R`を比較し、`L`の大きさが`R`未満かどうか判定します。 |
| `gt` | 型`L`と`R`を比較し、`L`の大きさが`R`超かどうか判定します。 |
| `le` | 型`L`と`R`を比較し、`L`の大きさが`R`以下かどうか判定します。 |
| `ge` | 型`L`と`R`を比較し、`L`の大きさが`R`以上かどうか判定します。 |
| `eq` | 型`L`と`R`を比較し、`L`と`R`が等しい大きさか判定します。 |
| `ne` | 型`L`と`R`を比較し、`L`と`R`が異なる大きさか判定します。 |
| `get_grater` | 型`L`と`R`を比較し、大きいほうの型を返します。 |
| `get_less` | 型`L`と`R`を比較し、小さいほうの型を返します。 |

なお、`sizeof`による型の大きさの比較用に、`tump::comparing_type`を利用した`tump::comparing_size`が定義済みです。

## 三方比較のメタ関数

`tump::comparing_type`は三方比較のメタ関数`Compare`により、任意の基準で大小比較を行います。  
ただし、メタ関数`Compare`は下記の機能を持っている必要があります。

1. 2 引数を受け取る第一級メタ関数
1. 型`L`と`R`を渡した結果、`L`の大きさが`R`未満の時負の整数を返却
1. 型`L`と`R`を渡した結果、`L`の大きさが`R`超の時正の整数を返却
1. 型`L`と`R`を渡した結果、`L`の大きさが`R`と等しい場合整数の`0`を返却

例えば、あらゆる型に対して`sizeof`による大小比較を行う`tump::comparing_size`は、下記のように定義された三方比較のメタ関数`compare_size`により定義されています。

```cpp
namespace tump
{
    namespace fn
    {
        template <class L, class R>
        struct compare_size : public vwrap<
            static_cast<int>(sizeof(L)) - static_cast<int>(sizeof(R))
        > {};

        // void は sizeof できないので、別途特殊化定義
        template <class L>
        struct compare_size<L, void> : public vwrap<int(1)> {};

        template <class R>
        struct compare_size<void, R> : public vwrap<int(-1)> {};

        template <>
        struct compare_size<void, void> : public vwrap<int(0)> {};
    }
    
    using compare_size = cbk<fn::compare_size, 2>;

    // compare_size と comparing_type により、comparing_size を定義
    using comparing_size = comparing_type<compare_size>;
}
```

## 比較可能な型の制約

比較の基準によっては、比較できない型が存在する場合があります。  
そのような場合に、任意の型に対して審議判定を行うメタ関数`Constraint`によって制約を行うことができます。

制約が不要な場合は、デフォルトで`tump::to_true`が指定されているため、三方比較を行うメタ関数`Compare`の指定だけで`tump::comparing_type`を使用することができます。

## 例

例として、下記ではテンプレート型に指定された、テンプレートパラメータパックの長さを比較するメタ関数を生成しています。

```cpp
#include <tuple>
#include <tump.hpp>

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

using list1 = tump::list<>;
using list2 = tump::list<int>;
using list3 = std::tuple<int, void>;
using list4 = tump::to_btree_t<tump::list<int, void, float>>;
using list5 = tump::list<int, void>;

static_assert(comparing_list_size::lt_v<list1, list2> == true);
static_assert(comparing_list_size::lt_v<list3, list5> == false);
static_assert(comparing_list_size::le_v<list2, list3> == true);
static_assert(comparing_list_size::le_v<list3, list5> == true);
static_assert(comparing_list_size::eq_v<list3, list4> == false);
static_assert(comparing_list_size::eq_v<list3, list5> == true);

static_assert(tump::eval<comparing_list_size::gt, list4, list3>::value == true);
static_assert(tump::eval<comparing_list_size::gt, list3, list5>::value == false);
static_assert(tump::eval<comparing_list_size::ge, list3, list2>::value == true);
static_assert(tump::eval<comparing_list_size::ge, list3, list5>::value == true);
static_assert(tump::eval<comparing_list_size::ne, list1, list2>::value == true);
static_assert(tump::eval<comparing_list_size::ne, list3, list5>::value == false);

// 下記は is_type_list の制約に抵触する型を比較しているため、
// コメントアウトを外すとコンパイルエラー
// comparing_list_size::lt_v<list1, int>;
// tump::eval<comparing_list_size::gt, void, list5>::value;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::to_true`|ref/metafunction/to_true}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::list`|ref/container/list}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
