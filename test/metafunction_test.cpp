#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <tump/metafunction.hpp>

using F1 = tump::callback<std::is_same, 2>;
using F2 = tump::callback<std::is_same>;
using F3 = tump::bind<F1, int>;
using F4 = tump::bind<F2, int>;
using F5 = tump::bind<F3, int>;

TEST(TumpMetafunctionTest, InvocableTest)
{
    ASSERT_EQ(F3::args_size, 1);
    ASSERT_EQ(F4::args_size, 0);
    ASSERT_EQ(F5::args_size, 0);

    constexpr auto case1 = tump::Invocable<F3>;
    constexpr auto case2 = tump::Invocable<F4>;
    constexpr auto case3 = tump::Invocable<F5>;
    
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);

    constexpr auto case4 = tump::InvocableArgN<F1, 2>;
    constexpr auto case5 = tump::InvocableArgN<F1, 1>;
    constexpr auto case6 = tump::InvocableArgN<F2, 1>;
    constexpr auto case7 = tump::InvocableArgN<F3, 1>;
    constexpr auto case8 = tump::InvocableArgN<F3, 0>;
    constexpr auto case9 = tump::InvocableArgN<F4, 1>;
    constexpr auto case10 = tump::InvocableArgN<F5, 0>;
    constexpr auto case11 = tump::InvocableArgN<F5, 1>;

    ASSERT_TRUE(case4);
    ASSERT_FALSE(case5);
    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
    ASSERT_FALSE(case8);
    ASSERT_TRUE(case9);
    ASSERT_TRUE(case10);
    ASSERT_FALSE(case11);
}

TEST(TumpMetafunctionTest, InvokeTest)
{
    constexpr auto case1 = tump::Functional<std::vector<int>>;
    constexpr auto case2 = tump::TFunctional<std::add_const<int>>;
    constexpr auto case3 = tump::VFunctional<std::add_const<int>>;
    constexpr auto case4 = tump::VFunctional<std::is_integral<int>>;
    
    ASSERT_FALSE(case1);
    ASSERT_TRUE(case2);
    ASSERT_FALSE(case3);
    ASSERT_TRUE(case4);

    constexpr auto case5 = tump::fn::invoke<F1, int, int>::value;
    constexpr auto case6 = tump::invoke_v<F2, int, float>;
    constexpr auto case7 = std::is_same_v<tump::invoke_t<F3, int>, std::true_type>;
    constexpr auto case8 = std::is_same_v<tump::invoke_t<F3, float>, std::false_type>;
    constexpr auto case9 = tump::invoke_v<F5>;
    
    ASSERT_TRUE(case5);
    ASSERT_FALSE(case6);
    ASSERT_TRUE(case7);
    ASSERT_TRUE(case8);
    ASSERT_TRUE(case9);
}

TEST(TumpMetafunctionTest, InvokeListTest)
{
    constexpr auto case1 = tump::invoke_list_v<F1, std::tuple<int, int>>;
    constexpr auto case2 = tump::invoke_list_v<F1, std::tuple<int, float>>;

    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
}

struct A {};
struct B : public A {};

TEST(TumpMetafunctionTest, FlipTest)
{
    using F = tump::callback<std::is_base_of>;

    constexpr auto case1 = tump::invoke_v<F, A, B>;
    constexpr auto case2 = tump::invoke_v<F, B, A>;
    constexpr auto case3 = tump::flip_v<F, A, B>;
    constexpr auto case4 = tump::flip_v<F, B, A>;

    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
    ASSERT_FALSE(case3);
    ASSERT_TRUE(case4);
}

TEST(TumpMetafunctionTest, ComposeTest)
{
    constexpr auto case7 = std::is_same_v<
        tump::invoke_t<
            tump::compose_t<
                tump::cbk<std::add_const, 1>,
                tump::cbk<std::make_unsigned, 1>
            >,
            int
        >,
        const unsigned int
    >;

    ASSERT_TRUE(case7);
}

TEST(TumpMetafunctionTest, ApplyTest)
{
    using type1 = tump::apply_t<
        tump::cbk<std::conjunction>,
        std::true_type,
        std::true_type
    >;

    constexpr auto case1 = tump::VFunctional<type1>;
    constexpr auto case2 = tump::Invocable<type1>;
    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);

    using type2 = tump::apply_t<F1, int>;
    constexpr auto case4 = tump::Invocable<type2>;
    constexpr auto case5 = tump::Functional<type2>;
    ASSERT_TRUE(case4);
    ASSERT_FALSE(case5);

    using type3 = tump::apply_t<F3, int>;
    constexpr auto case6 = tump::VFunctional<type3>;
    constexpr auto case7 = tump::Invocable<type3>;
    ASSERT_TRUE(case6);
    ASSERT_FALSE(case7);
}

TEST(TumpMetafunctionTest, InvokeResultTest)
{
    using type2 = tump::mp_invoke_result_t<tump::cbk<std::is_same, 2>, int, int>;
    constexpr auto case1 = tump::invoke_v<type2, std::true_type>;
    constexpr auto case2 = tump::invoke_v<type2, std::false_type>;
    constexpr auto case3 = tump::invoke_v<type2, int>;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_FALSE(case3);
}

TEST(TumpMetafunctionTest, ExpressionTest)
{
    constexpr auto case1 = tump::exp<tump::is_integral, int>::value;
    constexpr auto case2 = tump::exp<tump::is_same, int, int>::value;

    constexpr auto case3 = std::is_same_v<
        tump::invoke_t<
            tump::apply_t<tump::sec<tump::add_const, tump::_dot>, tump::make_unsigned>,
            int
        >,
        const unsigned int
    >;
    constexpr auto case4 = std::is_same_v<
        tump::invoke_t<tump::exp<tump::add_const, tump::_dot, tump::make_unsigned>, int>,
        const unsigned int
    >;
    constexpr auto case5 = std::is_same_v<
        tump::exp<tump::add_const, tump::_dot, tump::make_unsigned, tump::_doll, int>,
        const unsigned int
    >;
    // constexpr auto case6 = tump::exp<
    //     tump::is_same, const unsigned int,
    //     tump::_doll,
    //     tump::add_const, tump::_dot, tump::make_unsigned,
    //     tump::_doll,
    //     int
    // >::value;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
}
