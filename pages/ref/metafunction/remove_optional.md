---
title: remove_optional - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <class T>
        struct remove_optional {};
    }

    // 第一級関数化
    using remove_optional = cbk<fn::remove_optional, 1>;
    
    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <class T>
    using remove_optional_t = typename fn::remove_optional<T>::type;
}
```

### パラメータ・メンバ

- T - 任意の型

## 概要

`tump::remove_optional`は、任意の型が`std::optional`で包まれている場合、`std::optional`を除去するメタ関数です。

`std::optional`で包まれていない型に対しては、特に何も処理を行わないため、`tump::remove_optional`を適用しようとしている型が、`std::optional`で包まれているかかどうかを考慮する必要はありません。
