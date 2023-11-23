---
title: TypeListOrValueList - TumpCpp リファレンス
---

```cpp
namespace tump {
    // 制約
    template <class T>
    concept TypeListOrValueList = ...;
}
```

### パラメータ

- T - 任意の型

## 概要

指定のテンプレートパラメータ`T`が、**型**を保持するテンプレート型または、[{`tump::vlist`|ref/container/vlist}]であるかを判定します。  
なお、テンプレートテンプレートパラメータや、型と非型などが入り混じったテンプレートパラメータを受け取るテンプレート型は、偽と判定されます。

## 例

```cpp
#include <tuple>
#include <vector>
#include <tump.hpp>

// テンプレートパラメータなしまたは、
// テンプレートパラメータについて型と非型が入り混じっている場合などは偽と判定される。
struct A {};
template <auto V, class T>
struct B {};
template <template <class> class T, class U>
struct C {};

// テンプレートパラメータが全て型のクラスは真と判定される
template <class T, class U>
struct D {};

// 偽と判定されるものの例
static_assert(tump::TypeListOrValueList<int> == false);
static_assert(tump::TypeListOrValueList<A> == false);
static_assert(tump::TypeListOrValueList<B<int(1), float>> == false);
static_assert(tump::TypeListOrValueList<C<std::vector, float>> == false);
static_assert(tump::TypeListOrValueList<std::array<int, 2>> == false);

// 真と判定されるもの例
static_assert(tump::TypeListOrValueList<tump::list<int, float>> == true);
static_assert(tump::TypeListOrValueList<tump::vlist<int(1), long(2), double(3)>> == true);
static_assert(tump::TypeListOrValueList<tump::list<>> == true);
static_assert(tump::TypeListOrValueList<tump::vlist<>> == true);
static_assert(tump::TypeListOrValueList<D<int, float>> == true);
static_assert(tump::TypeListOrValueList<std::vector<int>> == true);
static_assert(tump::TypeListOrValueList<tump::make_empty_t<std::tuple<int, float>>> == true);
static_assert(tump::TypeListOrValueList<tump::empty_btree<>> == true);
static_assert(tump::TypeListOrValueList<tump::to_btree_t<std::tuple<int, float>>> == true);

// コンセプト TypeList によるテンプレートパラメータの制約
template <tump::TypeListOrValueList List>
struct E {};

E<tump::list<>>;
E<tump::vlist<1, nullptr>>;
E<std::vector<int>>;
E<std::tuple<int, float, double>>;
E<tump::make_empty_t<std::tuple<int, float>>>;

// 下記は TypeList の制約に抵触するため、
// コメントアウトを外すとコンパイルエラー

// E<int>;
// E<A>;
// E<B<int(1), float>>;
// E<C<std::vector, float>>;

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::list`|ref/container/list}]
- [{`tump::vlist`|ref/container/vlist}]
- [{バイナリツリー|ref/container/btree}]
- [{`tump::empty_btree`|ref/container/btree}]
- [{`tump::make_empty`|ref/container/method/make_empty}]
- [{`tump::to_btree`|ref/container/method/to_btree}]
