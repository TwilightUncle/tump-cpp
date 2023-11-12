---
title: make_type_list - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List, class... Types>
        struct make_type_list {};
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using make_type_list = cbk<fn::make_type_list, ArgsSize>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeList List, class... Types>
    using make_type_list_t = typename fn::make_type_list<List, Types...>::type;
}
```

### パラメータ

- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型
- Types - 任意数の型のテンプレートパラメータパック

## 概要

`tump::make_type_list`は、引数`List`が持つ要素を、テンプレートパラメータパック`Types`で置き換えます。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, char>;
using list2 = tump::make_empty_t<std::tuple<int, float, char>>;

static_assert(std::is_same_v<
    tump::make_type_list_t<list1, float, void, double>,
    tump::list<float, void, double>
> == true);

static_assert(tump::eval<
    tump::make_type_list<4>,
    list2,
    double, std::size_t, long long,
    tump::_eq,
    std::tuple<double, std::size_t, long long>
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::is_empty`|ref/container/method/is_empty}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
