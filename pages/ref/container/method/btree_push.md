---
title: push - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn
    {
        // 大元のメタ関数定義
        template <BynaryTree T, class... Types>
        struct push {};
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using push = cbk<fn::push, ArgsSize>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <BynaryTree T, class... Types>
    using push_t = typename fn::push<T, Types...>::type;
}
```

### パラメータ

- T - [{`tump::BynaryTree`|ref/invocable/is_btree}]で真と判定されるバイナリツリー
- Types - バイナリツリー`T`へ格納可能な型のパラメータパック

## 概要

`tump::push`は、バイナリツリー`T`へ、任意数の型`Types`を挿入するメタ関数です。  
挿入された型は、バイナリツリーが保持する要素の大小関係に準じた、適切な位置へ配置されます。

## 例

```cpp
#include <tump.hpp>

using size_btree = tump::push_t<tump::empty_btree<>, std::int32_t, std::uint8_t, std::int64_t>;

static_assert(std::is_same_v<
    tump::flatten_t<size_btree>,
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
    tump::empty_btree<comparing_list_size>,
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
- [{`tump::BynaryTree`|ref/container/method/is_btree}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::push`|ref/container/method/btree_push}]
- [{`tump::flatten`|ref/container/method/flatten}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::_apply`|ref/operator/apply}]
