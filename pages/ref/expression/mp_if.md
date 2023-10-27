---
title: mp_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class Cond, class T, class F>
        struct mp_if {};
    }

    // 第一級関数化
    using mp_if = cbk<fn::mp_if, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <MpCondition Cond, class T, class F>
    using mp_if_t = typename fn::mp_if<Cond, T, F>::type;
}
```

### パラメータ

- Cond - `std::bool_constant`を継承した型
- T - 任意の型
- F - 任意の型

## 概要

`tump::mp_if`は、三項演算子のように動作する条件分岐の式です。  
型パラメータ`Cond`が真と判定される際は、型パラメータ`T`に指定された型を、偽と判定された際は、型パラメータ`F`に指定された型を返却します。

なお、標準ライブラリにも似た機能を持つ`std::conditional`がありますが、`tump::mp_if`は以下の点が異なります。

- `std::conditional`は条件を非型パラメータとして受け取るが、`tump::mp_if`は`std::bool_constant`のような型で受け取る。
- `tump::mp_if`は全ての引数において、`tump::exp`による式を受け取った際に、評価結果を使用する

## 例

```cpp
#include <tump.hpp>

static_assert(std::is_same_v<tump::mp_if_t<std::true_type, int, double>, int> == true);
static_assert(std::is_same_v<tump::mp_if_t<std::false_type, int, double>, double> == true);

// exp による式は、あらかじめ評価を完了したうえで、
// 評価結果による判定や返却を行う
static_assert(std::is_same_v<tump::mp_if_t<
    tump::exp<int, tump::_eq, int>,
    tump::exp<tump::make_unsigned, int>,
    double
>, unsigned int> == true);

int main() {}
```

## 関連リンク

- [{`tump::exp`|ref/expression/exp}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::make_unsigned`|ref/metafunction/std}]
