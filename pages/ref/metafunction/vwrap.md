---
title: vwrap - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <auto V>
    struct vwrap
    {
        using value_type = decltype(V);
        using type = vwrap<V>;
        static constexpr auto value = V;
    };
}
```

### パラメータ・メンバ

- V - 任意の非型パラメータ
- value_type - 包んだパラメータの型
- type - 自身をそのまま格納
- value - 包んだ値をそのまま格納

## 概要

`tump::vwrap`は、任意の非型パラメータを型の文脈で扱うことができるように包みます。

`std::integral_constant`と同じように使いますが、特に型を指定する必要はありません。
