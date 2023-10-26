---
title: マクロ - TumpCpp リファレンス
overview: 
---

TumpCpp のプリプロセッサマクロについてのリファレンスです。  
ライブラリの配置やインクルードパスの設定など、コンパイルする構成の制御を行います。

## TUMP_COMMON_INCLUDE

```cpp
#define TUMP_COMMON_INCLUDE(path)
```

### 概要

このマクロ関数は、TumpCpp におけるヘッダファイルのインクルードパスを制御します。

TumpCpp のライブラリ内では、標準ライブラリを除いた全てのインクルードが本マクロを用いて行われています。  
そのため、本ライブラリを読み込むより先にこのマクロ関数を定義することで、本ライブラリにインクルードの基準のパスを伝えることができます。

具体的には、プロジェクトへの追加インクルードパスの設定を避けたり、インクルードを行う際の基準のディレクトリをずらすような場合に、本ライブラリを利用する側のソースであらかじめこのマクロ関数を定義してください。

デフォルトでは、下記ソースのように展開されます。

```cpp
// デフォルトでは、下記 2 つのインクルードが等価
#include TUMP_COMMON_INCLUDE(path/to/header.hpp)
#include <tump/path/to/header.hpp>
```

### パラメータ

- `path` : 基準となるディレクトリ以降のファイルパスを指定します。

### 例

本ライブラリを利用するプロジェクトディレクトリ配下に、本ライブラリを直接展開し、追加のインクルードディレクトリの設定を行わない場合を想定します。  
下記のようなディレクトリ構成とします。

```Tree
path/to/project/
├── submodules/
│   └── tump-cpp/include/
│       ├── tump.hpp
└── main.cpp
```

下記の`main.cpp`では、先頭で`TUMP_COMMON_INCLUDE`を定義することで、インクルードパスの設定なしで TumpCpp を使用できるようにしています。

<!-- TODO: 下記のビルドを検証すること -->
```cpp
// main.hpp

// tump.hpp の読み込み前にマクロ定義
#define TUMP_COMMON_INCLUDE(path) #submodules/tump/include/path

// #include "submodules/tump/include/tump.hpp" と等価
#include TUMP_COMMON_INCLUDE(tump.hpp)

using result_type = tump::eval<tump::is_same, int, int>;
static_assert(result_type::value);

int main() {}
```
