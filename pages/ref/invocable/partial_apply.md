---
title: partial_apply - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <Invocable F, class... PartialArgs>
    struct partial_apply;
}
```

### パラメータ

- F - 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- PartialArgs - 部分適用を行う引数の型パラメータパック。`F`を実行するのに必要な引数の数より、パラメータが多い場合はエラー。

## 概要

第一級関数化したメタ関数の部分適用を行います。

## 使い方

第一級関数化したメタ関数`F`について、部分適用を行いたい任意の数の型を`PartialArgs`として指定します。  
`partial_apply`による部分適用の結果も、第一級関数化したメタ関数として処理されます。

なお、[{`tump::callback`|ref/invocable/callback}]の`ArgsSize`で指定された引数の数より、部分適用した後の残りの引数の数を算出しています。  
上記算出の際、元のメタ関数の引数の数より、部分適用しようとしている引数の数が多くなった際は型制約により、コンパイルエラーとなります。

## 例

```cpp
#include <type_traits>
#include <tump.cpp>

using callback_is_same = tump::cbk<std::is_same, 2>;
using callback_is_int = tump::partial_apply<callback_is_same, int>;

static_assert(tump::eval<callback_is_int, int>::value == true);
static_assert(tump::eval<callback_is_int, double>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::callback`|ref/invocable/callback}]
- [{`tump::Invocable`|ref/invocable/invocable}]
