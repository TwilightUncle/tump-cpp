---
title: get - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <std::size_t N, TypeListOrValueList List>
        requires (N < len_v<List>)
        struct get {};
    }

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <std::size_t N, TypeListOrValueList List>
    using get_t = typename fn::get<N, List>::type;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <std::size_t N, TypeListOrValueList List>
    constexpr auto get_v = fn::get<N, List>::value;
}
```

### パラメータ

- N - 符号なし整数値。パラメータ`List`の持つ要素数よりも少ない値しか指定できない
- List - [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]で真と判定される型

## 概要

`tump::get`は、テンプレートパラメータ`List`が保持するパラメータパックから、`N`で指定した位置にある要素を取得します。  
`List`には型テンプレートパラメータパックまたは、[{`tump::vlist`|ref/container/vlist}]を指定できます。

パラメータ`N`にパラメータ`List`の要素数以上の数値を指定すると、制約によりコンパイルエラーとなります。  
また、パラメータ`List`に空のリストを渡してもコンパイルエラーとなります。

なお、`tump::get`は、受け取るテンプレートパラメータに非型テンプレートパラメータが含まれる都合上、[{`tump::callback`|ref/invocable/callback}]に渡すことはできず、第一級関数化の定義はありません。

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

static_assert(std::is_same_v<tump::get_t<0, list1>, int> == true);
static_assert(std::is_same_v<tump::get_t<3, list2>, std::vector<int>> == true);
static_assert(tump::get_v<2, list3> == char(3));

// 下記は リストのサイズ以上のインデックスまたは、
// 空のリストを指定しているため、コメントアウトを外すとコンパイルエラー
// tump::get_t<5, list1>;
// tump::get_v<3, list3>;
// tump::get_t<0, list4>;
// tump::get_v<0, list5>;

int main() {}
```

## 関連リンク

- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
