#ifndef TUMP_INCLUDE_GUARD_TUMP_VERSION_HPP
#define TUMP_INCLUDE_GUARD_TUMP_VERSION_HPP

    // c++20対応テスト
    #if __cplusplus == 202002L
        #define TUMP_ENABLE_CPP20
    #else // __cplusplus > 202002L
        #ifdef _MSVC_LANG
            #if _MSVC_LANG == 202002L
                #define TUMP_ENABLE_CPP20
            #endif // _MSVC_LANG > 202002L
        #endif // _MSVC_LANG
    #endif // __cplusplus > 202002L

    // c++23対応テスト
    #if __cplusplus > 202002L
        #define TUMP_ENABLE_CPP23
    #else // __cplusplus > 202002L
        #ifdef _MSVC_LANG
            #if _MSVC_LANG > 202002L
                #define TUMP_ENABLE_CPP23
            #endif // _MSVC_LANG > 202002L
        #endif // _MSVC_LANG
    #endif // __cplusplus > 202002L

#endif // TUMP_INCLUDE_GUARD_TUMP_VERSION_HPP
