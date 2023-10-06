#include <gtest/gtest.h>
#include <tump/containers.hpp>
#include <tump/metafunction/expression.hpp>

TEST(TumpContainersTest, FunctorTest)
{
    using functor1 = tump::add_const;
    constexpr auto case1 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor1, tump::_doll, int>,
        tump::exp<tump::type_identity, functor1, tump::_doll, int>
    >;
    ASSERT_TRUE(case1);

    using functor2 = tump::list<int, short, long>;
    constexpr auto case2 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor2>,
        tump::exp<tump::type_identity, functor2>
    >;
    ASSERT_TRUE(case2);

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
    using applicative1 = tump::list<int, short, long>;
    constexpr auto case1 = std::is_same_v<
        tump::exp<tump::pure, tump::type_identity, tump::_ap, applicative1>,
        applicative1
    >;
    ASSERT_TRUE(case1);
}
