---
title: map - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, Invocable F, TypeList List>
        struct map_if {};
    }

    // 第一級関数化
    using map_if = cbk<fn::map_if, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, Invocable F, TypeList List>
    using map_if_t = typename fn::map_if<Pred, F, List>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- F - [{`tump::Invocable`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::map_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、メタ関数`Pred`を適用した結果真となる全ての要素に対して、メタ関数`F`を適用するメタ関数です。  
`F`は 1 つ以上の引数を持つ全てのメタ関数が使用可能で、2 つ以上の引数を持つメタ関数の場合は、部分適用が行われます。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, char, long, void>;
using list2 = std::tuple<int, float, char, double, long>;

// 整数型のみ、符号なしに変更する
static_assert(std::is_same_v<
    tump::map_if_t<tump::is_integral, tump::make_unsigned, list1>,
    tump::list<unsigned int, float, unsigned char, unsigned long, void>
> == true);

// 浮動小数点型のみ定数に変更する
static_assert(tump::eval<
    tump::map_if, tump::is_floating_point, tump::add_const, list2,
    tump::_eq,
    std::tuple<int, const float, char, const double, long>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::make_unsigned`|ref/metafunction/std}]
- [{`tump::add_const`|ref/metafunction/std}]
