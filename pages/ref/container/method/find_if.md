---
title: find_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, TypeList List>
        using find_if = ...;
    }

    // 第一級関数化
    using find_if = cbk<fn::find_if, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> F, TypeList List>
    using find_if_t = typename fn::find_if<F, List>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::find_if`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Pred`のメタ関数を適用した結果、真と判定されるような最初の型を取得します。

該当する型が見つからなかった場合、`tump::mp_null_t`を返却します。

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

static_assert(std::is_same_v<tump::find_if_t<tump::is_integral, list1>, int> == true);
static_assert(std::is_same_v<tump::find_if_t<tump::is_floating_point, list2>, float> == true);
static_assert(std::is_same_v<tump::find_if_t<tump::to_true, list3>, tump::mp_null_t> == true);
static_assert(std::is_same_v<tump::find_if_t<tump::is_integral, list4>, char> == true);

static_assert(tump::eval<tump::find_if, tump::is_type_list, list1, tump::_eq, std::vector<int>>::value == true);
static_assert(tump::eval<tump::find_if, tump::is_void, list2, tump::_eq, tump::mp_null_t>::value == true);
static_assert(tump::eval<tump::find_if, tump::is_type_list, list4, tump::_eq, std::vector<int>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
- [{`tump::to_true`|ref/metafunction/to_true}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
- [{`tump::is_void`|ref/metafunction/std}]
