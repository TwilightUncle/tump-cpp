---
title: リスト要素の含有判定 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _elem = _op<exists, e_op_priority::_4>;
    using _not_elem = _op<not_exists, e_op_priority::_4>;
}
```

### _elem

- 結合性 : 非結合
- 優先度 : 4
- 左オペランド : 任意の型
- 右オペランド : 型のパラメータパックを持つテンプレート型
- 機能 : 左ぺランドの型が右オペランドのパラメータパックに含まれるか判定

### _not_elem

- 結合性 : 非結合
- 優先度 : 4
- 左オペランド : 任意の型
- 右オペランド : 型のパラメータパックを持つテンプレート型
- 機能 : 左ぺランドの型が右オペランドのパラメータパックに含まれないか判定

## 概要

`tump::_elem`は、 左ぺランドの型が右オペランドのパラメータパックに含まれるか判定する演算子です。  
`tump::_not_elem`は、`tump::_elem`と同様のオペランドをとりますが、反対の結果になります。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

static_assert(tump::eval<int, tump::_elem, tump::list<float, int, void, double>>::value == true);
static_assert(tump::eval<int, tump::_elem, tump::list<float, char, void, double>>::value == false);
static_assert(tump::eval<int, tump::_elem, std::tuple<float, int, void, double>>::value == true);
static_assert(tump::eval<int, tump::_elem, std::tuple<float, char, void, double>>::value == false);

static_assert(tump::eval<int, tump::_not_elem, tump::list<float, int, void, double>>::value == false);
static_assert(tump::eval<int, tump::_not_elem, tump::list<float, char, void, double>>::value == true);
static_assert(tump::eval<int, tump::_not_elem, std::tuple<float, int, void, double>>::value == false);
static_assert(tump::eval<int, tump::_not_elem, std::tuple<float, char, void, double>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::list`|ref/container/list}]
- [{`tump::exists`|ref/container/method/exists}]
- [{`tump::not_exists`|ref/container/method/exists}]
