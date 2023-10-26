---
title: invoke - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <Invocable F, class... Args>
        struct invoke;
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using invoke = callback<fn::invoke, ArgsSize>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <Invocable F, class... Args>
    using invoke_t = typename fn::invoke<F, Args...>::type;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <Invocable F, class... Args>
    constexpr auto invoke_v = fn::invoke<F, Args...>::value;
}
```

### パラメータ

- F - 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- Args - `F` の実行時に引数として渡す型テンプレートパラメータパック。
- ArgsSize - [{`tump::eval`|ref/expression/exp}]などの式で利用する際の、実行までに要する引数の固定。符号なし整数。

## 概要

第一級関数化したメタ関数に引数を渡して実行するメタ関数です。  
メタ関数`F`によって必要な引数が異なるため、`invoke`は可変引数のメタ関数です。

なお、`invoke`は部分適用を行わず、メタ関数を実行しようとします。
そのため、`F`の実行に必要な引数の数と、テンプレートパラメータパック`Args`の数が一致しない場合はコンパイルエラーとなります。

## 使い方

主に、高階関数であるメタ関数の実装に使用します。  

一応、第一級関数化のエイリアス宣言`tump::invoke`もありますが、[{`tump::eval`や`tump::exp`|ref/expression/exp}]では自動的に関数適用が行われるため、式の中での使用頻度は低いものと思われます。

## 例

```cpp
#include <type_traits>
#include <tump.cpp>

static_assert(tump::fn::invoke<tump::is_same, int, int>::value == true);
static_assert(tump::invoke_v<tump::is_floating_point, float> == true);
static_assert(std::is_same_v<tump::invoke_t<tump::add_const, int>, const int> == false);

// eval での使用
// tump::eval<tump::is_integral, int>::value == true と同様の結果
static_assert(tump::eval<tump::invoke<3>, tump::is_same, int, int>::value == true);

// 高階関数であるメタ関数の定義例
// T に Pred を適用した結果真となれば T を、偽となれば F を返却
template <tump::InvocableArgN<1> Pred, class T, class F>
struct block_if : public std::conditional<
    tump::invoke_v<Pred, T>,
    T,
    F
> {};

// block_if から、整数以外の型を全て int 型に変換するメタ関数定義
template <class T>
using to_integral_t = typename block_if<tump::is_integral, T, int>::type;

static_assert(std::is_same_v<to_integral_t<unsigned long>, unsigned long> == true);
static_assert(std::is_same_v<to_integral_t<float>, int> == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
- [{`tump::add_const`|ref/metafunction/std}]
- [{`tump::is_same`|ref/metafunction/std}]
- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
