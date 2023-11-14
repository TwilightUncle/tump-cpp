---
title: filter - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List>
        using filter = ...;
    }

    // 第一級関数化
    using filter = cbk<fn::filter, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, TypeList List>
    using filter_t = typename fn::filter<Pred, List>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::filter`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Pred`のメタ関数を適用した結果、真と判定されるような型を抽出するメタ関数です。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;

static_assert(std::is_same_v<
    tump::filter_t<tump::is_integral, list1>,
    tump::list<int, char>
> == true);
static_assert(std::is_same_v<
    tump::filter_t<tump::is_floating_point, list2>,
    std::tuple<float, double>
> == true);

static_assert(tump::eval<
    tump::filter, tump::is_void, list1,
    tump::_eq,
    tump::list<void>
>::value == true);
static_assert(tump::eval<
    tump::filter, tump::is_arithmetic, list2,
    tump::_eq,
    std::tuple<int, float, double>
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
