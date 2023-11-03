---
title: is_unique - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // メタ関数定義
        template <TypeListOrValueList List>
        using is_unique = ...;
    }

    // 第一級関数化
    using is_unique = cbk<fn::is_unique, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class T>
    constexpr auto is_unique_v = fn::is_unique<T>::value;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::is_unique`は、`List`に指定された型が持つテンプレートパックに、重複がないことを判定するメタ関数です。

リストがが空の場合は真となります。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, int, double>;
using list3 = tump::vlist<int(1), long(2), int(1)>;
using list4 = tump::vlist<int(1), long(2), int(3), long(4)>;
using list5 = tump::make_empty_t<std::tuple<int>>;
using list6 = tump::vlist<>;

static_assert(tump::is_unique_v<list1> == true);
static_assert(tump::is_unique_v<list3> == false);
static_assert(tump::is_unique_v<list5> == true);

static_assert(tump::eval<tump::is_unique, list2>::value == false);
static_assert(tump::eval<tump::is_unique, list4>::value == true);
static_assert(tump::eval<tump::is_unique, list6>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
