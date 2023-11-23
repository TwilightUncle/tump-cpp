#include <gtest/gtest.h>
#include <tuple>
#include <tump/algorithm.hpp>

TEST(TumpAlgorithmTest, HasTypeParametersTest)
{
    constexpr auto case1 = tump::has_type_parameters_v<int>;
    constexpr auto case2 = tump::has_type_parameters_v<tump::empty<std::tuple>>;
    constexpr auto case3 = tump::has_type_parameters_v<std::tuple<int, float, int*>>;
    constexpr auto case4 = tump::has_type_parameters_v<tump::list<int, float, int*>>;
    constexpr auto case5 = tump::has_type_parameters_v<tump::list<int, long, short>>;
    constexpr auto case6 = tump::has_type_parameters_v<tump::list<int, long, short>>;
    
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
        tump::make_type_list_t<tump::list<double>, long double, float, double>,
        tump::list<long double, float, double>
    >;
    constexpr auto case5 = std::is_same_v<
        tump::make_type_list_t<tump::list<>, int, short, char, long>,
        tump::list<int, short, char, long>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
}

TEST(TumpAlgorithmTest, MapTest)
{
    constexpr auto case1 = std::is_same_v<
        tump::map_t<
            tump::add_const,
            std::tuple<int, float, short>
        >,
        std::tuple<const int, const float, const short>
    >;
    // 空のリストに対する動作の確認
    constexpr auto case2 = std::is_same_v<
        tump::map_t<
            tump::add_const,
            tump::empty<std::tuple>
        >,
        tump::empty<std::tuple>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);

    constexpr auto case3 = std::is_same_v<
        tump::map_if_t<
            tump::is_integral,
            tump::add_const,
            tump::list<int, float, int*, double, char, long, void>
        >,
        tump::list<const int, float, int*, double, const char, const long, void>
    >;

    ASSERT_TRUE(case3);
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
        tump::copy_t<std::tuple<double, long, short, char>, tump::list<int, float, short>>,
        tump::list<double, long, short, char>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
}

struct A {};
struct B : public A  {};

template <class L, class R>
struct get_derived : std::conditional<std::is_base_of_v<L, R>, R, tump::mp_null_t> {};

TEST(TumpAlgorithmTest, FoldTest)
{
    using type1 = tump::foldl_t<
        tump::conjunction<>,
        std::true_type,
        tump::list<
            std::false_type,
            std::true_type,
            std::false_type
        >
    >;
    using type2 = tump::foldl_t<
        tump::conjunction<>,
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
            tump::list<int, char>,
            tump::list<long, unsigned short>,
            tump::list<long long, unsigned char>
        >,
        tump::list<int, char, long, unsigned short, long long, unsigned char>
    >;
    ASSERT_TRUE(case8);

    constexpr auto case9 = std::is_same_v<
        tump::concat_t<
            tump::vlist<1, 2u, 3l>,
            tump::vlist<4ul, 5ll>,
            tump::vlist<nullptr>,
            tump::vlist<>
        >,
        tump::vlist<1, 2u, 3l, 4ul, 5ll, nullptr>
    >;
    ASSERT_TRUE(case9);
}

TEST(TumpAlgorithmTest, PushTest)
{
    using type_list1 = tump::list<int, short, long long>;
    using type_list2 = tump::list<int, short, long long>;
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
    constexpr auto case7 = std::is_same_v<
        tump::push_back_if_t<tump::is_integral, empty_list, double, float>,
        empty_list
    >;
    ASSERT_TRUE(case7);
    constexpr auto case8 = std::is_same_v<
        tump::push_back_if_t<tump::is_integral, type_list2, unsigned long, double, char, float>,
        tump::list<int, short, long long, unsigned long, char>
    >;
    ASSERT_TRUE(case8);
    constexpr auto case9 = std::is_same_v<
        tump::push_front_if_t<tump::is_integral, empty_list, double, float>,
        empty_list
    >;
    ASSERT_TRUE(case9);
    constexpr auto case10 = std::is_same_v<
        tump::push_front_if_t<tump::is_integral, type_list2, unsigned long, double, char, float>,
        tump::list<unsigned long, char, int, short, long long>
    >;
    ASSERT_TRUE(case10);
}

