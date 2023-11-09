---
title: count_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List>
        using count_if = ...;
    }

    // 第一級関数化
    using count_if = cbk<fn::count_if, 2>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, TypeList List>
    constexpr auto count_if_v = fn::count_if<Pred, List>::value;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::count_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Pred`のメタ関数を適用した結果、真と判定されるようなパラメータの数を数えます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;
using list3 = tump::make_empty_t<std::tuple<int>>;
using list4 = tump::to_btree_t<list1>;

static_assert(tump::count_if_v<tump::is_integral, list1> == 2);
static_assert(tump::count_if_v<tump::is_integral, list2> == 1);
static_assert(tump::count_if_v<tump::is_integral, list3> == 0);
static_assert(tump::count_if_v<tump::is_integral, list4> == 2);

static_assert(tump::eval<tump::count_if, tump::is_arithmetic, list1>::value == 3);
static_assert(tump::eval<tump::count_if, tump::is_arithmetic, list2>::value == 3);
static_assert(tump::eval<tump::count_if, tump::is_arithmetic, list3>::value == 0);
static_assert(tump::eval<tump::count_if, tump::is_arithmetic, list4>::value == 3);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_arithmetic`|ref/metafunction/std}]
