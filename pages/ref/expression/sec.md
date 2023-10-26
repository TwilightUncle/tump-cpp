---
title: sec - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class Term1, class Term2>
    using sec = ...;
}
```

## 概要

`tump::sec`は演算子の部分適用を行います。  
結果として、第一級関数化されたメタ関数が返却されます。

2 つあるテンプレートパラメータの片方に演算子を、もう一方に部分適用するオペランドの型(第一級関数化されたメタ関数を含む)を指定します。  
演算子と演算子以外の型をどちらに指定するかによって、下記のとおり、左右どちらのオペランドが部分適用されるか異なります。

- Term1 に演算子、Term2 に演算子以外を指定 : 演算子の右オペランドを部分適用
- Term2 に演算子、Term1 に演算子以外を指定 : 演算子の左オペランドを部分適用

なお、`tump::sec`による演算子の部分適用を行った時点で、メタ関数として解釈されるため、該当の演算子に設定された評価順序は無視されます。

## 例

```cpp
#include <tump.hpp>

// case1, case2, case3 全て同じ処理
using case1 = tump::eval<tump::is_integral, int>;
using case2 = tump::eval<tump::sec<tump::_apply, int>, tump::is_integral>;
using case3 = tump::eval<tump::sec<tump::is_integral, tump::_apply>, int>;

static_assert(case1::value == true);
static_assert(std::is_same_v<case2, case1>);
static_assert(std::is_same_v<case3, case1>);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::_apply`|ref/operator/apply}]