TEST(TumpAlgorithmTest, LenTest)
{
    constexpr auto case1 = tump::len_v<tump::list<int, short, long long>>;
    constexpr auto case2 = tump::len_v<tump::list<>>;
    ASSERT_EQ(case1, 3);
    ASSERT_EQ(case2, 0);

    constexpr auto case3 = tump::len_v<tump::vlist<int(1), short(2), char(2), long(4)>>;
    constexpr auto case4 = tump::len_v<tump::vlist<>>;
    ASSERT_EQ(case3, 4);
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

    using value_lsit = tump::vlist<int(1), short(2), char(3), long(4)>;

    constexpr auto case7 = tump::get_front_v<value_lsit>;
    constexpr auto case8 = tump::get_v<0, value_lsit>;
    constexpr auto case9 = tump::get_v<2, value_lsit>;
    constexpr auto case10 = tump::get_v<3, value_lsit>;
    constexpr auto case11 = tump::get_back_v<value_lsit>;
    ASSERT_EQ(case7, int(1));
    ASSERT_EQ(case8, int(1));
    ASSERT_EQ(case9, char(3));
    ASSERT_EQ(case10, long(4));
    ASSERT_EQ(case11, long(4));
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

    using value_list1 = tump::vlist<int(1), short(2), long(3)>;
    using value_list2 = tump::vlist<int(1)>;
    constexpr auto case5 = std::is_same_v<tump::pop_front_t<value_list1>, tump::vlist<short(2), long(3)>>;
    constexpr auto case6 = std::is_same_v<tump::pop_front_t<value_list2>, tump::vlist<>>;
    constexpr auto case7 = std::is_same_v<tump::pop_back_t<value_list1>, tump::vlist<int(1), short(2)>>;
    constexpr auto case8 = std::is_same_v<tump::pop_back_t<value_list2>, tump::vlist<>>;
}

TEST(TumpAlgorithmTest, SliceTest)
{
    using type_list1 = tump::list<int, short, char, long long, float, double>;
    using type_list2 = tump::list<int, short, char, long long, float, double>;

    constexpr auto case1 = std::is_same_v<
        tump::slice_t<type_list1, tump::size_args<4>>,
        tump::list<float, double>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::slice_t<type_list1, tump::size_args<5>>,
        tump::list<double>
    >;
    constexpr auto case3 = std::is_same_v<
        tump::slice_t<type_list1, tump::size_args<6>>,
        tump::list<>
    >;
    constexpr auto case4 = std::is_same_v<
        tump::slice_t<type_list1, tump::size_args<0, 4>>,
        tump::list<int, short, char, long long>
    >;
    constexpr auto case5 = std::is_same_v<
        tump::slice_t<type_list2, tump::size_args<2, 3>>,
        tump::list<char, long long, float>
    >;
    constexpr auto case6 = std::is_same_v<
        tump::slice_t<type_list2, tump::size_args<2, 0>>,
        tump::list<>
    >;
    constexpr auto case7 = std::is_same_v<
        tump::slice_t<type_list2, tump::size_args<1, 3, 1>>,
        tump::list<short, long long, double>
    >;
    constexpr auto case8 = std::is_same_v<
        tump::slice_t<type_list2, tump::size_args<1, 3, 2>>,
        tump::list<short, float>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
    ASSERT_TRUE(case5);
    ASSERT_TRUE(case6);
    ASSERT_TRUE(case7);
    ASSERT_TRUE(case8);

    constexpr auto case9 = std::is_same_v<
        tump::slice_t<
            tump::vlist<int(1), short(2), long(3), std::size_t(4), char(5), 6u>,
            tump::size_args<1,3,2>
        >,
        tump::vlist<short(2), char(5)>
    >;
    ASSERT_TRUE(case9);
}

TEST(TumpAlgorithmTest, ReverseTest)
{
    using type_list1 = tump::list<int, short, char, long long, float, double>;
    using type_list2 = std::tuple<int, short, char, long long, float, double>;

    constexpr auto case1 = std::is_same_v<
        tump::reverse_t<type_list1>,
        tump::list<double, float, long long, char, short, int>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::reverse_t<type_list2>,
        std::tuple<double, float, long long, char, short, int>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);

    constexpr auto case3 = std::is_same_v<
        tump::reverse_t<tump::vlist<int(1), short(2), long(3)>>,
        tump::vlist<long(3), short(2), int(1)>
    >;
    ASSERT_TRUE(case3);
}

