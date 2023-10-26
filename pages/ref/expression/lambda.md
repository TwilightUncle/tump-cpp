---
title: lambda - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class FormalArgList, class Expression>
    using lambda = ...;

    template <class... Types>
    struct lambda_args;
}
```

## 概要

ラムダ式(無名関数)として、第一級関数化したメタ関数を生成します。  

## 使い方

`tump::lambda`のテンプレートパラメータ`FormalArgList`には仮引数リスト、テンプレートパラメータ`Expression`には式を指定します。  

`FormalArgList`には`tump::lambda_args`を通して仮引数を指定します。  
`tump::lambda_args`のパラメータパックと同じ型が、`Expression`に指定した式の中で出現した場合、ラムダ式から生成されたメタ関数を適用した型で置換されます。  
そのうえで、`Expression`の内容が式として評価されます。  

`Expression`には[{`tump::exp`|ref/expression/exp}]により式を記述します。  
※[{`tump::eval`|ref/expression/exp}]は仮引数周りの置換処理を行う前に、評価が完了してしまうため、ラムダ式で使用することはできません。

なお、TumpCpp では、`tump::lambda_args`の仮引数として使用するための下記の型が定義されています。

- `_arg1`
- `_arg2`
- `_arg3`
- `_arg4`
- `_argx`
- `_argy`
- `_argz`
- `_arga`
- `_argb`
- `_argc`

## 例

```cpp
#include <tump.hpp>

// ラムダ式により、2 引数のメタ関数を生成
using my_func = tump::lambda<
    tump::lambda_args<tump::_arg1, tump::_arg2>,
    tump::exp<
        tump::_arg1, tump::_eq, int,
        tump::_and,
        tump::_arg2, tump::_ne, double
    >
>;

// epx の _arg1 が long で、_arg2 が double で置き換えられた後、評価される
static_assert(tump::eval<my_func, long, double>::value == false);

// exp の _arg1 が int で、_arg2 が float で置き換えられた後、評価される
static_assert(tump::eval<my_func, int, float>::value == true);

int main() {}
```

## lambda_argsの注意点

`tump::lambda_args`のパラメータパックとして指定された型は、`Expression`に同じ型の記載がある場合、生成後のメタ関数の評価時に、全て引数で置き換えられます。  
しかし、`tump::lambda_args`にはあらゆる型を指定することができるため、`Expression`の式中で意図しない引数の置換が起きてしまう可能性があります。

例えば、下記のように`tump::lambda_args`に`int`型が指定されていた場合、`tump::exp`の内部で指定されていた`int`型はすべて、生成後のメタ関数の評価時に引数で置換されてしまいます。  
指定する引数の内容によっては、別の引数の内容にまで影響を及ぼすことがありますので、ご注意ください。

```cpp
#include <tump.hpp>

using my_func = tump::lambda<
    tump::lambda_args<int, tump::_arga>,
    tump::exp<int, tump::_eq, tump::_arga>
>;

// exp の int が long で、_arga が double で置き換えられた後、評価される
static_assert(tump::eval<my_func, long, double>::value == false);

// 実装における計算順序の都合上、
// exp の _arga が int で、_arga 置換後の int も含めた int が double で置き換えられた後、評価される
static_assert(tump::eval<my_func, double, int>::value == true);

int main() {}
```

特定が難しい不具合となる可能性があるため、下記のような型以外の、仮引数以外の用途でも使う型を、仮引数として使用しないことを推奨します。

- TumpCpp で定義済みの仮引数用の型
- 新たに仮引数専用の型を用意

```cpp
#include <tump.hpp>

struct my_arg_t {};

using my_func = tump::lambda<
    tump::lambda_args<my_arg_t, tump::_arga>,
    tump::exp<my_arg_t, tump::_eq, tump::_arga>
>;

// exp の 対応する位置の仮引数が引数で置き換えられた後、評価される
static_assert(tump::eval<my_func, long, double>::value == false);
static_assert(tump::eval<my_func, long, long>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::exp`|ref/expression/exp}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::_ne`|ref/operator/compare}]
- [{`tump::_and`|ref/operator/logical}]
