---
title: list - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <auto... Values>
    struct vlist {};
}
```

## 概要

型のテンプレートパラメータパック`Values`に指定した、任意の数の非型パラメータ(値)を要素として保持します。

## 使い方

`tump::vlist`は複数の非型パラメータをまとめて扱ったり、一括で処理を適用したい場合に使います。  
非型パラメータを保持しながらも、型であるため、テンプレートメタプログラミングにおけるタプルとして使用します。

[{`tump::list`|ref/container/list}]と一部のメタ関数を共有しており、[{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]の制約の場所で使用することができます。  
[{`tump::TypeList`|ref/container/method/is_type_list}]の制約の場所では、`tump::vlist`を使用できません。

## リスト用メタ関数・概念

`tump::vlist`および、型テンプレートパラメータを持つ、任意のテンプレート型に対して使用するためのメタ関数の一覧です。

### 情報取得

| メタ関数・概念の名称 | 説明 |
| --- | --- |
| [{`tump::is_empty`|ref/container/method/is_empty}] | リストが空か判定します。 |
| [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}] | 型または、値のリストとして利用できるテンプレート型かどうか判定します。 |
| [{`tump::len`|ref/container/method/len}] | リストの長さを取得します。 |

### 要素アクセス

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::get`|ref/container/method/get}] | リスト要素のうち、指定の位置の型を取得します。 |
| [{`tump::get_front`|ref/container/method/get_front}] | リスト要素の先頭の型を取得します。 |
| [{`tump::get_back`|ref/container/method/get_back}] | リスト要素の最後尾の型を取得します。 |
| [{`tump::is_unique`|ref/container/method/is_unique}] | リストの要素の、重複の有無を判定します。 |
| [{`tump::mp_min`|ref/container/method/mp_min}] | リストの要素のうち、最小と判定される型を取得します。 |
| [{`tump::mp_max`|ref/container/method/mp_max}] | リストの要素のうち、最大と判定される型を取得します。 |

### リスト操作

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::make_empty`|ref/container/method/make_empty}] | 空のリストを作成します。 |
| [{`tump::fill`|ref/container/method/fill}] | 全て同じ要素で埋めた状態の、新しいリストを作成します。 |
| [{`tump::concat`|ref/container/method/concat}] | 複数のリストを結合します。 |
| [{`tump::reverse`|ref/container/method/reverse}] | リストの要素の並びを反転します。 |
| [{`tump::slice`|ref/container/method/slice}] | リストの指定の範囲を切り出します。 |
| [{`tump::unique`|ref/container/method/unique}] | リストの重複している要素を削除します。 |
