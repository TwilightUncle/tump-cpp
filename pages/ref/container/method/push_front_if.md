---
title: push_front_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List, class... Types>
        using push_front_if = ...;
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 3>
    requires (ArgsSize > 1)
    using push_front_if = cbk<fn::push_front_if, ArgsSize>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, TypeList List, class... Types>
    using push_front_if_t = typename fn::push_front_if<Pred, List, Types...>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型
- Types - 可変長引数。任意の数の型

## 概要

`tump::push_front_if`は、テンプレートパラメータ`List`の先頭へ、パラメータパック`Types`のうち、`Pred`を適用した結果、真となる型のみを挿入するメタ関数です。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float>;
using list2 = std::tuple<int, float>;

// is_integral を double に適用した結果は偽となるため、リストに対して変更は行われない
static_assert(std::is_same_v<tump::push_front_if_t<tump::is_integral, list1, double>, list1> == true);

// is_integral を long に適用した結果は真となるため、リストに追加される
static_assert(std::is_same_v<tump::push_front_if_t<tump::is_integral, list1, long>, tump::list<long, int, float>> == true);

static_assert(tump::eval<
    tump::push_front_if<4>, tump::is_integral, list2, char, double,
    tump::_eq,
    std::tuple<char, int, float>
>::value == true);
static_assert(tump::eval<
    tump::push_front_if<6>, tump::is_integral, list2, char, double, short, float,
    tump::_eq,
    std::tuple<char, short, int, float>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::is_integral`|ref/metafunction/std}]
