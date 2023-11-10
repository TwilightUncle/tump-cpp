---
title: to_true - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class T>
        using to_true = std::true_type;
    }

    // 第一級関数化
    using to_true = cbk<fn::to_true, 1>;
    
    // 定数メンバ value 呼び出し省略のエイリアステンプレート
    template <class T>
    constexpr auto to_true_v = fn::to_true<T>::value;
}
```

### パラメータ

- T - 任意の型

## 概要

`tump::to_true`は、引数として任意の型を 1 つだけ受け取り、常に真として、`std::true_type`を返却するメタ関数です。

どのような型を渡しても真と判定されることから、型制約を指定する際に、制限がないことを明示的に示すような用途を想定しています。

例えば、TumpCpp では、比較用のメタ関数を定義する[{`tump::comparing_type`|ref/metafunction/comparing_type}]を定義しており、使用する際には比較可能な型の制約を行うメタ関数の指定が必要です。  
その際、あらゆる型で比較可能な処理を定義する場合は、`tump::to_true`を制約として指定することになります。

## 例

```cpp
#include <vector>
#include <tump.hpp>

// どのような型を渡しても真となる
static_assert(tump::to_true_v<void> == true);
static_assert(tump::to_true_v<int*> == true);
static_assert(tump::eval<tump::to_true, std::vector<int>>::value == true);
static_assert(tump::eval<tump::to_true, tump::to_true>::value == true);

// 例として、grater > 任意の型のサイズ となるような比較メタ関数を生成
template <class T> struct grater {};

template <class L, class R>
struct my_compare : public std::integral_constant<
    int, sizeof(L) - sizeof(R)
> {};
template <class L, class R>
struct my_compare<grater<L>, R> : public std::integral_constant<int, 1> {};
template <class L, class R>
struct my_compare<L, grater<R>> : public std::integral_constant<int, -1> {};
template <class L, class R>
struct my_compare<grater<L>, grater<R>> : public my_compare<L, R> {};
template <class T>
struct my_compare<T, void> : public std::integral_constant<int, 1> {};
template <class T>
struct my_compare<void, T> : public std::integral_constant<int, -1> {};

// 比較メタ関数の生成
// 全ての型で比較可能なように、第二引数に to_true を制約として指定
using my_comparing = tump::comparing_type<
    tump::cbk<my_compare, 2>,
    tump::to_true
>;

static_assert(my_comparing::lt_v<void, int> == true);
static_assert(my_comparing::lt_v<int, int> == false);
static_assert(my_comparing::le_v<std::int8_t, std::int16_t> == true);
static_assert(my_comparing::le_v<std::int8_t, std::int8_t> == true);
static_assert(my_comparing::eq_v<void, int> == false);
static_assert(my_comparing::eq_v<int, int> == true);

static_assert(tump::eval<my_comparing::gt, grater<void>, int>::value == true);
static_assert(tump::eval<my_comparing::gt, grater<int>, grater<int>>::value == false);
static_assert(tump::eval<my_comparing::ge, std::int16_t, grater<std::int16_t>>::value == false);
static_assert(tump::eval<my_comparing::ge, std::int8_t, std::int8_t>::value == true);
static_assert(tump::eval<my_comparing::ne, std::int8_t, std::int8_t>::value == false);
static_assert(tump::eval<my_comparing::ne, grater<std::int8_t>, std::int8_t>::value == true);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::cbk`|ref/invocable/callback}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
