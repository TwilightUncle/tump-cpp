// ----------------------------------
// 言語バージョン、
// 依存ライブラリバージョン、
// 本ライブラリバージョン等
// 制御
// ----------------------------------

#define TUMP_VERSION_1_0_0 100'000'0000
#define TUMP_VERSION_1_0_0_NAME "1.0.0"

#if !defined(TUMP_VERSION_1) || TUMP_VERSION_1 < TUMP_VERSION_1_0_0
    // 未定義または下位互換しか読み込まれていなかったら再定義
    #define TUMP_VERSION_1 TUMP_VERSION_1_0_0
    #define TUMP_VERSION_1_NAME TUMP_VERSION_1_0_0_NAME
#endif

// 最初に読み込まれたTUMPあるいは、あらかじめバージョン指定されていた場合、
// デフォルトでは当該ソースを読み込むようにする
#if !defined(TUMP_VERSION) || TUMP_VERSION == TUMP_VERSION_1_0_0
    #define TUMP_VERSION TUMP_VERSION_1_0_0
    #define TUMP_VERSION_NAME TUMP_VERSION_1_0_0_NAME
    #ifndef _TUMP_SET_USING_NAMESPACE
        #define _TUMP_SET_USING_NAMESPACE
        namespace tump = tump_1_0_0;
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
