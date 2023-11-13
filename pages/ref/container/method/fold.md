---
title: foldl/foldr - TumpCpp リファレンス
---

```cpp
namespace tump {
    namespace fn {
        // 大元のメタ関数定義
        template <InvocableArgN<2> F, class Init, TypeList List>
        struct foldl {};
        
        // 大元のメタ関数定義
        template <InvocableArgN<2> F, class Init, TypeList List>
        struct foldr {};
    }

    // 第一級関数化
    using foldl = cbk<fn::foldl, 3>;

    // 第一級関数化
    using foldr = cbk<fn::foldr, 3>;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldl_t = typename fn::foldl<F, Init, List>::type;

    // メンバ型 type 呼び出し省略のエイリアステンプレート
    template <InvocableArgN<2> F, class Init, TypeList List>
    using foldr_t = typename fn::foldr<F, Init, List>::type;
}
```

### パラメータ

- F - [{`tump::InvocableArgN<2>`|ref/invocable/invocable}]で真と判定されるメタ関数
- Init - 任意の型
- List - [{`tump::TypeList`|ref/container/method/is_type_list}]で真と判定される型のリスト

## 概要

`tump::foldl`および、`tump::foldr`は型のテンプレートパラメータパックを持つ`List`に対して、畳み込みを行うメタ関数です。  
`tump::foldl`は左から、`tump::foldr`は右から畳み込みを行います。

パラメータ`F`に 2 引数のメタ関数を、パラメータ`Init`に蓄積を行う初期型を指定します。

`tump::foldl`と`tump::foldr`の主な違いは、蓄積された結果の型について、`tump::foldl`では`F`の第一引数として喰われますが、`tump::foldr`では第二引数として喰われます。  
そのため、`F`に対して`tump::is_base_of`のように、第一引数と第二引数で役割が異なるようなメタ関数を指定した際に動きが異なる場合があり、注意が必要です。

## 例

TumpCpp ではいくつかのメタ関数の実装に畳み込みを用いています。  
`tump::foldl`を用いて実装が行われているメタ関数の例として、リストの要素の順番を反転する[{`tump::reverse`|ref/container/method/reverse}]があります。  
また、`tump::foldr`を用いて実装が行われているメタ関数の例として、関数合成を行う[{`tump::compose`|ref/invocable/compose}]があります。

## 関連リンク

- [{`tump::InvocableArgN`|ref/invocable/invocable}]
- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::reverse`|ref/container/method/reverse}]
- [{`tump::compose`|ref/invocable/compose}]
- [{`tump::is_base_of`|ref/metafunction/std}]
