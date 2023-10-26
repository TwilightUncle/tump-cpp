---
title: Invocable/InvocableArgN - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class T>
    concept Invocable = ...;

    template <class T, unsigned int ArgsSize>
    concept InvocableArgN = ...;
}
```

### パラメータ

- T - 検査対象の任意の型。
- ArgsSize - 引数の数について確認を行う

## 概要

第一級関数化されたメタ関数かどうか判定する制約です。  
`InvocableArgN`はメタ関数かどうかの判定に加え、より厳密に、メタ関数の実行に必要な引数の数も比較します。

## 使い方

型テンプレートパラメータに対する制約または、定数式上における型判定に使用します。

## 例

```cpp
#include <type_traits>
#include <tump.cpp>

using callback_is_same = tump::cbk<std::is_same, 2>;
using callback_is_int = tump::partial_apply<callback_is_same, int>;

// 第一級関数化されたメタ関数か判定
static_assert(tump::Invocable<callback_is_same> == true);
static_assert(tump::Invocable<callback_is_int> == true);
static_assert(tump::Invocable<int> == false);

// 第一級関数化されたメタ関数かの判定に加え、
// 実行に必要な引数の検査も実施
static_assert(tump::InvocableArgN<callback_is_same, 1> == false);
static_assert(tump::InvocableArgN<callback_is_int, 1> == true);
static_assert(tump::InvocableArgN<callback_is_same, 2> == true);
static_assert(tump::InvocableArgN<callback_is_int, 2> == false);

// コンセプトによる型制約
// 主に高階関数であるメタ関数の定義に使用
template <tump::Invocable Func>
struct tclass1 {};

template <tump::InvocableArgN<2> Func>
struct tclass2 {};

using class1 = tclass1<callback_is_same>;
using class2 = tclass1<callback_is_int>;
using class3 = tclass2<callback_is_same>;

// 下記は型制約に抵触するため、コメントアウトを外すとコンパイルエラー
// using error1 = tclass1<int>;
// using error2 = tclass2<callback_is_int>;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::callback`|ref/invocable/callback}]
