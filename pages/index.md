---
title: TumpCppについて
overview: TumpCpp は、C++20以降を対象とした、テンプレートメタプログラミングを支援するヘッダオンリーライブラリです。
---

## はじめに

TumpCpp はテンプレートメタプログラミングに関数型のパラダイムの式を導入することで、表現力を向上させ、より直感的にコーディングを行うことを目的としたライブラリです。

特に、定義済みのメタ関数を使いまわせるような、下記の機能を提供することによって、メタプログラミングに関わるテンプレートクラスの定義や`<>`の記述量を削減します。  
それによって、テンプレートメタプログラミングの煩雑さを軽減し、本質的な型操作/型判定のコーディングに専念できます。

- メタ関数の第一級関数
- メタ関数への、テンプレートパラメータの部分適用
- メタ関数の合成やラムダ式
- 関数型のパラダイムの式を導入

## インストール

[GitHub のリポジトリ](https://github.com/TwilightUncle/tump-cpp)より、ソースを取得の上、任意の場所に展開します。

本ライブラリを使用するプロジェクトのインクルードディレクトリに、下記パスを追加します。  
※ソースの展開先を`path/to/tump-cpp`とする

- `path/to/tump-cpp/include`

そのうえで、ソースコードに下記を記載することですべての機能を呼び出すことができます。

- `#include <tump.hpp>`

本ライブラリの機能は名前空間`tump`に定義されています。

<!-- より詳細なインクルードパスの制御方法については、[{TUMP_COMMON_INCLUDEの項|ref/macro}]を参照ください。 -->

## 基本的な使い方

[{`tump::eval`|ref/expression/exp}]のテンプレートパラメータへメタ関数や型、演算子を記述することで、式として評価を行い、結果の型を返却します。

### 1.メタ関数の適用

メタ関数を評価する際は、左から順番にテンプレートパラメータの適用が行われます。

```cpp
#include <tump.hpp>

// std::is_same<int, int> と等価
using result_type = tump::eval<tump::is_same, int, int>;
static_assert(result_type::value == true);

int main() {}
```
  
適用可能なパラメータの数が、メタ関数の実行に足りない場合は、部分適用した状態のメタ関数が結果として返却されます。  
部分適用したメタ関数は別の式で、足りなかった分のパラメータを適用することで実行できます。

```cpp
#include <tump.hpp>

// is_same を実行するためには、2 つの型を適用する必要があるが、
// 足りない場合は部分適用した結果を返却
using is_int = tump::eval<tump::is_same, int>;

// 部分適用した結果のメタ関数は別の式で使用可能で、
// 残りの型を指定することで実行可能
static_assert(tump::eval<is_int, int>::value == true);
static_assert(tump::eval<is_int, float>::value == false);

int main() {}
```

なお、[{`tump::eval`|ref/expression/exp}]のテンプレートパラメータに指定可能なメタ関数は、第一級関数化されたものだけです。  
そのため、`<type_traits>`に定義されているようなメタ関数を直接指定してもコンパイルエラーとなります。

```cpp
#include <type_traits>
#include <tump.hpp>

// コンパイルエラーでビルド不可
using err = tump::eval<std::is_same, int, int>;
```

`<type_traits>`のほとんどのメタ関数は、同じ名称で名前空間`tump`に第一級関数化したものが定義されていますので、そちらを使用してください。  
しかし、未定義だったり、ユーザー定義のメタ関数を使用したい場合は、[{`tump::cbk`|ref/invocable/callback}]によって第一級関数化する必要があります。

```cpp
#include <type_traits>
#include <tump.hpp>

// cbk の 1 つ目のパラメータへメタ関数を、
// 2 つ目のパラメータへ、実行に必要なテンプレートパラメータの数を指定する
using callback_is_same = tump::cbk<std::is_same, 2>;
static_assert(tump::eval<callback_is_same, int, int>::value == true);

int main() {}
```

式の評価についてより詳しい内容は、[{`eval`のリファレンス|ref/expression/exp}]を参照ください。

### 2.演算子

TumpCpp では[{`tump::eval`|ref/expression/exp}]で使用可能な、いくつかの演算子が定義されています。  
演算子は、左右の型/メタ関数に対して所定の処理を行います。

```cpp
#include <tump.hpp>

// std::is_same<int, int>と等価
using result_type = tump::eval<int, tump::_eq, int>;
static_assert(result_type::value == true);

int main() {}
```

また、演算子の評価より関数適用のほうが優先的に行われ、式中の一通りの関数適用が完了したのち、演算子の評価が行われます。

```cpp
#include <tump.hpp>

using type1 = tump::eval<tump::make_unsigned, int>;
using type2 = tump::eval<tump::remove_const, const unsigned int>;
using result_type1 = tump::eval<type1, tump::_eq, type2>;

// 関数適用が優先的に行われるため、
// result_type1 と result_type2 の処理は等価
using result_type2 = tump::eval<
    tump::make_unsigned, int,
    tump::_eq,
    tump::remove_const, const unsigned int
>;
static_assert(result_type1::value == true);
static_assert(result_type2::value == true);

int main() {}
```

なお、演算子にも優先順位や結合性の方向が設定され、評価順序が異なりますが詳細は[{演算子の項|ref/operator}]を参照してください。

## 動作確認環境

C++20を有効にした状態の、下記の環境/コンパイラにおいてコンパイルし、動作を確認しています。

- Windows11
    - Visual Studio 2022 付属の VC++
- ubuntu 22.04 (Docker)
    - GCC: 10, 11, 12
    - Clang: 12, 13, 14
