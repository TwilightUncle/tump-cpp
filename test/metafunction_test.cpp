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
