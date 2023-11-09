---
title: 関数適用の演算子 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _apply = _op<apply<>, e_op_priority::r_0>;
}
```

### _apply

- 結合性 : 右結合
- 優先度 : 0
- 左オペランド : 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- 右オペランド : 任意の型
- 機能 : 左オペランドのメタ関数を、右オペランドへ適用

## 概要

`tump::_apply`は左オペランドのメタ関数を、右オペランドの型に適用する機能を持ち、評価されるタイミングが最も遅い演算子です。

## 使い方

[{`tump::eval`|ref/expression/exp}]で記述された式において、メタ関数の適用は自動的に行われます。  
そのため、`tump::_apply`をメタ関数の適用目的のみで使用することはありません。

`tump::_apply`を使う目的は、自動的に行われる関数適用と、`tump::_apply`の評価の優先順位の違いにあります。

自動的に行われるメタ関数の適用は、式の左側から、演算子の評価よりも先におこなわれます。  
一方で、`tump::_apply`の評価の優先順位は最も低く、式の右側から評価される動作となり、順序が真逆です。  
つまり、メタ関数の適用を行う際に、`tump::_apply`を使うことで、`tump::_apply`の左右のオペランドの全ての評価が完了するまで、関数適用を遅らせることができます。

上記を応用し、関数適用のタイミングを遅らせることで、式の中で行われる評価の順序を制御することが可能です。

## 例

```cpp
#include <tump.hpp>

// _apply を用いない場合。
// 左から順番に is_same を適用するため、case1 の式は、
// add_const と int を比較した結果異なることから、std::false_type が返却される。
using case1 = tump::eval<tump::is_same, tump::add_const, int>;
static_assert(case1::value == false);

// _apply を用いた場合。
// case2 の式は、is_same と add_const の間に _apply をはさむことにより、
// int への add_const の適用が最初に行われる。
// 結果、is_same が const int を部分適用したメタ関数が返却される
using case2 = tump::eval<tump::is_same, tump::_apply, tump::add_const, int>;
static_assert(tump::eval<case2, const int>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::apply`|ref/invocable/apply}]
- [{`tump::add_const`|ref/metafunction/std}]
- [{`tump::is_same`|ref/metafunction/std}]
