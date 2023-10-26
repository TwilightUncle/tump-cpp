---
title: invoke_list - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <Invocable F, class ArgList>
        struct invoke_list;
    }

    // 第一級関数化
    using invoke_list = cbk<fn::invoke_list, 2>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <Invocable F, class ArgList>
    using invoke_list_t = typename fn::invoke_list<F, ArgList>::type;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <Invocable F, class ArgList>
    constexpr auto invoke_list_v = fn::invoke_list<F, ArgList>::value;
}
```

### パラメータ

- F - 第一級関数化したメタ関数。[{`tump::Invocable`|ref/invocable/invocable}]で真と判定されなければいけない。
- ArgList - 型のテンプレートパラメータパックを指定したテンプレートクラス

## 概要

第一級関数化したメタ関数に引数を渡して実行するメタ関数です。

ほとんど、[{`tump::invoke`|ref/invocable/invoke}]と機能は同じですが、メタ関数を適用する引数の渡し方が異なります。  
[{`tump::invoke`|ref/invocable/invoke}]が直接引数のテンプレートパラメータパックを受け取るのに対して、`tump::invoke_list`は型のテンプレートパラメータパックを持つテンプレート型により、引数を渡します。

## 例

```cpp
#include <tuple>
#include <tump.hpp>

// 引数リストは 型のテンプレートパラメータを持つテンプレートクラスであれば何でもよい
static_assert(tump::invoke_list_v<tump::is_same, tump::list<int, int>> == true);
static_assert(tump::invoke_list_v<tump::is_same, std::tuple<int, int>> == true);

// invoke による、上記と同様の処理。
// invoke_list と異なり、直接テンプレートパラメータを渡す
static_assert(tump::invoke_v<tump::is_same, int, int> == true);

// 第一級関数としての使用
static_assert(tump::eval<tump::invoke_list, tump::is_same, tump::list<int, int>>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::Invocable`|ref/invocable/invocable}]
- [{`tump::is_same`|ref/metafunction/std}]
- [{`tump::list`|ref/container/list}]
