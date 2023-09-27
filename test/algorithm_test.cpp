#include <gtest/gtest.h>
#include <tuple>
#include <tump/containers/array.hpp>
#include <tump/algorithm.hpp>

TEST(TumpAlgorithmTest, HasTypeParametersTest)
{
    constexpr auto case1 = tump::has_type_parameters_v<int>;
    constexpr auto case2 = tump::has_type_parameters_v<tump::empty<std::tuple>>;
    constexpr auto case3 = tump::has_type_parameters_v<std::tuple<int, float, int*>>;
    constexpr auto case4 = tump::has_type_parameters_v<tump::list<int, float, int*>>;
    constexpr auto case5 = tump::has_type_parameters_v<tump::st_list<tump::cbk<std::is_integral>, int, long, short>>;
    constexpr auto case6 = tump::has_type_parameters_v<tump::array<tump::cbk<std::is_integral>, 3, int, long, short>>;
    
    ASSERT_FALSE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
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
    constexpr auto case3 = std::is_same_v<
        tump::make_type_list_t<tump::list<double, long, short, char>, int, float, int*>,
        tump::list<int, float, int*>
    >;
    constexpr auto case4 = std::is_same_v<
        tump::make_type_list_t<tump::st_list<tump::cbk<std::is_floating_point>, double>, long double, float, double>,
        tump::st_list<tump::cbk<std::is_floating_point>, long double, float, double>
    >;
    constexpr auto case5 = std::is_same_v<
        tump::make_type_list_t<tump::array<tump::cbk<std::is_integral>, 4>, int, short, char, long>,
        tump::array<tump::cbk<std::is_integral>, 4, int, short, char, long>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);

    using constraint1 = tump::invoke_result_t<
        tump::cbk<tump::make_type_list>,
        tump::st_list<tump::cbk<std::is_integral>>
    >;

    constexpr auto case6 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_integral>>>;
    constexpr auto case7 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_integral>, int, short, long>>;
    constexpr auto case8 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_floating_point>, float>>;

    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
    ASSERT_FALSE(case8);
}

TEST(TumpAlgorithmTest, MapTest)
{
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
    // invoke_result を定義済みのメタ関数を実行した際の確認
    constexpr auto case3 = std::is_same_v<
        tump::map_t<
            tump::callback<std::is_integral, 1>,
            tump::st_list<tump::cbk<tump::to_true, 1>, int, float, short>
        >,
        tump::st_list<typename tump::constraint_bool_constant::type, std::true_type, std::false_type, std::true_type>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);

    using constraint1 = tump::invoke_result_t<
        tump::cbk<tump::map, 2>,
        tump::cbk<std::is_integral, 1>,
        tump::st_list<tump::cbk<std::is_integral>>
    >;
    using constraint2 = tump::invoke_result_t<
        tump::cbk<tump::map, 2>,
        tump::cbk<std::is_integral, 1>,
        tump::st_list<tump::cbk<std::is_integral>, int>
    >;

    constexpr auto case4 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_integral>>>;
    constexpr auto case5 = tump::invoke_v<constraint2, tump::st_list<typename tump::constraint_bool_constant::type>>;
    constexpr auto case6 = tump::invoke_v<constraint2, tump::st_list<typename tump::constraint_bool_constant::type, std::true_type, std::false_type>>;
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
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
    constexpr auto case3 = std::is_same_v<
        tump::copy_t<std::tuple<double, long, short, char>, tump::st_list<tump::cbk<tump::to_true, 1>, int, float, short>>,
        tump::st_list<tump::cbk<tump::to_true, 1>, double, long, short, char>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);

    using constraint1 = tump::invoke_result_t<
        tump::cbk<tump::copy, 2>,
        tump::list<int, long, short>,
        tump::st_list<tump::cbk<std::is_integral>>
    >;
    constexpr auto case4 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_integral>>>;
    constexpr auto case5 = tump::invoke_v<constraint1, tump::st_list<tump::cbk<std::is_floating_point>>>;
    ASSERT_TRUE(case4);
    ASSERT_FALSE(case5);
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
    using type3 = tump::foldl_t<
        tump::callback<std::conjunction>,
        std::true_type,
        tump::st_list<
            tump::cbk<tump::is_bool_constant, 1>,
            std::true_type,
            std::true_type,
            std::true_type
        >
    >;

    ASSERT_FALSE(type1::value);
    ASSERT_TRUE(type2::value);
    ASSERT_TRUE(type3::value);

    // foldlとfoldrの畳み込み順序の違いの確認
    using type4 = tump::foldl_t<
        tump::callback<get_derived>,
        A, tump::list<A, B>
    >;
    using type5 = tump::foldr_t<
        tump::callback<get_derived>,
        A, tump::list<A, B>
    >;

    constexpr auto case1 = std::is_same_v<type4, B>;
    constexpr auto case2 = std::is_same_v<type5, tump::mp_null_t>;
    
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, ConcatTest)
{
    using type_list1 = tump::list<int, short, long long>;
    using type_list2 = tump::list<float, double, char>;
    using empty_list = tump::list<>;

    // 2つのリストの結合
    constexpr auto case1 = std::is_same_v<
        tump::concat_t<type_list1, type_list2>,
        tump::list<int, short, long long, float, double, char>
    >;
    ASSERT_TRUE(case1);

    // 3つ以上のリストの結合
    constexpr auto case2 = std::is_same_v<
        tump::concat_t<type_list1, type_list2, type_list1, type_list2>,
        tump::list<int, short, long long, float, double, char, int, short, long long, float, double, char>
    >;
    ASSERT_TRUE(case2);

    // 空リストとリストの結合(空リストは無視されること)
    constexpr auto case3 = std::is_same_v<
        tump::concat_t<type_list1, empty_list>,
        type_list1
    >;
    ASSERT_TRUE(case3);
    constexpr auto case4 = std::is_same_v<
        tump::concat_t<empty_list, type_list2>,
        type_list2
    >;
    ASSERT_TRUE(case4);
    constexpr auto case5 = std::is_same_v<
        tump::concat_t<type_list1, empty_list, type_list2>,
        tump::list<int, short, long long, float, double, char>
    >;
    ASSERT_TRUE(case5);

    // 一つのリストだけ渡された場合
    constexpr auto case6 = std::is_same_v<
        tump::concat_t<type_list1>,
        type_list1
    >;
    ASSERT_TRUE(case6);
    constexpr auto case7 = std::is_same_v<
        tump::concat_t<empty_list>,
        empty_list
    >;
    ASSERT_TRUE(case7);

    constexpr auto case8 = std::is_same_v<
        tump::concat_t<
            tump::st_list<tump::cbk<std::is_integral, 1>, int, char>,
            tump::st_list<tump::cbk<std::is_integral, 1>, long, unsigned short>,
            tump::st_list<tump::cbk<std::is_integral, 1>, long long, unsigned char>
        >,
        tump::st_list<tump::cbk<std::is_integral, 1>, int, char, long, unsigned short, long long, unsigned char>
    >;
    ASSERT_TRUE(case8);
}

