---
title: slice - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <std::size_t... Sizes>
    struct size_args {};

    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List, class SizeArgs>
        struct slice;
    
        template <TypeListOrValueList List, std::size_t Start, std::size_t Size = len_v<List>, std::size_t Stride = 0>
        struct slice<List, size_args<Start, Size, Stride>> {};
    }

    // 第一級関数化
    using slice = cbk<fn::slice, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List, class SizeArgs>
    using slice_t = typename fn::slice<List, SizeArgs>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型
- SizeArgs - `tump::size_args`により、`Start`、`Size`、`Stride`を指定
- Start - 符号なし整数値。リストの要素数より小さい値を指定しなければいけない
- Size - 符号なし整数値。1 より大きい値を指定しなければいけない。指定しなくてもOK。
- Stride - 符号なし整数値。指定しなくてもOK。

## 概要

`tump::slice`は、テンプレートパラメータ`List`から、パラメータ`SizeArgs`により指定した範囲のリストを切り出します。

`SizeArgs`では`tump::size_args`を介して下記 3 つの値により、切り出す方法を決定します。

| パラメータ | 指定の要否 | 概要 |
| --- | --- | --- |
| `Start` | 必須 | 切り出しの開始位置を決定します。`tump::size_args`の 1 つ目のパラメータとして指定します。 |
| `Size` | 任意 | 切り出す長さを決定します。未指定または、`Size + Start`が`List`の要素数より大きい場合場合、`Start`の位置から、元の`List`の最後の要素までを取得します。tump::size_args`の 2 つ目のパラメータとして指定します。 |
| `Stride` | 任意 | 切り出す要素の間隔を決定します。例えば 1 を指定した場合は`Start`の位置から 1 個飛ばし、2 の場合は 2 個飛ばしで`Size`で指定した数の要素を取得します。デフォルトは 0 です。`tump::size_args`の 3 つ目のパラメータとして指定します。 |

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;
using list3 = tump::vlist<int(1), long(2), char(3), short(4), std::size_t(5), std::uint16_t(6)>;

// 2 の位置から最後尾まで要素を切り出す
static_assert(std::is_same_v<
    tump::slice_t<list1, tump::size_args<2>>,
    tump::list<void, std::vector<int>, char>
> == true);

// 1 の位置から 2 つ要素を切り出す
static_assert(tump::eval<
    tump::slice, list2, tump::size_args<1, 2>,
    tump::_eq,
    std::tuple<float, A>
>::value == true);

// 1 の位置から 1 つおきに 4 つの要素を切り出す。
// ただし、下記では取得可能な要素数が Size で指定したものよりも小さいため、
// 最後尾に到達した時点で処理を終わる。
static_assert(tump::eval<
    tump::slice, list3, tump::size_args<1, 4, 1>,
    tump::_eq,
    tump::vlist<long(2), short(4), std::uint16_t(6)>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::_eq`|ref/operator/compare}]
