---
title: get_back - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        using get_back = ...;
    }

    // 第一級関数化
    using get_back = cbk<fn::get_back, 1>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    using get_back_t = typename fn::get_back<List>::type;
    
    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    constexpr auto get_back_v = fn::get_back<List>::value;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::get_back`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、最後尾の要素を取得するメタ関数です。

パラメータ`List`には、型テンプレートパラメータパックを持つ任意の型または、[{`tump::vlist`|ref/container/vlist}]を指定することができます。

なお、`List`に空のリストを渡した場合は、制約によりコンパイルエラーとなります。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, char>;
using list2 = std::tuple<int, float, A, std::vector<int>, double>;
using list3 = tump::vlist<int(1), long(2), char(3)>;
using list4 = tump::make_empty_t<std::tuple<int>>;
using list5 = tump::vlist<>;
using list6 = tump::to_btree_t<list1>;

static_assert(std::is_same_v<tump::get_back_t<list1>, char> == true);
static_assert(tump::get_back_v<list3> == char(3));
static_assert(tump::eval<tump::get_back, list2, tump::_eq, double>::value == true);
static_assert(tump::eval<tump::get_back, list3>::value == char(3));
static_assert(tump::eval<tump::get_back, list6, tump::_eq, std::vector<int>>::value == true);

// 下記は空のリストを指定しているため、
// コメントアウトを外すとコンパイルエラー。
// tump::get_back_t<list4>;
// tump::eval<tump::get_back, list5>::value;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
- [{`tump::_eq`|ref/operator/compare}]
