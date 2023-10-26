---
title: 関数の合成の演算子 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _dot = _op<compose<>, e_op_priority::r_9>;
}
```

### _dot

- 結合性 : 右結合
- 優先度 : 9
- 左オペランド : 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- 右オペランド : 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- 機能 : 左右のオペランドのメタ関数を合成する。

## 概要

`tump::_dot`は左右のオペランドのメタ関数を合成する演算子です。  
メタ関数の合成についての詳細は、[{`tump::compose`|ref/invocable/compose}]を参照ください。

## 例

```cpp
#include <tump.hpp>

// 下記 case1 ~ case3 は全て同じ結果となります

// exp でくくることで、 make_unsigned の適用を先に行い、
// その結果を add_const する。
using case1 = tump::eval<tump::add_const, tump::exp<tump::make_unsigned, int>>;

// _apply 演算子により、add_const の評価を遅らせ、
// make_unsigned を先に評価する
using case2 = tump::eval<tump::add_const, tump::_apply, tump::make_unsigned, int>;

// add_const と make_unsigned を合成し、合成結果のメタ関数を int に適用する。
// 適用に _apply を用いているのは、デフォルトの関数適用の優先度が演算子より高いため。
// _apply を記載しないと、(make_unsigned, int) の評価が関数の合成より先におこなわれてしまう。
using case3 = tump::eval<tump::add_const, tump::_dot, tump::make_unsigned, tump::_apply, int>;

static_assert(std::is_same_v<case1, const unsigned int> == true);
static_assert(std::is_same_v<case2, const unsigned int> == true);
static_assert(std::is_same_v<case3, const unsigned int> == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::compose`|ref/invocable/compose}]
- [{`tump::add_const`|ref/metafunction/std}]
- [{`tump::make_unsigned`|ref/metafunction/std}]
