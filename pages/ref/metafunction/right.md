---
title: right - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class L, class R>
        struct right : public std::type_identity<L> {};
    }

    // 第一級関数化
    using right = cbk<fn::right, 2>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <class L, class R>
    using right_t = typename fn::right<L, R>::type;
}
```

### パラメータ

- L - 任意の型
- R - 任意の型

## 概要

`tump::right`は、引数として任意の型を 2 つ受け取り、必ず右側(第二引数)の型`R`を返却するメタ関数です。

形式的に 2 引数メタ関数を指定する必要があり、かつ、左側の引数を破棄したいような場合に使用することを想定しています。

## 例

```cpp
#include <tump.hpp>

// どのような型を渡しても真となる
static_assert(std::is_same_v<tump::right_t<int, float>, float> == true);
static_assert(tump::eval<tump::right, int, float, tump::_eq, float>::value == true);

// 引数を同じ型で全て埋めたうえで勝手に実行するメタ関数を定義
// 再帰による部分適用により、実装
template <tump::Invocable F, class FillType>
struct fill_apply : public tump::exp<
    std::conditional_t<
        tump::InvocableArgN<F, 1>,
        tump::right,
        tump::partial_apply<
            tump::flip,
            tump::cbk<fill_apply, 2>
        >
    >,
    FillType,
    tump::_apply,
    F, FillType
> {};

// std::is_same_v<int, int> と同じ
static_assert(fill_apply<tump::is_same, int>::type::value == true);

// std::conjunction_v<std::true_type, std::true_type, std::true_type, std::true_type> と同じ
static_assert(fill_apply<tump::conjunction<4>, std::true_type>::type::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::cbk`|ref/invocable/callback}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::partial_apply`|ref/invocable/partial_apply}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::_apply`|ref/operator/apply}]
