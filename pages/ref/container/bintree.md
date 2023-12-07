---
title: バイナリツリー - TumpCpp リファレンス
---

TumpCpp における**バイナリツリー**は、[{`tump::list`|ref/container/list}]と同じように、任意数の型パラメータを保持するテンプレートクラスです。

## 概要

バイナリツリーが持つパラメータは、[{`tump::comparing_type`|ref/metafunction/comparing_type}]により指定されたルールに従った大小関係を、常に保持する性質を持ちます。

また、バイナリツリーは[{`tump::TypeList`|ref/container/method/is_type_list}]および、[{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]の制約において真と判定され、[{`tump::list`|ref/container/list}]で使用可能なメタ関数をすべて使用することができます。

[{`tump::list`|ref/container/list}]と共有しているメタ関数については、[{`tump::list`|ref/container/list}]のリファレンスを参照ください。

## listのメタ関数を利用する際の留意点

バイナリツリーが持つ型パラメータは常に大小関係が維持されています。  
そのため、パラメータの並びによって結果が異なるメタ関数は、想定と異なる動作となる場合がありますので注意が必要です。  
例えば、影響の大きいメタ関数の一部として下記表のようなものがあります。

| メタ関数 | バイナリツリーに適用した時の動作 |
| --- | --- |
| [{`tump::push_front`|ref/container/method/push_front}] | 本来、リストの先頭にパラメータを追加する機能を持ちます。しかし、バイナリツリーに適用した場合は大小関係の判定に従ってパラメータが挿入され、関数名と実際の動作が異なってしまいます。 |
| [{`tump::pop_back`|ref/container/method/pop_back}] | バイナリツリーが持つ型パラメータは常に大小関係が保持されており、一番大きいと判定された型が最後尾に並びます。そのため、`pop_back`をバイナリツリーに適用した際は最大と判定される型が削除されます。 |
| [{`tump::index_of`|ref/container/method/index_of}] | バイナリツリーが持つ型パラメータは大小関係に従って並んでいるため、得られる結果は、大小関係の順位となります。<br>※小さいと判定された型ほど`0`に近い値が返却されます。 |
| [{`tump::reverse`|ref/container/method/reverse}] | バイナリツリーに対して適用しても特に意味はありません。コンパイル時に余計な計算資源を消費することが考えられますので、基本的には使用しないほうが良いです。 |
| [{`tump::replace`|ref/container/method/replace}] | バイナリツリーに適用した際、置き換え前後の型と、他パラメータの大小関係の判定が異なる場合、置き換え後の型を挿入する位置が、置き換え前の型があった位置と異なります。 |

## バイナリツリー用メタ関数・概念

バイナリツリーに関するメタ関数や概念の一覧です。

### メタ関数の生成

下記の 2 通りの生成方法があります。

| メタ関数・概念の名称 | 説明 |
| --- | --- |
| [{`tump::empty_bintree`|ref/container/method/empty_bintree}] | 空のバイナリツリーです。 |
| [{`tump::to_bintree`|ref/container/method/to_bintree}] | 型のリストからバイナリツリーを作成します。 |

### 情報取得

| メタ関数・概念の名称 | 説明 |
| --- | --- |
| [{`tump::is_bintree`|ref/container/method/is_bintree}] | バイナリツリーかどうか判定します。 |
| [{`tump::BinaryTree`|ref/container/method/is_bintree}] | バイナリツリーかどうか判定する制約です。 |

### 要素アクセス用メタ関数

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::get_min`|ref/container/method/get_min}] | バイナリツリーが保持する要素のうち、最大と判定されるものを取得します。 |
| [{`tump::get_max`|ref/container/method/get_max}] | バイナリツリーが保持する要素のうち、最小と判定されるものを取得します。 |

### 操作用メタ関数

| メタ関数の名称 | 説明 |
| --- | --- |
| [{`tump::push`|ref/container/method/bintree_push}] | バイナリツリーに要素を挿入します。大小関係を比較し、適切な位置に要素が配置されます。 |
| [{`tump::pop_min`|ref/container/method/pop_min}] | バイナリツリーから最小と判定される要素を取り除きます。 |
| [{`tump::pop_max`|ref/container/method/pop_max}] | バイナリツリーから最大と判定される要素を取り除きます。 |
| [{`tump::flatten`|ref/container/method/flatten}] | バイナリツリーを[{`tump::list`|ref/container/list}]に変換します。結果のリストが持つ要素の並びは、バイナリツリーの要素の大小関係に準じています。 |

## 関連リンク

- [{`tump::TypeList`|ref/container/method/is_type_list}]
- [{`tump::TypeListOrValueList`|ref/container/method/is_t_or_v_list}]
- [{`tump::list`|ref/container/list}]
