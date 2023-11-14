---
title: replace_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, class NewType, TypeList List>
        using replace_if = ...;
    }

    // 第一級関数化
    using replace_if = cbk<fn::replace_if, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, class NewType, TypeList List>
    using replace_if_t = typename fn::replace_if<Pred, NewType, List>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- NewType - 任意の型
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::replace_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、パラメータ`Pred`を適用した結果真と判定される全ての要素を、パラメータ`NewType`で置き換えます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, int>;
using list2 = std::tuple<short, float, A, std::vector<int>, double>;

// list1 の 算術型 を void で置き換える
static_assert(std::is_same_v<
    tump::replace_if_t<tump::is_arithmetic, void, list1>,
    tump::list<void, void, void, std::vector<int>, void>
> == true);

// list2 には const 就職された型が存在しないため、内容に特に変化なし
static_assert(tump::eval<
    tump::replace_if, tump::is_const, char, list2,
    tump::_eq,
    list2
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::is_arithmetic`|ref/metafunction/std}]
- [{`tump::is_const`|ref/metafunction/std}]
