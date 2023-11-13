---
title: count_if - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeListOrValueList... Lists>
        struct concat {};
    }

    // 第一級関数化
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using concat = cbk<fn::concat, ArgsSize>;

    // 定数メンバ type 呼び出し省略のエイリアステンプレート
    template <TypeListOrValueList... Lists>
    using concat_t = typename fn::concat<Lists...>::type;
}
```

### パラメータ

- Lists - [{`tump::TypeListOrValueList`|ref/invocable/is_t_or_v_list}]で真と判定されるリストによるパラメータパック。指定されるすべてのリストのコンテナは同じテンプレートでなければいけない。
- ArgsSize - [{`tump::eval`|ref/expression/exp}]などの式で利用する際の、実行までに要する引数の固定。符号なし整数。

## 概要

`tump::concat`は、1 または、複数のリストを結合し、1 つのリストとして返却するメタ関数です。

テンプレートパラメータパック`Lists`には 1 つ以上の任意数のリストをして可能ですが、テンプレートパラメータパックを保持するテンプレート型は同じものに統一されている必要があります。  
さもなくば、制約によりコンパイルエラーとなります。  
具体例は、下記の表を確認ください。

| 例 | OK/NG | 解説 |
| --- | --- | --- |
| `tump::concat_t<tump::list<int, double>>` | OK | `tump::concat`の引数が`tump::list`のみのため。 |
| `tump::concat_t<tump::list<int, double>, tump::list<>, tump::list<void, short>>` | OK | `tump::concat`の引数が`tump::list`のみのため。 |
| `tump::concat_t<std::tuple<int, double>, tump::tuple<void, short>>` | OK | `tump::concat`の引数が`std::tuple`のみのため。 |
| `tump::concat_t<std::list<int, double>, tump::tuple<void, short>>` | NG | `tump::concat`の引数に`tump::list`と`std::tuple`が入り混じっているため。 |

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void>;
using list2 = tump::list<std::vector<int>, char>;
using list3 = std::tuple<int, float, A>;
using list4 = std::tuple<std::vector<int>, double>;
using list5 = tump::make_empty_t<list3>;
using list6 = tump::vlist<int(1), long(2), short(3)>;
using list7 = tump::vlist<char(4), std::size_t(5)>;

// 引数が一つだけの場合
static_assert(std::is_same_v<
    tump::concat_t<list1>,
    list1
> == true);

// 引数が複数の場合
// 空のリストは無視される
static_assert(std::is_same_v<
    tump::concat_t<list1, list2>,
    tump::list<int, float, void, std::vector<int>, char>
> == true);
static_assert(std::is_same_v<
    tump::concat_t<list1, tump::list<>, list2>,
    tump::list<int, float, void, std::vector<int>, char>
> == true);

// 引数が一つだけの場合
static_assert(tump::eval<
    tump::concat<1>, list3,
    tump::_eq,
    list3
>::value == true);

// 引数が複数の場合
// 空のリストは無視される
static_assert(tump::eval<
    tump::concat<>, list3, list4,
    tump::_eq,
    std::tuple<int, float, A, std::vector<int>, double>
>::value == true);
static_assert(tump::eval<
    tump::concat<3>, list3, list4, list5,
    tump::_eq,
    std::tuple<int, float, A, std::vector<int>, double>
>::value == true);
static_assert(tump::eval<
    tump::concat<3>, list6, list7, tump::vlist<>,
    tump::_eq,
    tump::vlist<int(1), long(2), short(3), char(4), std::size_t(5)>
>::value == true);

// 下記は異なるテンプレートのリストが引数に含まれているため、
// コメントアウトを外すと制約によるコンパイルエラー
// tump::concat_t<list1, list5>;
// tump::eval<tump::concat<>, tump::list<>, list3>;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeListOrValueList`|ref/invocable/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::_eq`|ref/operator/compare}]
