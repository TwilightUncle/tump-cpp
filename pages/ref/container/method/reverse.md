---
title: reverse - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List>
        struct reverse {};
    }

    // 第一級関数化
    using reverse = cbk<fn::reverse, 1>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    using reverse_t = typename fn::reverse<List>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::reverse`は、テンプレートパラメータ`List`が保持するパラメータパックの順番を反転します。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;
using list3 = tump::vlist<int(1), long(2), char(3)>;

static_assert(std::is_same_v<
    tump::reverse_t<list1>,
    tump::list<char, std::vector<int>, void, float, int>
> == true);
static_assert(tump::eval<
    tump::reverse, list2,
    tump::_eq,
    std::tuple<double, std::vector<int>, A, float, int>
>::value == true);
static_assert(tump::eval<
    tump::reverse, list3,
    tump::_eq,
    tump::vlist<char(3), long(2), int(1)>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::_eq`|ref/operator/compare}]
