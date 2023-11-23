---
title: make_empty - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class List>
        struct make_empty;
    }

    // 第一級関数化
    using make_empty = cbk<fn::make_empty, 1>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <class List>
    using make_empty_t = typename fn::make_empty<List>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::make_empty`は、引数`List`が持つ要素を全て除去した状態の、空のリストを返すメタ関数です。  
`tump::make_empty`が返却する型は、全て[{`tump::is_empty`|ref/container/method/is_empty}]で真と判定されます。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, float, char>;
using list2 = std::tuple<int, float, char>;
using list3 = tump::vlist<int(1), char(2), std::size_t(3)>;
using list4 = tump::to_btree_t<list1>;

static_assert(tump::is_empty_v<tump::make_empty_t<list1>> == true);
static_assert(tump::is_empty_v<tump::make_empty_t<list2>> == true);
static_assert(tump::eval<tump::is_empty, tump::_apply, tump::make_empty, list3>::value == true);
static_assert(tump::eval<tump::is_empty, tump::_apply, tump::make_empty, list4>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{バイナリツリー|ref/container/btree}]
- [{`tump::is_empty`|ref/container/method/is_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
- [{`tump::_apply`|ref/operator/apply}]
