---
title: 定義済みメタ関数 - TumpCpp リファレンス
---

TumpCpp で定義されたメタ関数についてのリファレンスです。

## 一覧

| メタ関数・テンプレートクラス名 | 概要 |
| --- | :--- |
| [{標準ライブラリのメタ関数の第一級関数|ref/metafunction/std}] | 主に、標準ライブラリの`<type_traits>`に定義されたメタ関数を第一級関数化したものを定義しています。 |
| [{to_true|ref/metafunction/to_true}] | 必ず`std::true_type`を返却します。 |
| [{left|ref/metafunction/left}] | 2 つの引数を受け取り、常に第一引数の型を返却します。 |
| [{right|ref/metafunction/right}] | 2 つの引数を受け取り、常に第二引数の型を返却します。 |
| [{through_if|ref/metafunction/through_if}] | 条件に合致する型が指定された場合、その型をそのまま返却します。そうでなければデフォルトの型を返却します。 |
| [{block_if|ref/metafunction/block_if}] | 条件に合致しない型が指定された場合、その型をそのまま返却します。そうでなければデフォルトの型を返却します。 |
| [{vwrap|ref/metafunction/vwrap}] | 非型テンプレートパラメータを包み込んで、型として利用できるようにします。 |
| [{comparing_type|ref/metafunction/comparing_type}] | 型の比較を行うメタ関数群を生成します。 |
| [{add_optional|ref/metafunction/add_optional}] | 型を std::optional で包みます。 |
| [{remove_optional|ref/metafunction/remove_optional}] | 型から std::optional を除去します。 |
