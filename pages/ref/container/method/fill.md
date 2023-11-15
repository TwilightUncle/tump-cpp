---
title: fill - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class T, std::size_t N>
    struct fill_type_arg {};

    template <auto V, std::size_t N>
    struct fill_value_arg {};

    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List, class FillArg>
        struct fill {};
    }

    // 第一級関数化
    using fill = cbk<fn::fill, 2>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List, class FillArg>
    using fill_t = typename fn::fill<List, FillArg>::type;
}
```

### パラメータ

- T - 任意の型
- V - 任意の非型パラメータ
- N - 結果の型のリストの長さを示す整数値
- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型
- FillArg - `tump::fill_type_arg`により、`T`と`N`を指定するまたは、 `tump::fill_value_arg`により、`V`と`N`を指定する

## 概要

`tump::fill`は、引数`List`が持つ要素を、`N`個の`T`によるパラメータパックで置き換えます。

なお、テンプレートパラメータに非型が含まれていると、[{`tump::exp`や`tump::eval`|ref/expression/exp}]の式中で、使うことができないメタ関数となってしまいます。  
そのため、非型パラメータは直接`tump::fill`ではなく、`tump::fill_type_arg`または、`tump::fill_value_arg`をはさんで渡すような実装となっています。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, char>;
using list2 = tump::make_empty_t<std::tuple<int, float, char>>;
using list3 = tump::vlist<>;

static_assert(std::is_same_v<
    tump::fill_t<list1, tump::fill_type_arg<int, 5>>,
    tump::list<int, int, int, int, int>
> == true);

static_assert(tump::eval<
    tump::fill, list2, tump::fill_type_arg<double, 3>,
    tump::_eq,
    std::tuple<double, double, double>
>::value == true);

static_assert(tump::eval<
    tump::fill, list3, tump::fill_value_arg<long(3), 3>,
    tump::_eq,
    tump::vlist<long(3), long(3), long(3)>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
