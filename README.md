# tump-cpp

ヘッダオンリーの C++20 向け、テンプレートメタプログラミング支援ライブラリ。  
本ライブラリを用いることで、テンプレートメタプログラミングへ関数型のパラダイムの式を導入し、複雑な型操作/型判定の実装を容易に行うことができます。

主に、下記のような機能を持ちます。

-   テンプレートクラスであるメタ関数を、テンプレートパラメータの指定なしの状態で、型の文脈上で扱うことを可能とする。
    いわゆる第一級関数。
-   メタ関数の合成や部分適用による、余計な型定義の削減。
-   関数型のパラダイムの式導入。

一方で、型制約などの実装が甘く、複雑なテンプレート型の実体化の過程を経るため、テンプレートパラメータ指定ミスなどによる、コンパイルエラー出力は圧巻です。  

## ドキュメント

https://twilightuncle.github.io/tump-cpp.doc/

## 使い方

任意の場所に本ライブラリを展開し、プロジェクトのインクルードディレクトリに下記パスを追加してください。

- `path/to/tump-cpp/include`

そのうえで、ソースコードに下記を記載することで全ての機能を使用できます。

- `#include <tump.hpp>`

全ての機能は、名前空間`tump`において定義されています。

## 例

例として、テンプレートパラメータパックの全ての整数型を符号なし定数にしてみます。

```cpp
#include <tump.hpp>

using result_list = tump::eval<
    // パラメータパックのうち、整数型のみを符号なし定数に置き換える関数作成
    tump::exp<
        tump::map_if, tump::is_integral,
        tump::_apply,
        tump::add_const, tump::_dot, tump::make_unsigned
    >,
    // 実行対象の型リスト
    tump::list<int, float, void, long, char, double>
>;

// 結果型の確認
static_assert(std::is_same_v<
    result_list,
    tump::list<const unsigned int, float, void, const unsigned long, const unsigned char, double>
>);

int main() {}
```

`tump::_apply`は左オペランドのメタ関数を右オペランドの型に適用するだけの演算子で、優先度が最も低いため、式の評価順序の制御に使います。  
Haskell の `$` 演算子の模倣です。

`tump::_dot`は左右のオペランドのメタ関数を合成します。

## 動作確認環境

C++20を有効にした状態の、下記の環境/コンパイラにおいてコンパイルし、動作を確認しています。

- Windows11
    - Visual Studio 2022 付属の VC++
- ubuntu 22.04 (Docker)
    - GCC: 10, 11, 12
    - Clang: 12, 13, 14