TEST(TumpAlgorithmTest, ExistsTest)
{
    constexpr auto case1 = tump::exists_v<int, tump::list<float, int, double>>;
    constexpr auto case2 = tump::exists_v<int, tump::list<>>;
    ASSERT_TRUE(case1);
    ASSERT_FALSE(case2);
}

TEST(TumpAlgorithmTest, FilterTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long>;

    constexpr auto case1 = std::is_same_v<
        tump::filter_t<tump::is_integral, list1>,
        tump::list<int, char, unsigned long>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::filter_t<tump::is_floating_point, list1>,
        tump::list<float, double>
    >;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, RemoveIfTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long>;

    constexpr auto case1 = std::is_same_v<
        tump::remove_if_t<tump::is_integral, list1>,
        tump::list<float, double>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::remove_if_t<tump::is_floating_point, list1>,
        tump::list<int, char, unsigned long>
    >;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);

    constexpr auto case3 = std::is_same_v<
        tump::remove_t<int, tump::list<int, float, int, double, int, short>>,
        tump::list<float, double, short>
    >;
    ASSERT_TRUE(case3);
}

TEST(TumpAlgorithmTest, UniqueTest)
{
    using list1 = tump::list<int, float, int, char, float, int>;
    using list2 = tump::list<int, float, char>;

    constexpr auto case1 = std::is_same_v<
        tump::unique_t<list1>,
        tump::list<int, float, char>
    >;
    ASSERT_TRUE(case1);

    constexpr auto case2 = tump::is_unique_v<list1>;
    constexpr auto case3 = tump::is_unique_v<list2>;
    ASSERT_FALSE(case2);
    ASSERT_TRUE(case3);

    constexpr auto case4 = std::is_same_v<
        tump::unique_t<tump::vlist<int(1), short(2), long(3), int(1), int(2), long(3), long(4)>>,
        tump::vlist<int(1), short(2), long(3), int(2), long(4)>
    >;
    ASSERT_TRUE(case4);

    constexpr auto case5 = tump::is_unique_v<tump::vlist<int(1), short(2), long(3), int(1), int(2), long(3), long(4)>>;
    constexpr auto case6 = tump::is_unique_v<tump::vlist<int(1), short(2), long(3), int(2), long(4)>>;
    ASSERT_FALSE(case5);
    ASSERT_TRUE(case6);

}

TEST(TumpAlgorithmTest, FindIfTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long>;
    
    constexpr auto case1 = std::is_same_v<tump::find_if_t<tump::is_floating_point, list1>, float>;
    constexpr auto case2 = tump::find_if_v<tump::is_floating_point, list1>;
    constexpr auto case3 = std::is_same_v<tump::find_if_t<tump::is_pointer, list1>, tump::mp_null_t>;
    constexpr auto case4 = tump::find_if_v<tump::is_pointer, list1>;
    constexpr auto case5 = std::is_same_v<tump::find_t<double, list1>, double>;
    constexpr auto case6 = tump::find_v<double, list1>;
    constexpr auto case7 = std::is_same_v<tump::find_t<long long, list1>, tump::mp_null_t>;
    constexpr auto case8 = tump::find_v<long long, list1>;
    ASSERT_TRUE(case1);
    ASSERT_EQ(case2, 1);
    ASSERT_TRUE(case3);
    ASSERT_EQ(case4, -1);
    ASSERT_TRUE(case5);
    ASSERT_EQ(case6, 2);
    ASSERT_TRUE(case7);
    ASSERT_EQ(case8, -1);

    constexpr auto case9 = tump::index_of_if_v<tump::is_floating_point, list1>;
    constexpr auto case10 = tump::index_of_if_v<tump::is_pointer, list1>;
    constexpr auto case11 = tump::index_of_v<double, list1>;
    constexpr auto case12 = tump::index_of_v<long long, list1>;

    ASSERT_EQ(case9, 1);
    ASSERT_EQ(case10, -1);
    ASSERT_EQ(case11, 2);
    ASSERT_EQ(case12, -1);
}

