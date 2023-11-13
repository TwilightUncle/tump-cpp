---
title: map - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <Invocable F, TypeList List>
        struct map {};
    }

    // 第一級関数化
    using map = cbk<fn::map, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <Invocable F, TypeList List>
    using map_t = typename fn::map<F, List>::type;
}
```

### パラメータ

- F - [{`tump::Invocable`|ref/invocable/invocable}]で真と判定されるメタ関数
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::map`は、テンプレートパラメータ`List`が保持するパラメータパックの全ての要素に対して、メタ関数`F`を適用するメタ関数です。  
`F`は 1 つ以上の引数を持つ全てのメタ関数が使用可能で、2 つ以上の引数を持つメタ関数の場合は、部分適用が行われます。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, char, long>;
using list2 = std::tuple<int, float, double>;

static_assert(std::is_same_v<
    tump::map_t<tump::make_unsigned, list1>,
    tump::list<unsigned int, unsigned char, unsigned long>
> == true);
static_assert(tump::eval<
    tump::map, tump::add_const, list2,
    tump::_eq,
    std::tuple<const int, const float, const double>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
- [{`tump::make_unsigned`|ref/metafunction/std}]
- [{`tump::add_const`|ref/metafunction/std}]
