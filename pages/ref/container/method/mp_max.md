---
title: mp_max - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List, class Comparing = comparing_size>
        requires (len_v<List> > 0)
        struct mp_max {};
    }

    // 第一級関数化
    using mp_max = cbk<fn::mp_max, 2>;

    // 第一級関数化した際にデフォルト引数を使えないため、そのための定義
    using mp_size_max = partial_apply<flip, mp_max, comparing_size>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List, class Comparing = comparing_size>
    using mp_max_t = typename fn::mp_max<List, Comparing>::type;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List, class Comparing = comparing_size>
    constexpr auto mp_max_v = fn::mp_max<N, List>::value;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型
- Comparing - [{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラス

## 概要

`tump::mp_max`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、最も大きいと判定される型を返すメタ関数です。  
テンプレートパラメータ`Comparing`に対して、[{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラスを指定することで、任意の基準で大小比較を行うことが可能です。

デフォルトでは、パラメータ`Comparing`に`tump::comparing_size`が指定されており、パラメータ`List`のみでも`tump::mp_max`を使用することができます。  
パラメータ`Comparing`に`tump::comparing_size`が指定されている場合は、該当の型を`sizeof`した結果の大小により比較を行います。

なお、`List`に指定した型は、1 つ以上の要素を持っていない場合、制約によりコンパイルエラーとなります。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<std::int16_t, std::int64_t, std::int8_t, std::int32_t>;
using list2 = tump::vlist<int(1), std::uint16_t(5), char(-3), std::int64_t(-2)>;

// デフォルトの比較基準による mp_max の利用例
static_assert(std::is_same_v<tump::mp_max_t<list1>, std::int64_t> == true);
static_assert(tump::eval<tump::mp_size_max, list1, tump::_eq, std::int64_t>::value == true);

// 最大値を取得
static_assert(tump::mp_max_v<list2, tump::comparing_value_member> == std::uint16_t(5));

// ユーザー指定の評価基準を指定する例
// 最もパラメータパックが多いものを取り出す

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

template <tump::TypeList Lists>
using get_max_list_impl = tump::fn::mp_max<Lists, comparing_list_size>;
using get_max_list = tump::cbk<get_max_list_impl, 1>;

using list3 = tump::list<
    tump::list<int, float>,
    tump::list<>,
    std::tuple<int, float, char>,
    std::tuple<int>
>;

static_assert(tump::eval<get_max_list, list3, tump::_eq, std::tuple<int, float, char>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::comparing_size`|ref/metafunction/comparing_type}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::_eq`|ref/operator/compare}]
