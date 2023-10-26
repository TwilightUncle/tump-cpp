---
title: メタ関数の第一級関数化と適用 - TumpCpp リファレンス
---

TumpCpp の式では、第一級関数化したメタ関数を利用するため、TumpCpp で定義されていないようなメタ関数を使用したいときは、前準備として第一級関数化する必要があります。

また、[{`tump::exp`または`tump::eval`|ref/expression/exp}]では、部分適用や適用など、自動的に識別されますが、[{`tump::exp`または`tump::eval`|ref/expression/exp}]とは異なった基準で適用を実施したい場合が考えられます。  
上記のような場合、下記一覧に記載されたメタ関数やテンプレートクラスを使用します。

## 一覧

| メタ関数・テンプレートクラス名 | 概要 |
| --- | :--- |
| [{callback/cbk|ref/invocable/callback}] | メタ関数を第一級関数化します。 |
| [{partial_apply|ref/invocable/partial_apply}] | 第一級関数化したメタ関数へ引数の部分適用を行います。 |
| [{Invocable|ref/invocable/invocable}] | ある型が第一級関数化したメタ関数かどうか判定する制約です。 |
| [{invoke|ref/invocable/invoke}] | 第一級関数化したメタ関数を実行します。 |
| [{invoke_list|ref/invocable/invoke_list}] | 第一級関数化したメタ関数を実行します。引数をリストとしてまとめて渡します。 |
| [{apply|ref/invocable/apply}] | 第一級関数化したメタ関数へ引数の適用を行います。引数の数によって実行か部分適用かを自動的に判断します。 |
| [{flip|ref/invocable/flip}] | 2 引数のメタ関数について、引数を指定する順序を入れ替えた上で実行します。 |
| [{compose|ref/invocable/compose}] | 複数のメタ関数を合成します。 |
