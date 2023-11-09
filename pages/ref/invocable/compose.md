---
title: compose - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <Invocable F, Invocable... Funcs>
        struct compose;
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using compose = cbk<fn::compose, ArgsSize>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <Invocable F, Invocable... Funcs>
    using compose_t = typename fn::compose<F, Funcs...>::type;
}
```

### パラメータ

- F - 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- Funcs - `F` と同様の制約のメタ関数のパラメータパック。

## 概要

1 つ以上のメタ関数を合成し、第一級関数化されたメタ関数を結果として返却します。  
全てカリー化している関数として処理するため、指定可能なメタ関数は、実行に必要な引数の数について特に制限がありません。  
※引数が 1 つ以上であれば問題なし。

## 使い方

数学における合成関数と同じように、1 つの型に対して、指定された複数のメタ関数を順番に適用します。  
`tump::compose`における関数適用は、テンプレートパラメータパック`Funcs`の最後尾から先頭の方向に行われ、最後にテンプレートパラメータ`F`の適用が行われます。

単純にメタ関数呼び出しによる記述で関数を合成しようとすると、下記のように多くの`<>`をネストしたような記述をしなければいけません。

- `funcA<typename funcB<typename funcC<Arg>::type>::type>::type`

上記は可読性を著しく損ない、記述を誤った際は、C++ のコンパイルエラー出力も相まって不具合の特定が難しくなります。  
そのため、TumpCpp では`tump::compose`を使用することで、関数の合成を平坦に記述できるようにしています。

上記のネストした記述は、`tump::compose`を用いることで、下記のように書き換えることができます。  
※下記では全てのメタ関数が第一級関数化されているものとする。

- `tump::invoke_t<tump::compose_t<funcA, funcB, funcC>, Arg>`

## 例

```cpp
#include <tump.hpp>

using list1 = tump::list<int, float, int, double, float, void>;

// 下記 1 ~ 4 は、いずれも下記の操作を行う。
// 重複削除 -> 並びの反転 -> 最初に見つかる float のインデックス取得

// 1. メタ関数呼び出しによる、関数の合成
constexpr auto case1 = tump::index_of_v<float, 
    tump::reverse_t<
        tump::unique_t<list1>
    >
>;

// 2. compose を用いたメタ関数呼び出しによる関数の合成
constexpr auto case2 = tump::invoke_v<
    tump::compose_t<
        tump::partial_apply<tump::index_of, float>,
        tump::reverse,
        tump::unique
    >,
    list1
>;

// 3. eval による compose を用いない関数の合成
constexpr auto case3 = tump::eval<
    tump::index_of, float, tump::exp<
        tump::reverse, tump::exp<
            tump::unique, list1
        >
    >
>::value;

// 4. eval による compose を用いた関数の合成
constexpr auto case4 = tump::eval<
    tump::compose<3>,
    tump::partial_apply<tump::index_of, float>,
    tump::reverse,
    tump::unique,
    list1
>::value;

// 1 の確認及び、1 ~ 4 がすべて同じ結果となることの確認
static_assert(case1 == 2);
static_assert(case1 == case2);
static_assert(case1 == case3);
static_assert(case1 == case4);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::exp`|ref/expression/exp}]
- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::invoke`|ref/invocable/invoke}]
- [{`tump::partial_apply`|ref/invocable/partial_apply}]
- [{`tump::list`|ref/container/list}]
- [{`tump::index_of`|ref/container/method/index_of}]
- [{`tump::reverse`|ref/container/method/reverse}]
- [{`tump::unique`|ref/container/method/unique}]
