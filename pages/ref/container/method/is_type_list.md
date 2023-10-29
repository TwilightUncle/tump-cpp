---
title: is_type_list・TypeList - TumpCpp リファレンス
---

```cpp
namespace tump {
    // 制約
    template <class T>
    concept TypeList = ...;

    namespace fn {
        // メタ関数定義
        template <class T>
        struct is_type_list {};
    }

    // 第一級関数化
    using is_type_list = cbk<fn::is_type_list, 1>;

    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class T>
    constexpr auto is_type_list_v = fn::is_type_list<T>::value;
}
```

### パラメータ

- T - 任意の型

## 概要

指定のテンプレートパラメータ`T`が、**型の**テンプレートパラメータパックを保持するテンプレート型かどうかを判定します。  
なお、非型テンプレートパラメータや、テンプレートテンプレートパラメータを受け取るテンプレート型は、偽と判定されます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

// テンプレートパラメータなしまたは、
// テンプレートパラメータに型以外が含まれているものは偽と判定される。
struct A {};
template <auto V, class T>
struct B {};
template <template <class> class T, class U>
struct C {};

// テンプレートパラメータが全て型のクラスは真と判定される
template <class T, class U>
struct D {};

// 偽と判定されるものの例
static_assert(tump::TypeList<int> == false);
static_assert(tump::is_type_list_v<A> == false);
static_assert(tump::is_type_list_v<B<int(1), float>> == false);
static_assert(tump::is_type_list_v<C<std::vector, float>> == false);
static_assert(tump::is_type_list_v<std::array<int, 2>> == false);
static_assert(tump::eval<tump::is_type_list, tump::vlist<>>::value == false);

// 真と判定されるもの例
static_assert(tump::TypeList<tump::list<int, float>> == true);
static_assert(tump::is_type_list_v<D<int, float>> == true);
static_assert(tump::is_type_list_v<tump::list<>> == true);
static_assert(tump::is_type_list_v<std::tuple<int, float>> == true);
static_assert(tump::is_type_list_v<std::vector<int>> == true);
static_assert(tump::eval<tump::is_type_list, tump::_apply, tump::make_empty, std::tuple<int>>::value == true);

// コンセプト TypeList によるテンプレートパラメータの制約
template <tump::TypeList List>
struct E {};

E<tump::list<>>;
E<std::vector<int>>;
E<std::tuple<int, float, double>>;
E<tump::make_empty_t<std::tuple<int, float>>>;

// 下記は TypeList の制約に抵触するため、
// コメントアウトを外すとコンパイルエラー

// E<int>;
// E<A>;
// E<B<int(1), float>>;
// E<C<std::vector, float>>;
// E<tump::vlist<int(1), float(2), double(3)>>;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
