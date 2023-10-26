---
title: 演算子を定義する - TumpCpp リファレンス
---

```cpp
namespace tump {
    // 演算子の評価の優先度・結合性を指定する列挙体
    enum class e_op_priority : std::size_t
    {
        r_0, l_0, _0,
        r_1, l_1, _1,
        r_2, l_2, _2,
        r_3, l_3, _3,
        r_4, l_4, _4,
        r_5, l_5, _5,
        r_6, l_6, _6,
        r_7, l_7, _7,
        r_8, l_8, _8,
        r_9, l_9, _9,
    };
    
    // 演算子を定義するためのテンプレートクラス
    template <InvocableArgN<2> F, e_op_priority Priority>
    struct _op {};
}
```

### _op のパラメータ

- F - 第一級関数である、2 つの引数をとるメタ関数
- Priority - 優先度と結合性を、列挙体`e_op_priority`型の値から選択

## 概要

`tump::_op`は任意の 2 引数のメタ関数`F`を演算子に変換します。  
演算子の優先度は、パラメータ`Priority`に`e_op_priority`型の値を指定します。

`e_op_priority`の値は、列挙された値の識別子の、先頭と末尾の文字により、以下のルールで定義されています。

| 識別詞の中の文字の位置 | 文字 | 説明 |
| --- | --- | --- |
| 先頭 | `r` | 演算子の結合性を右結合にする |
| 先頭 | `l` | 演算子の結合性を左結合にする |
| 先頭 | `_` | 演算子の結合性を非結合にする |
| 末尾 | `0` ~ `9` の数字 | 演算子の評価の優先度を設定する。数字が大きいほど優先度が高い |

例えば、`tump::e_op_priority::l_6`は左結合で優先度`6`、`tump::e_op_priority::_3`は非結合で優先度`3`となります。

なお、TumpCpp の全ての演算子は、`tump::_op`を用いて定義されています。

## 例

```cpp
#include <tump.hpp>

// 演算子 _apply とオペランドが逆の演算子を定義する。
// _apply と同様に最も低い優先度かつ右結合を設定
using op_flip_apply = tump::_op<
    tump::partial_apply<tump::flip, tump::apply<>>,
    tump::e_op_priority::r_0
>;

static_assert(tump::eval<int, op_flip_apply, tump::is_integral>::value == true);
static_assert(tump::eval<float, op_flip_apply, tump::is_integral>::value == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::partial_apply`|ref/invocable/partial_apply}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::apply`|ref/invocable/apply}]
- [{`tump::is_integral`|ref/metafunction/std}]
- [{`tump::_apply`|ref/operator/apply}]
