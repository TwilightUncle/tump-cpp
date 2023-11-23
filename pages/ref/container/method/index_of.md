---
title: index_of - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class Search, TypeList List>
        using index_of = ...;
    }

    // 第一級関数化
    using index_of = cbk<fn::find_if, 2>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class Search, TypeList List>
    constexpr auto index_of_v = fn::index_of<Search, List>::value;
}
```

### パラメータ

- Search - 任意の型
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::index_of`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、テンプレートパラメータ`Search`を最初に見つけた位置を整数で返却します。

該当する型が見つからなかった場合、結果の値は`-1`となります。

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

static_assert(tump::index_of_v<float, list1> == 1);
static_assert(tump::index_of_v<double, list1> == -1);

static_assert(tump::eval<tump::index_of, std::vector<int>, list2>::value == 3);
static_assert(tump::eval<tump::index_of, long long, list2>::value == -1);
static_assert(tump::eval<tump::index_of, int, list3>::value == -1);
static_assert(tump::eval<tump::index_of, void, list4>::value == 0);
static_assert(tump::eval<tump::index_of, std::vector<int>, list4>::value == 4);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{バイナリツリー|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
