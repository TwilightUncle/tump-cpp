---
title: to_btree - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <TypeList List, class Comparing = comparing_size>
        struct to_btree {};
    }

    // 第一級関数化
    using to_btree = cbk<fn::to_btree, 2>;
    using to_size_btree = partial_apply<flip, to_btree, comparing_size>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <TypeList List, class Comparing = comparing_size>
    using to_btree_t = typename fn::to_btree<List, Comparing>::type;
}
```

### パラメータ

- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型
- Comparing - [{`tump::comparing_type`|ref/metafunction/comparing_type}]で作成した、型の比較クラス

## 概要

`tump::to_btree`は、テンプレートパラメータ`List`をバイナリツリー[{`tump::btree`|ref/container/btree}]に変換するメタ関数です。  
バイナリツリーの構築は、パラメータ`Comparing`によって定められた大小の基準で行われ、デフォルトでは`sizeof`による比較が行われます。

詳しくは**[{btree|ref/container/btree}]**を参照ください。

## 関連リンク

- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::btree`|ref/container/btree}]
- [{`tump::comparing_type`|ref/metafunction/comparing_type}]
