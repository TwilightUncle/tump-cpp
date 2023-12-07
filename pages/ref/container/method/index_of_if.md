---
title: index_of_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List>
        using index_of_if = ...;
    }

    // 第一級関数化
    using index_of_if = cbk<fn::index_of_if, 2>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> F, TypeList List>
    constexpr auto index_of_if_v = fn::index_of_if<F, List>::value;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::index_of_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Pred`のメタ関数を適用した結果、真と判定されるような最初の要素の位置を整数で返却します。

該当する型が見つからなかった場合、`-1`を返却します。

[{`tump::find_if`|ref/container/method/find_if}]と似ていますが、`tump::find_if`は該当する型をそのまま返却、`tump::index_of_if`は該当する型の**位置**を返却する点が異なります。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, const double>;
using list3 = tump::make_empty_t<std::tuple<int>>;
using list4 = tump::to_bintree_t<list1>;

static_assert(tump::index_of_if_v<tump::is_integral, list1> == 0);
static_assert(tump::index_of_if_v<tump::is_type_list, list1> == 3);
static_assert(tump::index_of_if_v<tump::is_pointer, list1> == -1);
static_assert(tump::index_of_if_v<tump::is_integral, list4> == 1);

static_assert(tump::eval<tump::index_of_if, tump::is_floating_point, list2>::value == 1);
static_assert(tump::eval<tump::index_of_if, tump::is_const, list2>::value == 4);
static_assert(tump::eval<tump::index_of_if, tump::to_true, list3>::value == -1);
static_assert(tump::eval<tump::index_of_if, tump::is_type_list, list4>::value == 4);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{バイナリツリー|ref/container/bintree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_bintree`|ref/container/method/to_bintree}]
- [{`tump::to_true`|ref/metafunction/to_true}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
- [{`tump::is_pointer`|ref/metafunction/std}]
- [{`tump::is_const`|ref/metafunction/std}]
