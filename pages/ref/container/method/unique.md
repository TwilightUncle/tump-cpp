---
title: unique - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List>
        struct unique {};
    }

    // 第一級関数化
    using unique = cbk<fn::unique, 1>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    using unique_t = typename fn::unique<List>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::unique`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、重複する要素を取り除きます。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, int, int, int>;
using list2 = std::tuple<int, float, int, double, char, double>;
using list3 = tump::vlist<int(1), char(1), long(2), int(1), char(3), long(2)>;

static_assert(std::is_same_v<
    tump::unique_t<list1>,
    tump::list<int>
> == true);
static_assert(tump::eval<
    tump::unique, list2,
    tump::_eq,
    std::tuple<int, float, double, char>
>::value == true);

// 非型パラメータのリストの場合、厳密な比較が行われる。
// 型と値ともに等しいもののみ重複しているとみなされる。
static_assert(tump::eval<
    tump::unique, list3,
    tump::_eq,
    tump::vlist<int(1), char(1), long(2), char(3)>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::_eq`|ref/operator/compare}]
