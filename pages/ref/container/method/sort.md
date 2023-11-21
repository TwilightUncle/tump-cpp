---
title: sort - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List, class Comparing = comparing_size>
        struct sort {};
    }

    // 第一級関数化
    using sort = cbk<fn::sort, 1>;
    using sort_size = partial_apply<flip, sort, comparing_size>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List, class Comparing = comparing_size>
    using sort_t = typename fn::sort<List, Comparing>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型
- Comparing - [{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラス

## 概要

`tump::sort`は、テンプレートパラメータ`List`が持つ要素を、パラメータ`Comparing`で指定した基準により、昇順で並び替えます。
テンプレートパラメータ`Comparing`に対して、[{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラスを指定することで、任意の基準で大小比較を行うことが可能です。

デフォルトでは、パラメータ`Comparing`に`tump::comparing_size`が指定されており、パラメータ`List`のみでも`tump::sort`を使用することができます。  
パラメータ`Comparing`に`tump::comparing_size`が指定されている場合は、該当の型を`sizeof`した結果の大小により比較を行います。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<std::int16_t, std::int64_t, std::int8_t, std::int32_t>;
using list2 = tump::vlist<int(1), std::uint16_t(5), char(-3), std::int64_t(-2)>;

// デフォルトの比較基準によるリストの並び替え
static_assert(std::is_same_v<
    tump::sort_t<list1>,
    tump::list<std::int8_t, std::int16_t, std::int32_t, std::int64_t>
> == true);
static_assert(tump::eval<
    tump::sort_size, list1,
    tump::_eq,
    tump::list<std::int8_t, std::int16_t, std::int32_t, std::int64_t>
>::value == true);
static_assert(tump::eval<
    tump::sort, list2, tump::comparing_value_member,
    tump::_eq,
    tump::vlist<char(-3), std::int64_t(-2), int(1), std::uint16_t(5)>
>::value == true);

// ユーザー指定の評価基準を指定する例
// 要素数が小さい順に並び替える

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

using list2 = std::tuple<
    tump::list<int, float>,
    tump::list<>,
    std::tuple<int, float, char>,
    std::tuple<int>
>;

static_assert(tump::eval<
    tump::sort, list2, comparing_list_size,
    tump::_eq,
    std::tuple<
        tump::list<>,
        std::tuple<int>,
        tump::list<int, float>,
        std::tuple<int, float, char>
    >
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::comparing_value_member`|ref/metafunction/comparing_type}]
- [{`tump::_eq`|ref/operator/compare}]
