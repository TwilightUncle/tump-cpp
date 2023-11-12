---
title: fill - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class T, std::size_t N>
    struct fill_arg {};

    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List, class FillArg>
        struct fill {};
    }

    // 第一級関数化
    using fill = cbk<fn::fill, 2>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeList List, class FillArg>
    using fill_t = typename fn::fill<List, FillArg>::type;
}
```

### パラメータ

- T - 任意の型
- N - 結果の型のリストの長さを示す整数値
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型
- FillArg - `tump::fill_arg`により、`T`と`N`を指定する

## 概要

`tump::fill`は、引数`List`が持つ要素を、`N`個の`T`によるパラメータパックで置き換えます。

なお、テンプレートパラメータに非型が含まれていると、[{`tump::exp`や`tump::eval`|ref/expression/exp}]の式中で、使うことができないメタ関数となってしまいます。  
そのため、非型パラメータである`N`は直接`tump::fill`ではなく、`tump::fill_arg`をはさんで渡すような実装となっています。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, char>;
using list2 = tump::make_empty_t<std::tuple<int, float, char>>;

static_assert(std::is_same_v<
    tump::fill_t<list1, tump::fill_arg<int, 5>>,
    tump::list<int, int, int, int, int>
> == true);

static_assert(tump::eval<
    tump::fill, list2, tump::fill_arg<double, 3>,
    tump::_eq,
    std::tuple<double, double, double>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
