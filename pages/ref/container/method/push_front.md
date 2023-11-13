---
title: push_front - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List, class... Types>
        using push_front = ...;
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using push_front = cbk<fn::push_front, ArgsSize>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeList List, class... Types>
    using push_front_t = typename fn::push_front<List, Types...>::type;
}
```

### パラメータ

- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型
- Types - 可変長引数。任意の数の型

## 概要

`tump::push_front`は、テンプレートパラメータ`List`の先頭へ、パラメータパック`Types`を挿入するメタ関数です。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float>;
using list2 = std::tuple<int, float>;

static_assert(std::is_same_v<tump::push_front_t<list1, double>, tump::list<double, int, float>> == true);
static_assert(tump::eval<tump::push_front<3>, list2, char, double, tump::_eq, std::tuple<char, double, int, float>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
