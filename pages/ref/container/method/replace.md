---
title: replace - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class OldType, class NewType, TypeList List>
        using replace = ...;
    }

    // 第一級関数化
    using replace = cbk<fn::replace, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <class OldType, class NewType, TypeList List>
    using replace_t = typename fn::replace<OldType, NewType, List>::type;
}
```

### パラメータ

- OldType - 任意の型
- NewType - 任意の型
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::replace`は、テンプレートパラメータ`List`が保持するパラメータパックのうち、パラメータ`OldType`と一致する型を、パラメータ`NewType`で置き換えます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

class A {};

using list1 = tump::list<int, float, void, std::vector<int>, int>;
using list2 = std::tuple<short, float, A, std::vector<int>, double>;

// list1 の int を char を置き換える
static_assert(std::is_same_v<
    tump::replace_t<int, char, list1>,
    tump::list<char, float, void, std::vector<int>, char>
> == true);

// list2 には int が存在しないため、内容に特に変化なし
static_assert(tump::eval<
    tump::replace, int, char, list2,
    tump::_eq,
    list2
>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::list`|ref/container/list}]
- [{`tump::_eq`|ref/operator/compare}]
