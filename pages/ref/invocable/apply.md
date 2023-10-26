---
title: apply - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <Invocable F, class... Args>
        struct apply;
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using apply = callback<fn::apply, ArgsSize>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <Invocable F, class... Args>
    using apply_t = typename fn::apply<F, Args...>::type;
}
```

### パラメータ

- F - 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- Args - `F` について適用を行う引数のパラメータパック。
- ArgsSize - [{`tump::eval`|ref/expression/exp}]などの式で利用する際の、実行までに要する引数の固定。符号なし整数。

## 概要

第一級関数化したメタ関数の適用を行います。  

具体的には、`F`の実行に必要なメタ関数が足りない場合は部分適用を行い、`F`の実行が可能な数の引数が渡された際は、メタ関数を実行します。  
[{`tump::partial_apply`|ref/invocable/partial_apply}]と[{`tump::invoke`|ref/invocable/invoke}]の機能を併せ持ったようなメタ関数で、与えられた引数の数に応じて、`partial_apply`か`invoke`のどちらを行うか自動的に切り替えます。

## 例

```cpp
#include <tump.hpp>

// 部分適用。
// is_same の実行には引数が足りないため、
// 結果は部分適用された状態のメタ関数となる。
using is_int1 = tump::apply_t<tump::is_same, int>;

// is_int1 と同じ
using is_int2 = tump::partial_apply<tump::is_same, int>;

// メタ関数の実行
static_assert(tump::apply_t<tump::is_same, int, int>::value == true);
static_assert(tump::apply_t<is_int1, int>::value == true);
static_assert(tump::apply_t<is_int2, int>::value == true);

// 実行可能な数の引数が渡された場合は、invoke と同じ動き
static_assert(tump::invoke_t<tump::is_same, int, int>::value == true);
static_assert(tump::invoke_t<is_int1, int>::value == true);
static_assert(tump::invoke_t<is_int2, int>::value == true);

// 第一級関数としての使用。
// apply のテンプレートパラメータを未指定の場合、
// デフォルト引数として apply を実行するのに必要な引数の数が 2 で固定される
static_assert(tump::eval<tump::apply<>, tump::is_integral, int>::value == true);
static_assert(tump::eval<tump::apply<3>, tump::is_same, int, int>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::partial_apply`|ref/invocable/partial_apply}]
- [{`tump::invoke`|ref/invocable/invoke}]
- [{`tump::is_same`|ref/metafunction/std}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::eval`|ref/expression/exp}]
