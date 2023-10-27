#include <gtest/gtest.h>
#include <tump/expression.hpp>

// 全般的な式のテスト


TEST(TumpExpressionTest, ExpressionTest)
{
    constexpr auto case1 = tump::eval<tump::is_integral, int>::value;
    constexpr auto case2 = tump::eval<tump::is_same, int, int>::value;

    constexpr auto case3 = std::is_same_v<
        tump::invoke_t<
            tump::apply_t<tump::sec<tump::add_const, tump::_dot>, tump::make_unsigned>,
            int
        >,
        const unsigned int
    >;
    constexpr auto case4 = std::is_same_v<
        tump::invoke_t<tump::eval<tump::add_const, tump::_dot, tump::make_unsigned>, int>,
        const unsigned int
    >;
    constexpr auto case5 = std::is_same_v<
        tump::eval<tump::add_const, tump::_dot, tump::make_unsigned, tump::_apply, int>,
        const unsigned int
    >;
    constexpr auto case6 = tump::eval<
        tump::is_same, const unsigned int,
        tump::_apply,
        tump::add_const, tump::_dot, tump::make_unsigned,
        tump::_apply,
        int
    >::value;
    constexpr auto case7 = tump::eval<
        tump::is_same, const unsigned int,
        tump::_dot, tump::add_const, tump::_dot, tump::make_unsigned,
        tump::_apply,
        int
    >::value;

    constexpr auto case8 = std::is_same_v<tump::eval<int>, int>;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
    ASSERT_TRUE(case8);
    
    // 下記のような記載は文法エラー
    // tump::eval<tump::is_integral, tump::_apply>;
    // tump::eval<tump::_apply, int>;
    // tump::eval<int, int>;
}

TEST(TumpExpressionTest, MpIfTest)
{
    constexpr auto case1 = std::is_same_v<tump::mp_if_t<std::true_type, int, double>, int>;
    constexpr auto case2 = std::is_same_v<tump::mp_if_t<std::false_type, int, double>, double>;
    constexpr auto case3 = std::is_same_v<tump::mp_if_t<std::true_type, tump::list<int, double>>, int>;
    constexpr auto case4 = std::is_same_v<tump::mp_if_t<std::false_type, tump::list<int, double>>, double>;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);

    constexpr auto case5 = std::is_same_v<tump::mp_if_t<
        tump::exp<int, tump::_eq, int>,
        int,
        double
    >, int>;
    ASSERT_TRUE(case5);
}

TEST(TumpExpressionTest, LambdaTest)
{
    using arg_expect = tump::_farg<'E'>; // expect
    using arg_value = tump::_farg<'V'>; // value

    // 与えた引数と結果の比較テストを行うラムダ式
    using test_lambda = tump::lambda<
        tump::lambda_args<arg_expect, arg_value>,
        tump::exp<
            tump::is_same, arg_expect,
            tump::_dot, tump::add_const, tump::_dot, tump::make_unsigned,
            tump::_apply,
            arg_value
        >
    >;

    // ネストした式の中の引数も置き換わるか確認
    using test_lambda2 = tump::lambda<
        tump::lambda_args<arg_value, tump::_arg2>,
        tump::exp<
            tump::exp<
                tump::exp<arg_value, tump::_eq, tump::_arg2>
            >
        >
    >;

    constexpr auto case1 = tump::eval<test_lambda, const unsigned int, int>::value;
    constexpr auto case2 = tump::eval<test_lambda, const unsigned long long, long long>::value;
    constexpr auto case3 = tump::eval<test_lambda2, int, int>::value;
    constexpr auto case4 = tump::eval<test_lambda2, double, double>::value;
    constexpr auto case5 = tump::eval<test_lambda2, double, long>::value;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_FALSE(case5);
}

template <class T>
using guard_test_func = tump::guard_t<
    tump::if_clause<std::is_unsigned<T>, unsigned int>,
    tump::if_clause<std::is_integral<T>, int>,
    tump::if_clause<std::is_floating_point<T>, float>,
    tump::otherwise<void>
>;

TEST(TumpExpressionTest, GuardTest)
{
    constexpr auto case1 = std::is_same_v<guard_test_func<std::size_t>, unsigned int>;
    constexpr auto case2 = std::is_same_v<guard_test_func<char>, int>;
    constexpr auto case3 = std::is_same_v<guard_test_func<double>, float>;
    constexpr auto case4 = std::is_same_v<guard_test_func<std::tuple<int>>, void>;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);

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

    constexpr auto case5 = tump::eval<test_lambda, int, int>::value;
    constexpr auto case6 = tump::eval<test_lambda, long, double, tump::_eq, int>::value;
    constexpr auto case7 = tump::eval<test_lambda, tump::list<>, double, tump::_eq, void>::value;

    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
}
