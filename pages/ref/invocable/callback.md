---
title: callback/cbk - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <
        template <class...> class MetaFunc,
        unsigned int ArgsSize = 0
    >
    struct callback;

    template <
        template <class...> class MetaFunc,
        unsigned int ArgsSize = 0
    >
    using cbk = callback<MetaFunc, ArgsSize>;
}
```

## 概要

テンプレートクラスであるメタ関数を、型の文脈で扱えるように第一級関数化します。  
`tump::cbk`は`tump::callback`のエイリアスであり、使い方も同様です。

## 使い方

1 つ目のパラメータ`MetaFunc`にはテンプレートクラスであるメタ関数を指定します。  
2 つ目のパラメータ`ArgsSize`には、`MetaFunc`に指定したメタ関数が必要とするパラメータの数を指定します。

特に、[{`tump::exp`/`tump::eval`|ref/expression/exp}]や、[{`tump::apply`|ref/invocable/apply}]で利用したいメタ関数については、メタ関数について部分適用を行うか、実行するかについて`ArgsSize`をみて判定するため、必ず設定する必要があります。

デフォルトのまま、`ArgsSize`へ`0`を指定した場合は、部分適用が行われず、最初の適用時点でメタ関数が実行されます。  
そのため、引数の数とメタ関数が必要とするパラメータの数が異なる場合は、コンパイルエラーとなります。

なお、標準ライブラリ`<type_traits>`で定義されているメタ関数および、TumpCpp で定義されているメタ関数のほとんどは、名前空間`tump`直下に`tump::callback`の適用により第一級関数化された状態のものが定義されています。  
ユーザー定義のメタ関数や、可変長引数で実行に必要なパラメータの数が定まっていないメタ関数を第一級関数化する用途で、`tump::callback`を利用することになると思われます。

また、テンプレートパラメータ`MetaFunc`には、メンバ型`type`または、コンパイル時評価可能なメンバ定数`value`が定義されているテンプレートクラスを指定しなければいけません。

## 例

```cpp
#include <type_traits>
#include <tump.cpp>

// std::is_same は 2 つのパラメータを受け取り、比較するメタ関数のため、
// ArgsSize に 2 を指定する
using callback_is_same1 = tump::callback<std::is_same, 2>;

// callback_is_same1 と等価
using callback_is_same2 = tump::cbk<std::is_same, 2>;

// 実行に必要なパラメータが定まっていないメタ関数は任意の数値を指定してもエラーとはならない
// 下記は 3 つの std::bool_constant で論理和を計算する
using callback_or_3 = tump::cbk<std::conjuction, 3>;

// 第一級関数化したメタ関数は 式の中で使用できるようになる
static_assert(tump::eval<callback_is_same1, int, int>::value == true);
static_assert(tump::eval<callback_is_same2, int, int>::value == true);
static_assert(tump::eval<callback_or_3, std::false_type, std::true_type, std::false_type>::value == true);
static_assert(tump::eval<callback_or_3, std::false_type, std::false_type, std::false_type>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
