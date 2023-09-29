#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP

#include <tump/algorithm/pop.hpp>

namespace tump
{
    namespace _
    {
        template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
        struct slice_impl;

        template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
        requires (!is_empty_v<List> && Size > 0 && len_v<List> > Start)
        struct slice_impl<List, Result, Start, Size, Stride> : public slice_impl<
            pop_front_t<List>,
            invoke_t<
                std::conditional_t<Start != 0, cbk<left, 2>, cbk<push_back, 2>>,
                Result,
                get_front_t<List>
            >,
            Start != 0 ? Start - 1 : Stride,
            Start != 0 ? Size : Size - 1,
            Stride
        > {};

        template <TypeList List, TypeList Result, std::size_t Start, std::size_t Size, std::size_t Stride>
        requires (is_empty_v<List> || !Size || len_v<List> <= Start)
        struct slice_impl<List, Result, Start, Size, Stride> : public std::type_identity<Result> {};
    }

    /**
     * リストを切り出す
    */
    template <TypeList List, std::size_t Start, std::size_t Size = len_v<List>, std::size_t Stride = 0>
    using slice = _::slice_impl<List, make_empty_t<List>, Start, Size, Stride>;

    /**
     * リストを切り出す
    */
    template <TypeList List, std::size_t Start, std::size_t Size = len_v<List>, std::size_t Stride = 0>
    using slice_t = typename slice<List, Start, Size, Stride>::type;

    // TODO: 戻り値制約についても考える(本メタ関数を格納可能なcallbackを定義か？)
}

#endif
