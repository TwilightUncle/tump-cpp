#include <gtest/gtest.h>
#include <tuple>
#include <tump/null.hpp>
#include <tump/list.hpp>
#include <tump/algorithm/copy.hpp>
#include <tump/algorithm/map.hpp>
#include <tump/algorithm/fold.hpp>


TEST(TumpAlgorithmTest, HasTypeParametersTest)
{
    constexpr auto case1 = tump::has_type_parameters_v<int>;
    constexpr auto case2 = tump::has_type_parameters_v<tump::empty<std::tuple>>;
    constexpr auto case3 = tump::has_type_parameters_v<std::tuple<int, float, int*>>;
    
    ASSERT_FALSE(case1);
    ASSERT_FALSE(case2);
    ASSERT_TRUE(case3);
}

TEST(TumpAlgorithmTest, MakeTypeListTest)
{
    constexpr auto case1 = std::is_same_v<
        tump::make_type_list_t<tump::empty<std::tuple>, int, float, int*>,
        std::tuple<int, float, int*>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::make_type_list_t<std::tuple<double, long, short, char>, int, float, int*>,
        std::tuple<int, float, int*>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, MapTest)
{
    using type_list = std::tuple<int, float, short>;
    constexpr auto case1 = std::is_same_v<
        tump::map_t<
            tump::callback<std::add_const, 1>,
            std::tuple<int, float, short>
        >,
        std::tuple<const int, const float, const short>
    >;
    // 空のリストに対する動作の確認
    constexpr auto case2 = std::is_same_v<
        tump::map_t<
            tump::callback<std::add_const, 1>,
            tump::empty<std::tuple>
        >,
        tump::empty<std::tuple>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, CopyTest)
{
    constexpr auto case1 = std::is_same_v<
        tump::copy_t<tump::list<int, float, int*>, tump::empty<std::tuple>>,
        std::tuple<int, float, int*>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::copy_t<tump::list<int, float, int*>, std::tuple<double, long, short, char>>,
        std::tuple<int, float, int*>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

struct A {};
struct B : public A  {};

template <class L, class R>
struct get_derived : std::conditional<std::is_base_of_v<L, R>, R, tump::mp_null_t> {};

TEST(TumpAlgorithmTest, FoldTest)
{
    using type1 = tump::foldl_t<
        tump::callback<std::conjunction>,
        std::true_type,
        tump::list<
            std::false_type,
            std::true_type,
            std::false_type
        >
    >;
    using type2 = tump::foldl_t<
        tump::callback<std::conjunction>,
        std::true_type,
        tump::list<
            std::true_type,
            std::true_type,
            std::true_type
        >
    >;

    ASSERT_FALSE(type1::value);
    ASSERT_TRUE(type2::value);

    // foldlとfoldrの畳み込み順序の違いの確認
    using type3 = tump::foldl_t<
        tump::callback<get_derived>,
        A, tump::list<A, B>
    >;
    using type4 = tump::foldr_t<
        tump::callback<get_derived>,
        A, tump::list<A, B>
    >;

    constexpr auto case1 = std::is_same_v<type3, B>;
    constexpr auto case2 = std::is_same_v<type4, tump::mp_null_t>;
    
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, ConcatTest)
{
}

TEST(TumpAlgorithmTest, PushTest)
{
}
