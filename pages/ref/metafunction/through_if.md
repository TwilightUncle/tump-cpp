---
title: through_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, class T, class Default>
        struct through_if {};
    }

    // 第一級関数化
    using through_if = cbk<fn::through_if, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, class T, class Default>
    using through_if_t = typename fn::through_if<Pred, T, Default>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- T - 任意の型
- Default - 任意の型

## 概要

`tump::through_if`は、型`T`を`Pred`に食わせた結果、真と判定された際はそのまま`T`を、偽と判定された際は`Default`を返却するメタ関数です。

## 例

```cpp
#include <tump.hpp>

static_assert(std::is_same_v<tump::through_if_t<tump::is_floating_point, double, float>, double> == true);
static_assert(std::is_same_v<tump::through_if_t<tump::is_floating_point, char, float>, float> == true);

// 整数型はそのまま、整数型以外は int に変換するメタ関数作成
using my_func = tump::eval<
    tump::flip,
    tump::exp<
        tump::through_if,
        tump::is_integral
    >,
    int
>;

static_assert(tump::eval<my_func, long long, tump::_eq, long long>::value == true);
static_assert(tump::eval<my_func, float, tump::_eq, int>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
