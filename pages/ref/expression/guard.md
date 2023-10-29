---
title: guard - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class Cond, class T>
    struct if_clause {};
    
    template <class T>
    using otherwise = if_clause<std::true_type, T>;

    namespace fn {
        // 大元のメタ関数定義
        template <class... Clauses>
        struct guard {};
    }

    // 第一級関数化
    template <std::size_t ArgsSize = 2>
    using guard = cbk<fn::guard, ArgsSize>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <class... Clauses>
    using guard_t = typename fn::guard<Clauses...>::type;
}
```

### クラス・パラメータ

- if_clause - `guard`に指定する if 節。`if-else if-else`の`if`や`else`に該当
- otherwise - `guard`に指定する otherwise 節。`if-elseif-else`の`else`や、`switch`の`default`に該当
- Cond - `std::bool_constant`を継承した型
- T - 任意の型
- ArgsSize - `guard` に指定する`if_clause`や`otherwise`の数を指定
- Clauses - テンプレートパラメータパック。`if_clause`と`otherwise`のみ指定可能

## 概要

`tump::guard`は、`if-elseif-else`のような任意数の条件分岐を行うメタ関数です。  
`tump::guard`が受け取る、型テンプレートパラメータパック`Clauses`に指定可能な型は、`tump::if_clause`と`tump::otherwise`のみです。  
※`tump::otherwise`も実装上は`tump::if_clause`の型エイリアスであり、厳密には`tump::if_clause`とその別名のみ`Clauses`に指定可能。

`tump::guard`を実行する際、`Clauses`は先頭から順番に評価されます。  
`Clauses`の評価中最初に見つかった、パラメータ`Cond`が真と評価された`tump::if_clause`または`tump::otherwise`の、パラメータ`T`が`tump::guard`の結果として返却されます。

`Clauses`の一番最後に`tump::otherwise`を指定することで、全ての`tump::if_clause`に該当しない場合の結果を指定することができます。

テンプレートパラメータ`Cond`および`T`には、[{`tump::exp`|ref/expression/exp}]による式も指定可能です。  
[{`tump::exp`|ref/expression/exp}]を指定した際は、`tump::guard`を実行する際に、先に`tump::exp`が評価され、その結果を判定したり、返却します。

なお、`tump::if_clause`および`tump::otherwise`は**メタ関数ではありません**。  
あくまでも、`tump::guard`のパラメータ`Clauses`でしか利用できないテンプレートクラスとなりますので、ご注意ください。

## 例

```cpp
#include <tump.hpp>

// 符号なし整数、整数、浮動小数点、それ以外と型を判定し、
// それぞれの条件に合致した場合の型を返却。
template <class T>
using sample_guard1_t = tump::guard_t<
    tump::if_clause<std::is_unsigned<T>, unsigned int>,
    tump::if_clause<std::is_integral<T>, int>,
    tump::if_clause<std::is_floating_point<T>, float>,
    tump::otherwise<void>
>;

static_assert(std::is_same_v<sample_guard1_t<std::size_t>, unsigned int> == true);
static_assert(std::is_same_v<sample_guard1_t<char>, int> == true);
static_assert(std::is_same_v<sample_guard1_t<double>, float> == true);
static_assert(std::is_same_v<sample_guard1_t<std::tuple<int>>, void> == true);

// ラムダ式における guard の条件分岐の使用例。
// if_clause や otherwise のパラメータに指定された exp は先に評価される。
using sample_guard2 = tump::lambda<
    tump::lambda_args<tump::_arg1, tump::_arg2>,
    tump::exp<
        tump::guard<3>,
        // 2 つの引数が等しい場合、std::true_type を返却
        tump::if_clause<
            std::is_same<tump::_arg1, tump::_arg2>,
            tump::exp<tump::_arg1, tump::_eq, tump::_arg2>
        >,
        // 2 つの引数が異なり、第一引数が整数の場合 int を返却
        tump::if_clause<
            tump::exp<
                tump::is_not_same, tump::_arg1, tump::_arg2,
                tump::_and,
                tump::is_integral, tump::_arg1
            >,
            int
        >,
        // 上記 2 つの条件に一致しない場合、void を返却
        tump::otherwise<void>
    >
>;

static_assert(tump::eval<sample_guard2, int, int>::value == true);
static_assert(tump::eval<sample_guard2, long, double, tump::_eq, int>::value == true);
static_assert(tump::eval<sample_guard2, tump::list<>, double, tump::_eq, void>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::_and`|ref/operator/logical}]
- [{`tump::is_unsigned`|ref/metafunction/std}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::is_floating_point`|ref/metafunction/std}]
