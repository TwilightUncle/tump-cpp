if (CMAKE_PROJECT_NAME STREQUAL "tump")
    # -----------------------------------------------
    # Google Test 取得
    # -----------------------------------------------
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )
    # Google Testの不要なキャッシュ変数をオフにしておく
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    # 親プロジェクトのコンパイラ・リンカ設定を上書きするのを防ぐ（Windowsのみ）
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)

    # -----------------------------------------------
    # テストのビルド
    # -----------------------------------------------
    add_executable(tumptest ${TUMP_TESTS})
    
    # ソース列挙
    target_sources(tumptest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/metafunction_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithm_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/containers_test.cpp
    )

    target_include_directories(tumptest PRIVATE ${tump_SOURCE_DIR}/include)
    target_link_libraries(tumptest PRIVATE gtest_main)
    add_test(NAME tumptest COMMAND tumptest)
endif ()
