---
title: mp_min - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List>
        requires (!is_empty_v<List>)
        using mp_min = ...;
    }

    // 第一級関数化
    using get_front = cbk<fn::get_front, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    using get_front_t = typename fn::get_front<List>::type;
    
    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    constexpr auto get_front_v = fn::get_front<List>::value;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::get_front`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、先頭要素を取得するメタ関数です。

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

static_assert(std::is_same_v<tump::get_front_t<list1>, int> == true);
static_assert(tump::get_front_v<list3> == int(1));
static_assert(tump::eval<tump::get_front, list2, tump::_eq, int>::value == true);
static_assert(tump::eval<tump::get_front, list3>::value == int(1));
static_assert(tump::eval<tump::get_front, list6, tump::_eq, void>::value == true);

// 下記は空のリストを指定しているため、
// コメントアウトを外すとコンパイルエラー。
// tump::get_front_t<list4>;
// tump::eval<tump::get_front, list5>::value;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
- [{`tump::_eq`|ref/operator/compare}]
