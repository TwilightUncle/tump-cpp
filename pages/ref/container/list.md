---
title: list - TumpCpp リファレンス
---

```cpp
namespace tump {
    template <class... Types>
    struct list {};
}
```

## 概要

型のテンプレートパラメータパック`Types`に指定した、任意の数の型を要素として保持します。

## 使い方

`tump::list`は複数の型をまとめて扱ったり、一括で処理を適用したい場合に使います。  
要素が、値か型かの違いはありますが、`std::vector`や`std::list`と同じような用途です。

TumpCpp では、`tump::list`を主な対象とした、いくつかのリスト操作用メタ関数が定義されており、それらと組み合わせて使います。

また、型のみをテンプレートパラメータとして受け取る、任意のテンプレート型も、`tump::list`と同様に型のリストとして扱うことができます。

## リスト用メタ関数・概念

`tump::list`および、型テンプレートパラメータを持つ、任意のテンプレート型に対して使用するためのメタ関数の一覧です。

### 情報取得

| メタ関数・概念の名称 | 説明 |
| --- | --- |
| [{`tump::is_empty`|ref/container/method/is_empty}] | リストが空か判定します。 |
| [{`tump::is_type_list`|ref/container/method/is_type_list}] | 型のリストとして利用できるテンプレート型かどうか判定します。 |
| [{`tump::TypeList`|ref/container/method/is_type_list}] | 型のリストとして利用できるテンプレート型かどうか判定する制約です。 |
| [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}] | 型または、値のリストとして利用できるテンプレート型かどうか判定します。 |
| [{`tump::len`|ref/container/method/len}] | リストの長さを取得します。 |

### 要素アクセス

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::count_if`|ref/container/method/count_if}] | 指定の条件に合致する要素の数を数えます。 |
| [{`tump::exists`|ref/container/method/exists}] | リストの要素に指定の型が含まれるかどうか判定します。 |
| [{`tump::find_if`|ref/container/method/find_if}] | リストの要素から、指定の条件に合致する最初の型を取得します。 |
| [{`tump::get`|ref/container/method/get}] | リスト要素のうち、指定の位置の型を取得します。 |
| [{`tump::get_front`|ref/container/method/get_front}] | リスト要素の先頭の型を取得します。 |
| [{`tump::get_back`|ref/container/method/get_back}] | リスト要素の最後尾の型を取得します。 |
| [{`tump::index_of`|ref/container/method/index_of}] | リストの要素から、指定の型が最初に見つかった位置を取得します。 |
| [{`tump::index_of_if`|ref/container/method/index_of_if}] | リストの要素から、指定の条件に合致する最初の型が見つかった位置を取得します。 |
| [{`tump::is_unique`|ref/container/method/is_unique}] | リストの要素の、重複の有無を判定します。 |

### リスト操作

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::make_empty`|ref/container/method/make_empty}] | 空のリストを作成します。 |
| [{`tump::make_type_list`|ref/container/method/make_type_list}] | 新しいリストを作成します。 |
| [{`tump::concat`|ref/container/method/concat}] | 複数のリストを結合します。 |
| [{`tump::copy`|ref/container/method/copy}] | リストが持つテンプレートパラメータの内容を、別のリストに写します。 |
| [{`tump::filter`|ref/container/method/filter}] | リストが持つテンプレートパラメータから、条件に合致する要素のみ抽出します。 |
| [{`tump::foldl`・`tump::foldr`|ref/container/method/fold}] | 畳み込みを行います。 |
| [{`tump::map`|ref/container/method/map}] | リストが持つ全ての要素に任意の処理を適用します。 |
| [{`tump::map_if`|ref/container/method/map_if}] | リストが持つ要素のうち、指定の条件に合致する要素すべてに、任意の処理を適用します。 |
| [{`tump::pop_front`|ref/container/method/pop_front}] | リストの先頭の要素を削除します。 |
| [{`tump::pop_back`|ref/container/method/pop_back}] | リストの最後尾の要素を削除します。 |
| [{`tump::push_front`|ref/container/method/push_front}] | リストの先頭に要素を挿入します。 |
| [{`tump::push_back`|ref/container/method/push_back}] | リストの最後尾に要素を挿入します。 |
| [{`tump::push_front_if`|ref/container/method/push_front_if}] | リストの先頭に、指定の条件に一致する要素を挿入します。 |
| [{`tump::push_back_if`|ref/container/method/push_back_if}] | リストの先頭に、指定の条件に一致する要素を挿入します。 |
| [{`tump::remove_if`|ref/container/method/remove_if}] | リストが持つテンプレートパラメータから、条件に合致する要素のみ削除します。 |
| [{`tump::replace`|ref/container/method/replace}] | リストが持つ要素のうち、指定の型を新しい型で置き換えます。 |
| [{`tump::replace_if`|ref/container/method/replace_if}] | リストが持つ要素のうち、指定の条件に合致する型を新しい型で置き換えます。 |
| [{`tump::reverse`|ref/container/method/reverse}] | リストの要素の並びを反転します。 |
| [{`tump::slice`|ref/container/method/slice}] | リストの指定の範囲を切り出します。 |
| [{`tump::unique`|ref/container/method/unique}] | リストの重複している要素を削除します。 |
| [{`tump::zip`|ref/container/method/zip}] | 2 つのリストから要素を 1 つずつ取り出した組のリストを生成します。 |

### その他

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::fmap`|ref/container/method/fmap}] | リストがファンクタとして振舞うためのメタ関数です。機能は[{`tump::map`|ref/container/method/map}]とまったく同じです。 |
| [{`tump::pure`|ref/container/method/pure}] | メタ関数を、アプリカティブファンクタに適用可能な形に持ち上げます。 |
| [{`tump::ap`|ref/container/method/ap}] | リストがアプリカティブファンクタとして振舞うためのメタ関数です。アプリカティブファンクタに持ち上げられたメタ関数を、アプリカティブファンクタに適用します。 |
| [{`tump::ret`|ref/container/method/ret}] | メタ関数を、モナドに適用可能な形に持ち上げます。[{`tump::pure`|ref/container/method/pure}]の別名です。 |
| [{`tump::bind`|ref/container/method/bind}] | モナドから値を取り出し、モナドを返却するメタ関数に食わせます。 |

## 例

```cpp
#include <tuple>
#include <type_traits>
#include <tump.cpp>

// map でテンプレートパラメータパックに一括適用。
// 型のテンプレートパラメータのみとるテンプレート型であれば、
// std::tuple や、std::is_same のようなテンプレート型でもOK。
using list1 = tump::eval<tump::map, tump::add_const, tump::list<int, float, char>>;
using list2 = tump::eval<tump::map, tump::add_const, std::tuple<int, float, char>>;
using list3 = tump::eval<tump::map, tump::add_const, std::is_same<int, float>>;

// 全てのテンプレートパラメタに const がついていることの確認。
static_assert(std::is_same_v<list1, tump::list<const int, const float, const char>>);
static_assert(std::is_same_v<list2, std::tuple<const int, const float, const char>>);
static_assert(std::is_same_v<list3, std::is_same<const int, const float>>);

int main() {}
```

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
- [{`tump::add_const`|ref/metafunction/std}]
