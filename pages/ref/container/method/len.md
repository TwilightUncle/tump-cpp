---
title: len - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList T>
        struct len {};
    }

    // 第一級関数化
    using len = cbk<fn::len, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    constexpr auto len_v = fn::len<List>::value;
}
```

### パラメータ

- T - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::len`は、受け取ったパラメータ`T`が保持する、テンプレートパラメータパックの長さを取得するメタ関数です。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

using list1 = tump::list<int, float>;
using list2 = tump::vlist<int(0), float(1), nullptr>;
using list3 = std::vector<int>;
using list4 = tump::make_empty_t<std::tuple<int>>;
using list5 = tump::vlist<>;

static_assert(tump::len_v<list1> == 2);
static_assert(tump::len_v<list2> == 3);
static_assert(tump::len_v<list3> == 2);
static_assert(tump::eval<tump::len, list4>::value == 0);
static_assert(tump::eval<tump::len, list5>::value == 0);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
