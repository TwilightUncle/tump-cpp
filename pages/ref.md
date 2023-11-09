---
title: TumpCpp リファレンス
overview: TumpCpp のリファレンスTOPです。
---

## 概要

リファレンスでは、TumpCpp で実装された各機能の定義や、使い方のサンプルを掲載しています。

## 項目一覧

| 機能の分類 | 概要 | 該当するクラス・関数・概念 |
| --- | :--- | :--- |
| [{式|ref/expression}] | TumpCpp における式のリファレンスです。 | [{exp|ref/expression/exp}], [{sec|ref/expression/sec}], [{lambda|ref/expression/lambda}], [{mp_if|ref/expression/mp_if}], [{guard|ref/expression/guard}] |
| [{メタ関数の第一級関数化と適用|ref/invocable}] | メタ関数を第一級関数として扱うためのリファレンスです。<br>第一級関数への変換、第一級関数の適用(実行)、部分適用が含まれます。 | [{callback|ref/invocable/callback}], [{cbk|ref/invocable/callback}], [{partial_apply|ref/invocable/partial_apply}], [{Invocable|ref/invocable/invocable}] [{invoke|ref/invocable/invoke}], [{invoke_list|ref/invocable/invoke_list}], [{apply|ref/invocable/apply}], [{flip|ref/invocable/flip}], [{compose|ref/invocable/compose}] |
| [{演算子|ref/operator}] | TumpCpp の式で扱う演算子のリファレンスです。 | [{_apply|ref/operator/apply}], [{_dot|ref/operator/dot}], [{_eq|ref/operator/compare}], [{_ne|ref/operator/compare}], [{_or|ref/operator/logical}], [{_and|ref/operator/logical}], [{_elem|ref/operator/elem}], [{_not_elem|ref/operator/elem}], [{_concat|ref/operator/concat}], [{_cons|ref/operator/concat}], [{_fmap|ref/operator/fmap}], [{_ap|ref/operator/ap}], [{_bind|ref/operator/bind}],  [{_op|ref/operator/op}] |
| [{コンテナ|ref/container}] | テンプレートメタプログラミングで利用することができる、リストや木構造などの構造的なテンプレートクラスと、関連する概念のリファレンスです。<br>また、各テンプレートクラスの項には、そのテンプレートクラス用に定義されたメタ関数の説明が含まれる場合があります。 | [{list|ref/container/list}], [{vlist|ref/container/vlist}], [{btree|ref/container/btree}], [{ファンクタ|ref/container/functor}], [{アプリカティブファンクタ|ref/container/applicative}], [{モナド|ref/container/monad}] |
| [{定義済みメタ関数|ref/metafunction}] | TumpCpp で定義されているメタ関数のリファレンスです。 | [{標準ライブラリのメタ関数の第一級関数|ref/metafunction/std}], [{to_true|ref/metafunction/to_true}], [{left|ref/metafunction/left}], [{right|ref/metafunction/right}], [{through_if|ref/metafunction/through_if}], [{block_if|ref/metafunction/block_if}], [{vwrap|ref/metafunction/vwrap}], [{comparing_type|ref/metafunction/comparing_type}] |
| <!--[{マクロ|ref/macro}]-->マクロ | TumpCpp に影響を及ぼすプリプロセッサマクロ定義についてのリファレンスです。 |  |

## 名前空間

全ての機能は名前空間`tump`の下に定義されており、TumpCpp の機能は名前空間`tump`直下に所属している識別子のみの利用で完結できます。  
しかし、TumpCpp における[{式|ref/expression}]の機能を利用せず、定義されているメタ関数のみを利用したい場合は少し異なります。

### 標準ライブラリのメタ関数との、定義内容や命名の違い

TumpCpp では、メタ関数について、下記の定義が行われています。

1. メタ関数の大元の定義
1. メタ関数の評価結果の型を得るための、`::type`呼び出しを省略するエイリアステンプレート定義
1. メタ関数の評価結果の値を得るための、`::value`呼び出しを省略する変数テンプレート定義

しかし、上記に加えて、TumpCpp では下記の定義も行っています。

- **1** を第一級関数化した型エイリアス定義

本ライブラリは、通常のメタ関数を利用することによる煩雑さの軽減を目的の 1 つとして、式の中で第一級関数化したメタ関数を利用するような使い方を想定しています。

そのため、通常のメタ関数の定義は、TumpCpp の機能の実装のために最低限必要なものと位置づけ、ネストした名前空間`tump::fn`の下で定義しています。  
ほとんどのメタ関数は、下記のような形式で所属する名前空間が決まっています。

| メタ関数の状態 | 識別子の命名規則 | 所属する名前空間 |
| :--- | :--- | --- |
| 基本的なメタ関数 | メタ関数名そのまま | `tump::fn` |
| 直接結果型を返却する、メタ関数のエイリアステンプレート | メタ関数名の末尾に`_t`が付与されている | `tump` |
| 直接結果の値を返却する、メタ関数の変数テンプレート |　メタ関数の末尾に`_v`が付与されている | `tump` |
| **第一級関数化したメタ関数** | **メタ関数名そのまま** | `tump` |