TEST(TumpAlgorithmTest, PushTest)
{
    using type_list1 = tump::list<int, short, long long>;
    using empty_list = tump::list<>;

    constexpr auto case1 = std::is_same_v<
        tump::push_back_t<type_list1, float>,
        tump::list<int, short, long long, float>
    >;
    ASSERT_TRUE(case1);
    constexpr auto case2 = std::is_same_v<
        tump::push_back_t<type_list1, float, double>,
        tump::list<int, short, long long, float, double>
    >;
    ASSERT_TRUE(case2);
    constexpr auto case3 = std::is_same_v<
        tump::push_back_t<empty_list, int>,
        tump::list<int>
    >;
    ASSERT_TRUE(case3);

    constexpr auto case4 = std::is_same_v<
        tump::push_front_t<type_list1, float>,
        tump::list<float, int, short, long long>
    >;    
    ASSERT_TRUE(case4);
    constexpr auto case5 = std::is_same_v<
        tump::push_front_t<type_list1, float, double>,
        tump::list<float, double, int, short, long long>
    >;
    ASSERT_TRUE(case5);
    constexpr auto case6 = std::is_same_v<
        tump::push_front_t<empty_list, int>,
        tump::list<int>
    >;
    ASSERT_TRUE(case6);
}

TEST(TumpAlgorithmTest, LenTest)
{
    constexpr auto case1 = tump::len_v<tump::list<int, short, long long>>;
    constexpr auto case2 = tump::len_v<tump::list<>>;
    constexpr auto case3 = tump::len_v<tump::st_list<tump::cbk<std::is_integral, 1>, int, short>>;
    constexpr auto case4 = tump::len_v<tump::st_list<tump::cbk<std::is_integral, 1>>>;
    ASSERT_EQ(case1, 3);
    ASSERT_EQ(case2, 0);
    ASSERT_EQ(case3, 2);
    ASSERT_EQ(case4, 0);
}

TEST(TumpAlgorithmTest, GetTest)
{
    using type_list1 = tump::list<int, short, char, long long>;

    constexpr auto case1 = std::is_same_v<tump::get_front_t<type_list1>, int>;
    constexpr auto case2 = std::is_same_v<tump::get_t<0, type_list1>, int>;
    constexpr auto case3 = std::is_same_v<tump::get_t<1, type_list1>, short>;
    constexpr auto case4 = std::is_same_v<tump::get_t<2, type_list1>, char>;
    constexpr auto case5 = std::is_same_v<tump::get_t<3, type_list1>, long long>;
    constexpr auto case6 = std::is_same_v<tump::get_back_t<type_list1>, long long>;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
}

