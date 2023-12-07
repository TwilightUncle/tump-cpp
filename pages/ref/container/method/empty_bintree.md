---
title: empty_bintree - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class Comparing = comparing_size>
    using empty_bintree = ...;
}
```

### パラメータ

- Comparing - [{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラス

## 概要

`tump::empty_bintree`は、任意の基準によって、要素の大小関係を維持する空のバイナリツリーを作成します。

## 例

```cpp
#include <tump.hpp>

using size_bintree = tump::push_t<tump::empty_bintree<>, std::int32_t, std::uint8_t, std::int64_t>;

static_assert(std::is_same_v<
    tump::flatten_t<size_bintree>,
    tump::list<std::uint8_t, std::int32_t, std::int64_t>
> == true);

template <class L, class R>
struct compare_list_size : public tump::vwrap<
    int(tump::len_v<L>) - int(tump::len_v<R>)
> {};

using comparing_list_size = tump::comparing_type<
    tump::cbk<compare_list_size, 2>,
    tump::is_type_list
>;

using sorted_list = tump::eval<
    tump::flatten,
    tump::_apply,
    tump::push<5>,
    tump::empty_bintree<comparing_list_size>,
    tump::list<int, float>,
    tump::list<>,
    std::tuple<int, float, char>,
    std::tuple<int>
>;

static_assert(std::is_same_v<
    sorted_list,
    tump::list<
        tump::list<>,
        std::tuple<int>,
        tump::list<int, float>,
        std::tuple<int, float, char>
    >
> == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::push`|ref/container/method/bintree_push}]
- [{`tump::flatten`|ref/container/method/flatten}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::_apply`|ref/operator/apply}]
