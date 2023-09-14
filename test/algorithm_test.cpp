#include <gtest/gtest.h>
#include <tuple>
#include <tump/algorithm/has_type_parameters.hpp>


TEST(TumpAlgorithmTest, HasTypeParametersTest)
{
    constexpr auto case1 = tump::has_type_parameters_v<int>;
    constexpr auto case2 = tump::has_type_parameters_v<tump::empty<std::tuple>>;
    constexpr auto case3 = tump::has_type_parameters_v<std::tuple<int, float, int*>>;
    
    ASSERT_FALSE(case1);
    ASSERT_FALSE(case2);
    ASSERT_TRUE(case3);
}
