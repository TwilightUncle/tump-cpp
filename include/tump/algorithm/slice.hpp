#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP

#include <tump/algorithm/pop.hpp>

namespace tump
{
    template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
    struct slice_impl;

    template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
    requires (!is_empty_v<List> && Size > 0)
    struct slice_impl<List, Result, Start, Size, Stride>
        : public slice_impl<pop_front_t<List>, Result, Start - 1, Size, Stride>
    {};

    template <TypeList List, TypeList Result, std::size_t Size, std::size_t Stride>
    requires (!is_empty_v<List> && Size > 0)
    struct slice_impl<List, Result, 0, Size, Stride> : public slice_impl<
        pop_front_t<List>,
        push_back_t<Result, get_front_t<List>>,
        Stride,
        Size - 1,
        Stride
    > {};

    template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
    requires (is_empty_v<List> || !Size)
    struct slice_impl<List, Result, Start, Size, Stride> : public std::type_identity<Result> {};

    /**
     * リストを切り出す
    */
    template <TypeList List, std::size_t Start, std::size_t Size = len_v<List>, std::size_t Stride = 0>
    using slice = slice_impl<List, make_empty_t<List>, Start, Size, Stride>;

    /**
     * リストを切り出す
    */
    template <TypeList List, std::size_t Start, std::size_t Size = len_v<List>, std::size_t Stride = 0>
    using slice_t = slice<List, Start, Size, Stride>::type;

    // TODO: 戻り値制約についても考える(本メタ関数を格納可能なcallbackを定義か？)
}

#endif
