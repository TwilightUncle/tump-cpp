---
title: add_optional - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class T>
        struct add_optional {};
    }

    // 第一級関数化
    using add_optional = cbk<fn::add_optional, 1>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <class T>
    using add_optional_t = typename fn::add_optional<T>::type;
}
```

### パラメータ・メンバ

- T - 任意の型

## 概要

`tump::add_optional`は、任意の型を`std::optional`で包みます。  
C++ における、NULL許容型を生成するようなメタ関数です。

通常、型`T`を`std::optional`で包むのであれば、直接`std::optional<T>`と記述することで事足ります。  
しかし、[{`tump::map`|ref/container/method/map}]を使って、リストの全ての要素を`std::optional`で包もうとしたり、条件付きで`std::optional`を付与するかどうか切り分けたい場合、メタ関数であると都合がよいため、`tump::add_optional`は定義されています。

なお、すでに`std::optional`に包まれている型が指定された場合、受け取った型を直接返却するため、`tump::add_optional`を適用しようとしている型が、すでに`std::optional`で包まれているかかどうかを考慮する必要はありません。

また、`tump::add_optional_t`は形式的に定義されたものであり、下記の 2 つの式は同義のため特に使う意味はありません。

- `std::optional<T>`
- `tump::add_optional_t<T>`
