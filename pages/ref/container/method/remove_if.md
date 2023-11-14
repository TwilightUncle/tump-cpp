---
title: remove_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List>
        using remove_if = ...;
    }

    // 第一級関数化
    using remove_if = cbk<fn::remove_if, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, TypeList List>
    using remove_if_t = typename fn::remove_if<Pred, List>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::remove_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Pred`のメタ関数を適用した結果、真と判定されるような型を全て除去するメタ関数です。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;

static_assert(std::is_same_v<
    tump::remove_if_t<tump::is_integral, list1>,
    tump::list<float, void, std::vector<int>>
> == true);
static_assert(std::is_same_v<
    tump::remove_if_t<tump::is_floating_point, list2>,
    std::tuple<int, A, std::vector<int>>
> == true);

static_assert(tump::eval<
    tump::remove_if, tump::is_void, list1,
    tump::_eq,
    tump::list<int, float, std::vector<int>, char>
>::value == true);
static_assert(tump::eval<
    tump::remove_if, tump::is_arithmetic, list2,
    tump::_eq,
    std::tuple<A, std::vector<int>>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
- [{`tump::is_void`|ref/metafunction/std}]
- [{`tump::is_arithmetic`|ref/metafunction/std}]
