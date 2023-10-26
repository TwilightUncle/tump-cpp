---
title: 比較演算子 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _eq = _op<is_same<>, e_op_priority::_4>;
    using _ne = _op<is_not_same, e_op_priority::_4>;
}
```

### _eq

- 結合性 : 非結合
- 優先度 : 4
- 左オペランド : 任意の型
- 右オペランド : 任意の型
- 機能 : 左右のオペランドの型が一致するとき真

### _ne

- 結合性 : 非結合
- 優先度 : 4
- 左オペランド : 任意の型
- 右オペランド : 任意の型
- 機能 : 左右のオペランドの型が異なるとき真

## 概要

`tump::_eq`は`==`演算子、`tump::_ne`は`!=`演算子と同じように機能し、左右のオペランドが一致するかどうかの比較を行います。

## 例

```cpp
#include <tump.hpp>

static_assert(tump::eval<int, tump::_eq, int>::value == true);
static_assert(tump::eval<int, tump::_eq, float>::value == false);
static_assert(tump::eval<int, tump::_ne, float>::value == true);
static_assert(tump::eval<int, tump::_ne, int>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::is_same`|ref/metafunction/std}]
- [{`tump::is_not_same`|ref/metafunction/std}]
