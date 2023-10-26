---
title: 論理演算子 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _or = _op<disjunction<>, e_op_priority::r_2>;
    using _and = _op<conjunction<>, e_op_priority::r_3>;
}
```

### _or

- 結合性 : 右結合
- 優先度 : 2
- 左オペランド : 任意の型
- 右オペランド : 任意の型
- 機能 : 論理和

### _and

- 結合性 : 右結合
- 優先度 : 3
- 左オペランド : 任意の型
- 右オペランド : 任意の型
- 機能 : 論理積

## 概要

`tump::_or`は論理和、`tump::_and`は論理積の演算子です。  
それぞれ、`std::true_type`を真、`std::false_type`を偽として評価します。

## 例

```cpp
#include <tump.hpp>

// _or の例。
// 一つだけ true_type と評価されるオペランドが含まれる。
static_assert(tump::eval<
    std::false_type, tump::_or,
    tump::is_integral, int, tump::_or,
    tump::is_pointer, int
>::value == true);

// _or の例。
// 全てのオペランドが、false_type と評価される場合。
static_assert(tump::eval<
    std::false_type, tump::_or,
    tump::is_integral, float, tump::_or,
    tump::is_pointer, int
>::value == false);

// _and の例。
// 一つでも false_type と評価されるオペランドが含まれる場合。
static_assert(tump::eval<
    std::true_type, tump::_and,
    tump::is_integral, int, tump::_and,
    tump::is_pointer, int
>::value == false);

// _and の例。
// 全てのオペランドが、true_type と評価される場合。
static_assert(tump::eval<
    std::true_type, tump::_and,
    tump::is_integral, int, tump::_and,
    tump::is_pointer, int*
>::value == true);

// _or と _and が混ざった例。
// _and の方が優先度が高く、先に評価される。
static_assert(tump::eval<
    std::false_type, tump::_or,
    tump::is_integral, int, tump::_and,
    tump::is_pointer, int*
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::disjunction`|ref/metafunction/std}]
- [{`tump::conjunction`|ref/metafunction/std}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_pointer`|ref/metafunction/std}]
