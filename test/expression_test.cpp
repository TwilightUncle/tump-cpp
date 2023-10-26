#include <gtest/gtest.h>
#include <tump.hpp>

// 全般的な式のテスト

// TEST(TumpExpressionTest, EvalTest)
// {

// }

TEST(TumpExpressionTest, LambdaGuardTest)
{
    using test_lambda = tump::lambda<
        tump::lambda_args<tump::_arg1, tump::_arg2>,
        tump::exp<
            tump::guard<3>,
            tump::if_clause<
                std::is_same<tump::_arg1, tump::_arg2>,
                tump::exp<tump::_arg1, tump::_eq, tump::_arg2>
            >,
            tump::if_clause<
                tump::exp<tump::is_not_same, tump::_arg1, tump::_arg2, tump::_and, tump::is_integral, tump::_arg1>,
                int
            >,
            tump::otherwise<void>
        >
    >;

    constexpr auto case1 = tump::eval<test_lambda, int, int>::value;
    constexpr auto case2 = tump::eval<test_lambda, long, double, tump::_eq, int>::value;
    constexpr auto case3 = tump::eval<test_lambda, tump::list<>, double, tump::_eq, void>::value;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
}
