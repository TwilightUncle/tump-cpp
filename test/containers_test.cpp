#include <gtest/gtest.h>
#include <tump/metafunction/expression.hpp>
#include <tump/containers.hpp>

TEST(TumpContainersTest, FunctorTest)
{
    // 第一則(それぞれ生成された関数実行結果の比較)
    using functor1 = tump::add_const;
    constexpr auto case1 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor1, tump::_doll, int>,
        tump::exp<tump::type_identity, functor1, tump::_doll, int>
    >;
    ASSERT_TRUE(case1);

    // リストの第一則
    using functor2 = tump::list<int, short, long>;
    constexpr auto case2 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor2>,
        tump::exp<tump::type_identity, functor2>
    >;
    ASSERT_TRUE(case2);

    // 関数の第二則
    using functor3 = tump::type_identity;
    constexpr auto case3 = std::is_same_v<
        tump::exp<tump::exp<
            tump::fmap, tump::_doll,
            tump::add_const, tump::_dot, tump::make_unsigned
        >, functor3, tump::_doll, int>,
        tump::exp<tump::exp<
            tump::fmap, tump::add_const, tump::_dot,
            tump::fmap, tump::make_unsigned
        >, functor3, tump::_doll, int>
    >;
    ASSERT_TRUE(case3);

    // リストの第二則
    constexpr auto case4 = std::is_same_v<
        tump::exp<tump::exp<
            tump::fmap, tump::_doll,
            tump::add_const, tump::_dot, tump::make_unsigned
        >, functor2>,
        tump::exp<tump::exp<
            tump::fmap, tump::add_const, tump::_dot,
            tump::fmap, tump::make_unsigned
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
