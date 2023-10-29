---
title: is_empty - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class T>
        struct is_empty {};
    }

    // 第一級関数化
    using is_empty = cbk<fn::is_empty, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class T>
    constexpr auto is_empty_v = fn::is_empty<T>::value;
}
```

### パラメータ

- T - 任意の型

## 概要

指定のテンプレートパラメータ`T`が空か判定し、空の場合は`std::true_type`、それ以外の場合は`std::false_type`を継承します。

下記のような型が空と判定されます。

- [{`tump::make_empty`|ref/container/method/make_empty}]で生成された型
- [{`tump::list<>`|ref/container/list}]
- [{`tump::vlist<>`|ref/container/vlist}]

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using not_empty1 = tump::list<int, float>;
using not_empty2 = tump::vlist<int(0), float(1), nullptr>;
using not_empty3 = int;
using not_empty4 = std::tuple<int>;

using empty1 = tump::list<>;
using empty2 = tump::vlist<>;
using empty3 = tump::make_empty_t<not_empty1>;
using empty4 = tump::make_empty_t<not_empty4>;

static_assert(tump::is_empty_v<not_empty1> == false);
static_assert(tump::is_empty_v<not_empty2> == false);
static_assert(tump::eval<tump::is_empty, not_empty3>::value == false);
static_assert(tump::eval<tump::is_empty, not_empty4>::value == false);

static_assert(tump::is_empty_v<empty1> == true);
static_assert(tump::is_empty_v<empty2> == true);
static_assert(tump::eval<tump::is_empty, empty3>::value == true);
static_assert(tump::eval<tump::is_empty, empty4>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/eval}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]