TEST(TumpAlgorithmTest, ReplaceIfTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long, char>;
    
    constexpr auto case1 = std::is_same_v<
        tump::replace_if_t<tump::is_integral, short, list1>,
        tump::list<short, float, double, short, short, short>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::replace_t<char, short, list1>,
        tump::list<int, float, double, short, unsigned long, short>
    >;
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, ZipTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long, char>;

    constexpr auto case1 = std::is_same_v<
        tump::zip_t<list1, tump::reverse_t<list1>>,
        tump::list<
            tump::list<int, char>,
            tump::list<float, unsigned long>,
            tump::list<double, char>,
            tump::list<char, double>,
            tump::list<unsigned long, float>,
            tump::list<char, int>
        >
    >;

    ASSERT_TRUE(case1);
}

TEST(TumpAlgorithmTest, CountIfTest)
{
    using list1 = tump::list<int, float, double, char, unsigned long, long double, void>;

    constexpr auto case1 = tump::count_if_v<tump::is_integral, list1>;
    ASSERT_EQ(case1, 3);
}

TEST(TumpAlgorithmTest, FillTest)
{
    using list1 = tump::list<int, float>;
    using list2 = tump::empty<std::tuple>;
    using list3 = tump::vlist<>;

    constexpr auto case1 = std::is_same_v<
        tump::fill_t<list1, tump::type_value<double, 4u>>,
        tump::list<double, double, double, double>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::fill_t<list2, tump::fill_type_arg<long, 3>>,
        std::tuple<long, long, long>
    >;
    constexpr auto case3 = std::is_same_v<
        tump::fill_t<list3, tump::fill_value_arg<long(3), 3u>>,
        tump::vlist<long(3), long(3), long(3)>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
}

TEST(TumpAlgorithmTest, MpMaxMinTest)
{
    using list1 = tump::list<std::int32_t, std::uint64_t, std::int8_t, std::uint16_t>;
    using list2 = tump::vlist<int(1), std::uint16_t(5), char(-3), std::int64_t(-2)>;

    constexpr auto case1 = std::is_same_v<
        tump::mp_max_t<list1>,
        std::uint64_t
    >;
    constexpr auto case2 = tump::mp_max_v<list2, tump::comparing_value_member>;
    constexpr auto case3 = std::is_same_v<
        tump::mp_min_t<list1>,
        std::int8_t
    >;
    constexpr auto case4 = tump::mp_min_v<list2, tump::comparing_value_member>;

    ASSERT_TRUE(case1);
    ASSERT_EQ(case2, std::uint16_t(5));
    ASSERT_TRUE(case3);
    ASSERT_EQ(case4, char(-3));
}

TEST(TumpAlgorithmTest, SortTest)
{
    using list1 = tump::list<std::int32_t, std::uint64_t, std::int8_t, std::uint16_t, std::uint8_t, std::int64_t>;
    using list2 = tump::vlist<int(1), std::uint16_t(5), char(-3), std::int64_t(-2)>;

    constexpr auto case1 = std::is_same_v<
        tump::sort_t<list1>,
        tump::list<std::uint8_t, std::int8_t, std::uint16_t, std::int32_t, std::int64_t, std::uint64_t>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::sort_t<list2, tump::comparing_value_member>,
        tump::vlist<char(-3), std::int64_t(-2), int(1), std::uint16_t(5)>
    >;

    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
}

TEST(TumpAlgorithmTest, AddOptionalTest)
{
    constexpr auto case1 = std::is_same_v<
        tump::add_optional_t<int>, std::optional<int>
    >;
    constexpr auto case2 = std::is_same_v<
        tump::add_optional_t<std::optional<int>>, std::optional<int>
    >;

    constexpr auto case3 = std::is_same_v<
        tump::remove_optional_t<int>, int
    >;
    constexpr auto case4 = std::is_same_v<
        tump::remove_optional_t<std::optional<int>>, int
    >;
    
    ASSERT_TRUE(case1);
    ASSERT_TRUE(case2);
    ASSERT_TRUE(case3);
    ASSERT_TRUE(case4);
}
