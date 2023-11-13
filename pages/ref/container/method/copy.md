---
title: count_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList Src, TypeList Dest>
        requires (!is_empty_v<Src>)
        using copy = ...;
    }

    // 第一級関数化
    using copy = cbk<fn::copy, 2>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeList Src, TypeList Dest>
    using copy_t = typename fn::copy<Src, Dest>::type;
}
```

### パラメータ

- Src - [{`tump::TypeList`|ref/invocable/is_type_list}]で真と判定される型。空のリストを指定できない。
- Dest - [{`tump::TypeList`|ref/invocable/is_type_list}]で真と判定される型。

## 概要

`tump::copy`は、リスト`Dest`の中身を、リスト`Src`が持つパラメータパックに置き換えます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<std::vector<int>, char>;
using list2 = std::tuple<int, float, A>;
using list3 = tump::make_empty_t<list2>;

static_assert(std::is_same_v<
    tump::copy_t<list2, list1>,
    tump::list<int, float, A>
> == true);
static_assert(tump::eval<
    tump::copy, list1, list3,
    tump::_eq,
    std::tuple<std::vector<int>, char>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/invocable/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::is_empty`|ref/container/method/is_empty}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
