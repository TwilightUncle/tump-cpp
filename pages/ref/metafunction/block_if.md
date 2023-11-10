---
title: block_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<1> Pred, class T, class Default>
        struct block_if {};
    }

    // 第一級関数化
    using block_if = cbk<fn::block_if, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<1> Pred, class T, class Default>
    using block_if_t = typename fn::block_if<Pred, T, Default>::type;
}
```

### パラメータ

- Pred - [{`tump::InvocableArgN<1>`|ref/invocable/invocable}]で真と判定されるメタ関数
- T - 任意の型
- Default - 任意の型

## 概要

`tump::block_if`は、型`T`を`Pred`に食わせた結果、偽と判定された際はそのまま`T`を、真と判定された際は`Default`を返却するメタ関数です。

## 例

```cpp
#include <tump.hpp>

static_assert(std::is_same_v<tump::block_if_t<tump::is_floating_point, double, int>, int> == true);
static_assert(std::is_same_v<tump::block_if_t<tump::is_floating_point, char, int>, char> == true);

// int を許さないメタ関数作成
using my_func = tump::eval<
    tump::flip,
    tump::exp<
        tump::block_if,
        tump::is_integral
    >,
    void
>;

static_assert(tump::eval<my_func, long long, tump::_eq, void>::value == true);
static_assert(tump::eval<my_func, float, tump::_eq, float>::value == true);

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
