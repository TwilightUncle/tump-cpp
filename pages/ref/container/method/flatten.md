---
title: flatten - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn
    {
        // 大元のメタ関数定義
        template <BynaryTree T>
        struct flatten {};
    }

    // 第一級関数化
    using flatten = cbk<fn::flatten, 1>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <BynaryTree T>
    using flatten_t = typename fn::flatten<T>::type;
}
```

### パラメータ

- T - [{`tump::BynaryTree`|ref/invocable/is_bintree}]で真と判定されるバイナリツリー

## 概要

`tump::flatten`は、バイナリツリー`T`を、[{`tump::list`|ref/container/list}]に変換するメタ関数です。    

TumpCppにおけるバイナリツリーは、同じ比較基準で同じ要素を保持する場合でも、要素の型を追加する順序によって生成される木構造が異なっている場合があります。  
バイナリツリー同士の比較や評価にはあまり向いていないので、いったん[{`tump::list`|ref/container/list}]に変換することで、望んだ結果を得ることができます。

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
- [{`tump::BynaryTree`|ref/container/method/is_bintree}]
- [{`tump::is_type_list`|ref/container/method/is_type_list}]
- [{`tump::len`|ref/container/method/len}]
- [{`tump::empty_bintree`|ref/container/method/empty_bintree}]
- [{`tump::push`|ref/container/method/bintree_push}]
- [{`tump::vwrap`|ref/metafunction/vwrap}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
- [{`tump::_apply`|ref/operator/apply}]
