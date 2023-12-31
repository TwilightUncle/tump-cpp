#include <gtest/gtest.h>
#include <tump/containers.hpp>
#include <tump/expression/lambda.hpp>

TEST(TumpContainersTest, BtreeTest)
{
    using list1 = tump::list<std::int32_t, std::uint64_t, std::int8_t, std::uint16_t>;
    using tree1 = tump::to_bintree_t<list1>;

    constexpr auto case1 = std::is_same_v<
        tree1,
        tump::bintree<tump::bnode<std::int32_t, std::uint64_t, tump::bnode<std::int8_t, std::uint16_t, tump::mp_null_t>>>
    >;
    constexpr auto case2 = std::is_same_v<tump::to_bintree_t<tree1>, tree1>;
    constexpr auto case3 = std::is_same_v<
        tump::flatten_t<tree1>,
        tump::list<std::int8_t, std::uint16_t, std::int32_t, std::uint64_t>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);

    constexpr auto case4 = tump::is_bintree_v<int>;
    constexpr auto case5 = tump::is_bintree_v<tree1>;
    constexpr auto case6 = tump::BynaryTree<list1>;
    constexpr auto case7 = tump::BynaryTree<tree1>;

    ASSERT_FALSE(case4);
    ASSERT_TRUE(case5);
    ASSERT_FALSE(case6);
    ASSERT_TRUE(case7);

    using tree2 = tump::push_t<tump::empty_bintree<>, std::int32_t>;
    using tree3 = tump::push_t<tree2, std::uint64_t, std::int8_t, std::uint16_t>;

    constexpr auto case8 = std::is_same_v<
        tump::flatten_t<tree2>,
        tump::list<std::int32_t>
    >;
    constexpr auto case9 = std::is_same_v<
        tump::flatten_t<tree3>,
        tump::list<std::int8_t, std::uint16_t, std::int32_t, std::uint64_t>
    >;

    ASSERT_TRUE(case8);
    ASSERT_TRUE(case9);
}

TEST(TumpContainersTest, FunctorTest)
{
    // function
    using functor1 = tump::add_const;
    constexpr auto case1 = std::is_same_v<
        tump::eval<tump::fmap, tump::type_identity, functor1, tump::_apply, int>,
        tump::eval<tump::type_identity, functor1, tump::_apply, int>
    >;
    ASSERT_TRUE(case1);

    // list
    using functor2 = tump::list<int, short, long>;
    constexpr auto case2 = std::is_same_v<
        tump::eval<tump::fmap, tump::type_identity, functor2>,
        tump::eval<tump::type_identity, functor2>
    >;
    ASSERT_TRUE(case2);

    // function
    using functor3 = tump::type_identity;
    constexpr auto case3 = std::is_same_v<
        tump::eval<tump::eval<
            tump::fmap, tump::_apply,
            tump::add_const, tump::_dot, tump::make_unsigned
        >, functor3, tump::_apply, int>,
        tump::eval<tump::eval<
            tump::fmap, tump::add_const, tump::_dot,
            tump::fmap, tump::make_unsigned
        >, functor3, tump::_apply, int>
    >;
    ASSERT_TRUE(case3);

    // list
    constexpr auto case4 = std::is_same_v<
        tump::eval<tump::eval<
            tump::fmap, tump::_apply,
            tump::add_const, tump::_dot, tump::make_unsigned
        >, functor2>,
        tump::eval<tump::eval<
            tump::fmap, tump::add_const, tump::_dot,
            tump::fmap, tump::make_unsigned
        >, functor2>
    >;
    ASSERT_TRUE(case4);
}

TEST(TumpContainersTest, ApplicativeTest)
{
    // common
    // pure f <*> pure x = pure (f x)
    constexpr auto case1 = std::is_same_v<
        tump::eval<tump::pure, tump::make_unsigned, tump::_ap, tump::pure, char>,
        tump::pure_t<unsigned char>
    >;
    ASSERT_TRUE(case1);

    // list
    using applicative1 = tump::list<unsigned short, long>;
    using applicative2 = tump::list<tump::add_const, tump::add_pointer>;
    using applicative3 = tump::list<tump::make_signed, tump::make_unsigned>;

    // pure id <*> v = v
    constexpr auto case2 = std::is_same_v<
        tump::eval<tump::pure, tump::type_identity, tump::_ap, applicative1>,
        applicative1
    >;
    ASSERT_TRUE(case2);

    // pure (.) <*> u <*> v <*> w = u <*> (v <*> w)
    constexpr auto case3 = std::is_same_v<
        tump::eval<tump::pure, tump::compose<>, tump::_ap, applicative2, tump::_ap, applicative3, tump::_ap, applicative1>,
        tump::eval<applicative2, tump::_ap, tump::eval<applicative3, tump::_ap, applicative1>>
    >;
    ASSERT_TRUE(case3);

    // u <*> pure y = pure ($ y) <*> u
    constexpr auto case4 = std::is_same_v<
        tump::eval<applicative2, tump::_ap, tump::pure, char>,
        tump::eval<tump::pure, tump::sec<tump::_apply, char>, tump::_ap, applicative2>
    >;
    ASSERT_TRUE(case4);

    constexpr auto case5 = std::is_same_v<
        tump::eval<tump::compose<>, tump::_fmap, applicative2, tump::_ap, applicative3, tump::_ap, applicative1>,
        tump::list<
            const signed short, const signed long,
            const unsigned short, const unsigned long,
            signed short*, signed long*,
            unsigned short*, unsigned long*
        >
    >;
    ASSERT_TRUE(case5);
}

TEST(TumpContainersTest, MonadTest)
{
    // list

    using monad1 = tump::list<unsigned short, long>;
    using func1 = tump::eval<tump::cbk<tump::fn::make_type_list, 2>, tump::list<>, tump::_dot, tump::make_unsigned>;
    using func2 = tump::eval<tump::cbk<tump::fn::make_type_list, 2>, tump::list<>, tump::_dot, tump::add_const>;

    // return a >>= k = k a
    constexpr auto case1 = std::is_same_v<
        tump::eval<tump::ret, short, tump::_bind, func1>,
        tump::eval<func1, short>
    >;
    ASSERT_TRUE(case1);

    // m >>= return = m
    constexpr auto case2 = std::is_same_v<
        tump::eval<monad1, tump::_bind, tump::ret>,
        monad1
    >;
    ASSERT_TRUE(case2);

    // m >>= (\x -> k x >>= h) = (m >>= k) >>= h
    constexpr auto case3 = std::is_same_v<
        tump::eval<
            monad1, tump::_bind,
            tump::lambda<
                tump::lambda_args<tump::_argx>,
                tump::exp<func1, tump::_argx, tump::_bind, func2>
            >
        >,
        tump::eval<
            tump::exp<monad1, tump::_bind, func1>,
            tump::_bind, func2
        >
    >;
    ASSERT_TRUE(case3);
}
