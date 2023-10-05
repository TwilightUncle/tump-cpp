#include <gtest/gtest.h>
#include <tump/containers.hpp>

TEST(TumpContainersTest, FunctorTest)
{
    // 第一則(それぞれ生成された関数実行結果の比較)
    using functor1 = tump::add_const;
    constexpr auto case1 = std::is_same_v<
        tump::invoke_t<
            tump::fmap_t<tump::type_identity, functor1>,
            int
        >,
        tump::invoke_t<
            std::type_identity_t<functor1>,
            int
        >
    >;
    ASSERT_TRUE(case1);

    // リストの第一則
    using functor2 = tump::list<int, short, long>;
    constexpr auto case2 = std::is_same_v<
        tump::fmap_t<tump::type_identity, functor2>,
        std::type_identity_t<functor2>
    >;
    ASSERT_TRUE(case2);

    // 関数の第二則
    using functor3 = tump::type_identity;
    constexpr auto case3 = std::is_same_v<
        tump::invoke_t<
            tump::fmap_t<tump::compose_t<
                tump::add_const,
                tump::make_unsigned
            >, functor3>,
            int
        >,
        tump::invoke_t<
            tump::invoke_t<tump::compose_t<
                tump::bind<tump::fmap, tump::add_const>,
                tump::bind<tump::fmap, tump::make_unsigned>
            >, functor3>,
            int
        >
    >;
    ASSERT_TRUE(case3);

    // リストの第二則
    constexpr auto case4 = std::is_same_v<
        tump::fmap_t<tump::compose_t<
            tump::add_const,
            tump::make_unsigned
        >, functor2>,
        tump::invoke_t<tump::compose_t<
            tump::bind<tump::fmap, tump::add_const>,
            tump::bind<tump::fmap, tump::make_unsigned>
        >, functor2>
    >;
    ASSERT_TRUE(case4);
}

TEST(TumpContainersTest, ApplicativeTest)
{
    // アプリカティブのN則を式で再現すればテストになるであろう
    // using applicative1 = tump::list<int, short, long>;
    // constexpr auto case1 = std::is_same_v<
    //     tump::ast_t<
    //         tump::pure<tump::type_identity>,
    //         applicative1
    //     >,
    //     applicative1
    // >;
    // ASSERT_TRUE(case1);

    // constexpr auto case2 = 
}
