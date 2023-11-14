---
title: zip - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List1, TypeList List2>
        struct zip {};
    }

    // 第一級関数化
    using zip = cbk<fn::zip, 2>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeList List1, TypeList List2>
    using zip_t = typename fn::zip<F, List>::type;
}
```

### パラメータ

- List1 - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト
- List2 - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::zip`は、 2 つの型のリストから同じインデックスの型を 1 つずつ取り出し、ペアとした要素を持つリストを作成するメタ関数です。

2 つのリストの長さが等しくない場合、コンパイルエラーとなります。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

using list1 = tump::list<int, char, long>;
using list2 = std::tuple<char, float, double>;

static_assert(std::is_same_v<
    tump::zip_t<list1, list2>,
    tump::list<
        tump::list<int, char>,
        tump::list<char, float>,
        tump::list<long, double>
    >
> == true);
static_assert(tump::eval<
    tump::zip, list2, list1,
    tump::_eq,
    tump::list<
        tump::list<char, int>,
        tump::list<float, char>,
        tump::list<double, long>
    >
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
