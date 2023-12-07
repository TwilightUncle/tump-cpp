---
title: is_bintree・BynaryTree - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class T>
        struct is_bintree {};
    }

    // 第一級関数化
    using is_bintree = cbk<fn::is_bintree, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class T>
    constexpr auto is_bintree_v = fn::is_bintree<T>::value;

    // 制約
    template <class T>
    concept BynaryTree = is_bintree_v<T>;
}
```

### パラメータ

- T - 任意の型

## 概要

指定のテンプレートパラメータ`T`がバイナリツリーか判定し、バイナリツリーの場合は`std::true_type`、それ以外の場合は`std::false_type`を継承します。

下記のような型がバイナリツリーと判定されます。

- [{`tump::empty_bintree`|ref/container/method/empty_bintree}]で生成された型
- [{`tump::to_bintree`|ref/container/method/to_bintree}]で生成された型

## 例

```cpp
#include <tump.hpp>

using size_bintree = tump::push_t<tump::empty_bintree<>, std::int32_t, std::uint8_t, std::int64_t>;

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

using sorted_list = tump::eval<
    tump::flip, tump::to_bintree,
    comparing_list_size,
    tump::list<
        tump::list<int, float>,
        tump::list<>,
        std::tuple<int, float, char>,
        std::tuple<int>
    >
>;

static_assert(tump::is_bintree_v<tump::empty_bintree<>> == true);
static_assert(tump::is_bintree_v<int> == false);
static_assert(tump::eval<tump::is_bintree, size_bintree>::value == true);
static_assert(tump::eval<tump::is_bintree, tump::list<>>::value == false);
static_assert(tump::BynaryTree<sorted_list> == true);
static_assert(tump::BynaryTree<std::tuple<int, float>> == false);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::push`|ref/container/method/bintree_push}]
- [{`tump::empty_bintree`|ref/container/method/empty_bintree}]
- [{`tump::to_bintree`|ref/container/method/to_bintree}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