TEST(TumpAlgorithmTest, PopTest)
{
    using type_list1 = tump::list<int, short, char, long long>;
    using type_list2 = tump::list<int>;

    constexpr auto case1 = std::is_same_v<
        tump::pop_front_t<type_list1>,
        tump::list<short, char, long long>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::pop_back_t<type_list1>,
        tump::list<int, short, char>
    >;
    constexpr auto case3 = std::is_same_v<tump::pop_front_t<type_list2>, tump::list<>>;
    constexpr auto case4 = std::is_same_v<tump::pop_back_t<type_list2>, tump::list<>>;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
}

TEST(TumpAlgorithmTest, SliceTest)
{
    using type_list1 = tump::list<int, short, char, long long, float, double>;
    using type_list2 = tump::st_list<tump::cbk<std::is_arithmetic>, int, short, char, long long, float, double>;

    constexpr auto case1 = std::is_same_v<
        tump::slice_t<type_list1, 4>,
        tump::list<float, double>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::slice_t<type_list1, 5>,
        tump::list<double>
    >;
    constexpr auto case3 = std::is_same_v<
        tump::slice_t<type_list1, 6>,
        tump::list<>
    >;
    constexpr auto case4 = std::is_same_v<
        tump::slice_t<type_list1, 0, 4>,
        tump::list<int, short, char, long long>
    >;
    constexpr auto case5 = std::is_same_v<
        tump::slice_t<type_list2, 2, 3>,
        tump::st_list<tump::cbk<std::is_arithmetic>, char, long long, float>
    >;
    constexpr auto case6 = std::is_same_v<
        tump::slice_t<type_list2, 2, 0>,
        tump::st_list<tump::cbk<std::is_arithmetic>>
    >;
    constexpr auto case7 = std::is_same_v<
        tump::slice_t<type_list2, 1, 3, 1>,
        tump::st_list<tump::cbk<std::is_arithmetic>, short, long long, double>
    >;
    constexpr auto case8 = std::is_same_v<
        tump::slice_t<type_list2, 1, 3, 2>,
        tump::st_list<tump::cbk<std::is_arithmetic>, short, float>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
    ASSERT_TRUE(case8);
}

TEST(TumpAlgorithmTest, ReverseTest)
{
    using type_list1 = tump::list<int, short, char, long long, float, double>;
    using type_list2 = tump::st_list<tump::cbk<std::is_arithmetic>, int, short, char, long long, float, double>;
    using type_list3 = tump::array<tump::cbk<std::is_arithmetic>, 6, int, short, char, long long, float, double>;

    constexpr auto case1 = std::is_same_v<
        tump::reverse_t<type_list1>,
        tump::list<double, float, long long, char, short, int>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::reverse_t<type_list2>,
        tump::st_list<tump::cbk<std::is_arithmetic>, double, float, long long, char, short, int>
    >;
    constexpr auto case3 = std::is_same_v<
        tump::reverse_t<type_list3>,
        tump::array<tump::cbk<std::is_arithmetic>, 6, double, float, long long, char, short, int>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
}

TEST(TumpAlgorithmTest, ExistsTest)
{
    constexpr auto case1 = tump::exists_v<int, tump::list<float, int, double>>;
    constexpr auto case2 = tump::exists_v<int, tump::list<>>;
    constexpr auto case3 = tump::exists_v<int, tump::array<tump::cbk<std::is_arithmetic, 1>, 3, float, int, double>>;
    constexpr auto case4 = tump::exists_v<tump::cbk<std::is_arithmetic, 1>, tump::array<tump::cbk<std::is_arithmetic, 1>, 3, float, int, double>>;
    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
    ASSERT_TRUE(case3);
    ASSERT_FALSE(case4);
}

TEST(TumpAlgorithmTest, MpIfTest)
{
    constexpr auto case1 = std::is_same_v<tump::mp_if_t<std::true_type, int, double>, int>;
    constexpr auto case2 = std::is_same_v<tump::mp_if_t<std::false_type, int, double>, double>;
    constexpr auto case3 = std::is_same_v<tump::mp_if_t<std::true_type, tump::list<int, double>>, int>;
    constexpr auto case4 = std::is_same_v<tump::mp_if_t<std::false_type, tump::array<tump::cbk<std::is_arithmetic, 1>, 2, int, double>>, double>;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);

    using constraint1 = tump::invoke_result_t<
        tump::cbk<tump::mp_if, 3>,
        std::true_type,
        int,
        double
    >;
    using constraint2 = tump::invoke_result_t<
        tump::cbk<tump::mp_if, 3>,
        std::true_type,
        tump::array<tump::cbk<std::is_arithmetic, 1>, 2, int, double>
    >;

    constexpr auto case5 = tump::invoke_v<constraint1, int>;
    constexpr auto case6 = tump::invoke_v<constraint1, double>;
    constexpr auto case7 = tump::invoke_v<constraint1, char>;
    constexpr auto case8 = tump::invoke_v<constraint2, int>;
    constexpr auto case9 = tump::invoke_v<constraint2, double>;
    constexpr auto case10 = tump::invoke_v<constraint2, char>;
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
    ASSERT_FALSE(case7);
    ASSERT_TRUE(case8);
    ASSERT_TRUE(case9);
    ASSERT_FALSE(case10);
}
