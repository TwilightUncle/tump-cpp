#include <gtest/gtest.h>
#include <tump/containers.hpp>
#include <tump/metafunction/expression.hpp>

TEST(TumpContainersTest, FunctorTest)
{
    // function
    using functor1 = tump::add_const;
    constexpr auto case1 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor1, tump::_doll, int>,
        tump::exp<tump::type_identity, functor1, tump::_doll, int>
    >;
    ASSERT_TRUE(case1);

    // list
    using functor2 = tump::list<int, short, long>;
    constexpr auto case2 = std::is_same_v<
        tump::exp<tump::fmap, tump::type_identity, functor2>,
        tump::exp<tump::type_identity, functor2>
    >;
    ASSERT_TRUE(case2);

    // function
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

    // list
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
    // common
    constexpr auto case1 = std::is_same_v<
        tump::exp<tump::pure, tump::make_unsigned, tump::_ap, tump::pure, char>,
        tump::pure_t<unsigned char>
    >;
    ASSERT_TRUE(case1);

    // list
    using applicative1 = tump::list<unsigned short, long>;
    using applicative2 = tump::list<tump::add_const, tump::add_pointer>;
    using applicative3 = tump::list<tump::make_signed, tump::make_unsigned>;
    constexpr auto case2 = std::is_same_v<
        tump::exp<tump::pure, tump::type_identity, tump::_ap, applicative1>,
        applicative1
    >;
    ASSERT_TRUE(case2);

    constexpr auto case3 = std::is_same_v<
        tump::exp<tump::pure, tump::compose, tump::_ap, applicative2, tump::_ap, applicative3, tump::_ap, applicative1>,
        tump::exp<applicative2, tump::_ap, tump::exp<applicative3, tump::_ap, applicative1>>
    >;
    ASSERT_TRUE(case3);

    constexpr auto case4 = std::is_same_v<
        tump::exp<applicative2, tump::_ap, tump::pure, char>,
        tump::exp<tump::pure, tump::exp<tump::flip, tump::cbk<tump::fn::apply, 2>, tump::_doll, char>, tump::_ap, applicative2>
    >;
    ASSERT_TRUE(case4);

    constexpr auto case5 = std::is_same_v<
        tump::exp<tump::compose, tump::_fmap, applicative2, tump::_ap, applicative3, tump::_ap, applicative1>,
        tump::list<
            const signed short, const signed long,
            const unsigned short, const unsigned long,
            signed short*, signed long*,
            unsigned short*, unsigned long*
        >
    >;
    ASSERT_TRUE(case5);
}
