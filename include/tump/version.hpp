// ----------------------------------
// 言語バージョン、
// 依存ライブラリバージョン、
// 本ライブラリバージョン等
// 制御
// ----------------------------------

// とりあえず、下記のように値を管理
// - メジャーバージョン: 2 桁
// - マイナーバージョン: 2 桁
// - パッチバージョン: 3 桁
// - プレスリリース(a, b ... をプレスリリースとし、fを安定板と考える): 1 桁
#define TUMP_VERSION_0_1_1 0x00'01'001'fUL
#define TUMP_VERSION_0_1_1_NAME "0.1.1"
// #define TUMP_VERSION_1_0_0_ALPHA 0x01'00'000'aUL
// #define TUMP_VERSION_1_0_0_ALPHA_NAME "1.0.0-alpha"

// 最初に読み込まれたTUMPあるいは、あらかじめバージョン指定されていた場合、
// デフォルトでは当該ソースを読み込むようにする
#if !defined(TUMP_VERSION) || TUMP_VERSION == TUMP_VERSION_0_1_1
    #define TUMP_VERSION TUMP_VERSION_0_1_1
    #define TUMP_VERSION_NAME TUMP_VERSION_0_1_1_NAME
    #ifndef _TUMP_SET_USING_NAMESPACE
        #define _TUMP_SET_USING_NAMESPACE
        namespace tump = tump_0_1_1;
    #endif
#endif

// c++20対応テスト
#ifndef TUMP_ENABLE_CPP20
    #if __cplusplus == 202002L || defined(_MSVC_LANG) && _MSVC_LANG == 202002L
        #define TUMP_ENABLE_CPP20
    #endif
#endif

// c++23対応テスト
#ifndef TUMP_ENABLE_CPP23
    #if __cplusplus > 202002L || defined(_MSVC_LANG) && _MSVC_LANG > 202002L
        #define TUMP_ENABLE_CPP23
    #endif
#endif
