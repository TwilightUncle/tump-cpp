---
title: get_max - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn
    {
        // 大元のメタ関数定義
        template <BynaryTree T>
        struct get_max {};
    }

    // 第一級関数化
    using get_max = cbk<fn::get_max, 1>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <BynaryTree T>
    using get_max_t = typename fn::get_max<T>::type;
}
```

### パラメータ

- T - [{`tump::BynaryTree`|ref/invocable/is_btree}]で真と判定されるバイナリツリー

## 概要

`tump::get_max`は、バイナリツリー`T`が保持する要素のうち、最大と判定される型を返却します。

## 例

```cpp
#include <tump.hpp>

using size_btree = tump::push_t<tump::empty_btree<>, std::int32_t, std::uint8_t, std::int64_t>;

static_assert(std::is_same_v<tump::get_max_t<size_btree>, std::int64_t> == true);

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

using sorted_list = tump::eval<
    tump::flip, tump::to_btree,
    comparing_list_size,
    tump::list<
        tump::list<int, float>,
        tump::list<>,
        std::tuple<int, float, char>,
        std::tuple<int>
    >
>;

static_assert(tump::eval<tump::get_max, sorted_list, tump::_eq, std::tuple<int, float, char>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::BynaryTree`|ref/container/method/is_btree}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::push`|ref/container/method/btree_push}]
- [{`tump::flip`|ref/invocable/flip}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::_eq`|ref/operator/compare}]
