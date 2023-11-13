---
title: pop_front - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList List>
        requires (!is_empty_v<List>)
        using pop_front = ...;
    }

    // 第一級関数化
    using pop_front = cbk<fn::pop_front, 1>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList List>
    using pop_front_t = typename fn::pop_front<List>::type;
}
```

### パラメータ

- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::pop_front`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、先頭要素を除去するメタ関数です。

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

static_assert(std::is_same_v<tump::pop_front_t<list1>, tump::list<float, void, std::vector<int>, char>> == true);
static_assert(std::is_same_v<tump::pop_front_t<list3>, tump::vlist<long(2), char(3)>> == true);
static_assert(tump::eval<tump::pop_front, list2, tump::_eq, std::tuple<float, A, std::vector<int>, double>>::value == true);

// 下記は空のリストを指定しているため、
// コメントアウトを外すとコンパイルエラー。
// tump::pop_front_t<list4>;
// tump::eval<tump::pop_front, list5>::value;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
