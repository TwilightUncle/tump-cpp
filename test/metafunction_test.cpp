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

TEST(TumpMetafunctionTest, ApplyTest)
{
    constexpr auto case1 = tump::Functional<std::vector<int>>;
    constexpr auto case2 = tump::TFunctional<std::add_const<int>>;
    constexpr auto case3 = tump::VFunctional<std::add_const<int>>;
    constexpr auto case4 = tump::VFunctional<std::is_integral<int>>;
    
    ASSERT_FALSE(case1);
    ASSERT_TRUE(case2);
    ASSERT_FALSE(case3);
    ASSERT_TRUE(case4);

    constexpr auto case5 = tump::apply<F1, int, int>::value;
    constexpr auto case6 = tump::apply_v<F2, int, float>;
    constexpr auto case7 = std::is_same_v<tump::apply_t<F3, int>, std::true_type>;
    constexpr auto case8 = std::is_same_v<tump::apply_t<F3, float>, std::false_type>;
    constexpr auto case9 = tump::apply_v<F5>;
    
    ASSERT_TRUE(case5);
    ASSERT_FALSE(case6);
    ASSERT_TRUE(case7);
    ASSERT_TRUE(case8);
    ASSERT_TRUE(case9);
}

TEST(TumpMetafunctionTest, ApplyListTest)
{
    constexpr auto case1 = tump::apply_list_v<F1, std::tuple<int, int>>;
    constexpr auto case2 = tump::apply_list_v<F1, std::tuple<int, float>>;

    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
}

struct A {};
struct B : public A {};

TEST(TumpMetafunctionTest, FlipTest)
{
    using F = tump::callback<std::is_base_of>;

    constexpr auto case1 = tump::apply_v<F, A, B>;
    constexpr auto case2 = tump::apply_v<F, B, A>;
    constexpr auto case3 = tump::flip_v<F, A, B>;
    constexpr auto case4 = tump::flip_v<F, B, A>;

    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
    ASSERT_FALSE(case3);
    ASSERT_TRUE(case4);
}

TEST(TumpMetafunctionTest, RelayTest)
{
    constexpr auto case1 = tump::InvocableList<std::tuple<
        F1,
        F3
    >>;
    constexpr auto case2 = tump::InvocableList<std::tuple<
        F1,
        int
    >>;
    constexpr auto case3 = tump::InvocableList<int>;

    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
    ASSERT_FALSE(case3);

    constexpr auto case4 = tump::InvocableArgNList<std::tuple<
        F1,
        F1,
        F2
    >, 2>;
    constexpr auto case5 = tump::InvocableArgNList<std::tuple<
        F1,
        F3
    >, 2>;
    constexpr auto case6 = tump::InvocableArgNList<std::tuple<
        F3,
        F3,
        F4
    >, 1>;

    ASSERT_TRUE(case4);
    ASSERT_FALSE(case5);
    ASSERT_TRUE(case6);

    constexpr auto case7 = std::is_same_v<
        tump::relay_t<
            decltype([]() -> double { return 1.; }),
            std::tuple<
                tump::cbk<std::invoke_result, 1>,
                tump::cbk<std::add_const, 1>
            >
        >,
        const double
    >;

    ASSERT_TRUE(case7);
}
