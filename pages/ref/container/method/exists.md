---
title: exists - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class Search, TypeList List>
        using exists = ...;
    }

    // 第一級関数化
    using exists = cbk<fn::exists, 2>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class Search, TypeList List>
    constexpr auto exists_v = fn::exists<Search, List>::value;
}
```

### パラメータ

- Search - 任意の型
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::exists`は、テンプレートパラメータ`List`が保持するパラメータパックの中に、テンプレートパラメータ`Search`が含まれているか判定を行うメタ関数です。

## 例

```cpp
#include <vector>
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = tump::make_empty_t<std::tuple<int>>;
using list3 = tump::to_btree_t<list1>;

static_assert(tump::exists_v<float, list1> == true);
static_assert(tump::exists_v<float, list2> == false);
static_assert(tump::exists_v<float, list3> == true);

static_assert(tump::eval<tump::exists, double, list1>::value == false);
static_assert(tump::eval<tump::exists, double, list3>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{バイナリツリー|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
