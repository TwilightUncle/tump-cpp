---
title: リスト結合・要素追加 - TumpCpp リファレンス
---

```cpp
namespace tump {
    using _cons = _op<partial_apply<flip, push_front<>>, e_op_priority::r_5>;
    using _concat = _op<concat<>, e_op_priority::r_5>;
}
```

### _cons

- 結合性 : 右結合
- 優先度 : 5
- 左オペランド : 任意の型
- 右オペランド : 型のパラメータパックを持つテンプレート型
- 機能 : 左オペランドの型を右オペランドのパラメータパックの先頭に挿入する

### _concat

- 結合性 : 右結合
- 優先度 : 5
- 左オペランド : 型のパラメータパックを持つテンプレート型
- 右オペランド : 型のパラメータパックを持つ左オペランドと同じテンプレート型
- 機能 : 左右のオペランドのパラメータパックを結合する

## 概要

`tump::_cons`は、 左ぺランドの型を右オペランドのリストに追加する演算子です。  
`tump::_concat`は、左右のオペランドのリストを結合する演算子です。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

static_assert(std::is_same_v<
    tump::eval<int, tump::_cons, tump::list<float, double, char>>,
    tump::list<int, float, double, char>
> == true);
static_assert(std::is_same_v<
    tump::eval<int, tump::_cons, std::tuple<float, double, char>>,
    std::tuple<int, float, double, char>
> == true);

static_assert(std::is_same_v<
    tump::eval<tump::list<int, long>, tump::_concat, tump::list<float, double, char>>,
    tump::list<int, long, float, double, char>
> == true);
static_assert(std::is_same_v<
    tump::eval<std::tuple<int, long>, tump::_concat, std::tuple<float, double, char>>,
    std::tuple<int, long, float, double, char>
> == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::_op`|ref/operator/op}]
- [{`tump::list`|ref/container/list}]
- [{`tump::partial_apply`|ref/invocable/partial_apply}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::concat`|ref/metafunction/list_op/concat}]
- [{`tump::push_front`|ref/metafunction/list_op/push}]
