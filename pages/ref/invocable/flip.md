---
title: flip - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<2> F, class L, class R>
        using flip = invoke<F, R, L>;
    }

    // 第一級関数化
    using flip = cbk<fn::flip, 3>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<2> F,  class L, class R>
    using flip_t = typename fn::flip<F, L, R>::type;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<2> F,  class L, class R>
    constexpr auto flip_v = fn::flip<F, L, R>::value;
}
```

### パラメータ

- F - 第一級関数化した 2 引数を受け取るメタ関数。[{`tump::InvocableArgN<2>`|ref/invocable/invocable}]で真と判定されなければいけない。
- L - `F` の第二引数として渡す型。
- R - `F` の第一引数として渡す型。

## 概要

2 つの引数を受け取る、第一級関数化したメタ関数を、左右の引数を入れ替えた上で実行します。

## 使い方

TumpCpp では関数型のパラダイムの式を導入しており、関数適用は左側から行われます。  
そのため、部分適用を行った後に関数の合成を行うような際、先に適用しておきたい引数が右側にあるような場合でも、そのままでは左側の引数が先に適用されてしまいます。  
そこで、`flip`を用いて引数の順序を入れ替えることで、右側の引数を先に部分適用することが可能となります。

## 例

```cpp
#include <tump.hpp>

class Base {};
class Derived : public Base {};
class DerivedDerived : public Derived {};

// invoke と比較して、引数の順序が逆になる。
static_assert(tump::invoke_v<tump::is_base_of, Base, Derived> == true);
static_assert(tump::flip_v<tump::is_base_of, Derived, Base> == true);

// flip を用いてクラス Derived の基底クラスかどうか判定するメタ関数定義。
// is_base_of は左側に基底クラスを、右側に継承先のクラスを指定するが、
// flipにより引数の順序を入れ替えることで、先に継承先のクラスを部分適用している
using is_Derived_base = tump::eval<tump::flip, tump::is_base_of, Derived>;
static_assert(tump::eval<is_Derived_base, Base>::value == true);
static_assert(tump::eval<is_Derived_base, Derived>::value == true);
static_assert(tump::eval<is_Derived_base, DerivedDerived>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::invoke`|ref/invocable/invoke}]
- [{`tump::is_base_of`|ref/metafunction/std}]
