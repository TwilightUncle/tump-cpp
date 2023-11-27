---
title: pop_min - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn
    {
        // 大元のメタ関数定義
        template <BynaryTree T>
        struct pop_min {};
    }

    // 第一級関数化
    using pop_min = cbk<fn::pop_min, 1>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <BynaryTree T>
    using pop_min_t = typename fn::pop_min<T>::type;
}
```

### パラメータ

- T - [{`tump::BynaryTree`|ref/invocable/is_btree}]で真と判定されるバイナリツリー

## 概要

`tump::pop_min`は、バイナリツリー`T`が保持する要素のうち、最小と判定される型を取り除きます。

## 例

```cpp
#include <tump.hpp>

using size_btree = tump::push_t<tump::empty_btree<>, std::int32_t, std::uint8_t, std::int64_t>;

static_assert(std::is_same_v<
    tump::flatten_t<tump::pop_min_t<size_btree>>,
    tump::list<std::int32_t, std::int64_t>
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
    tump::_dot,
    tump::pop_min,
    tump::_apply,
    tump::push<5>,
    tump::empty_btree<comparing_list_size>,
    tump::list<int, float>,
    tump::list<>,
    std::tuple<int, float, char>,
    std::tuple<int>
>;

static_assert(std::is_same_v<
    sorted_list,
    tump::list<
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
- [{`tump::BynaryTree`|ref/container/method/is_btree}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::push`|ref/container/method/btree_push}]
- [{`tump::flatten`|ref/container/method/flatten}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::_apply`|ref/operator/apply}]
- [{`tump::_dot`|ref/operator/dot}]
