#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_SLICE_HPP

#include TUMP_COMMON_INCLUDE(algorithm/pop.hpp)

namespace tump
{
    template <std::size_t... Sizes>
    struct size_args {};

    namespace fn
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
                    std::conditional_t<Start != 0, ::tump::left, ::tump::push_back<>>,
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
        template <TypeListOrValueList List, class SizeArgs>
        struct slice;
    
        template <TypeListOrValueList List, std::size_t Start, std::size_t Size, std::size_t Stride>
        struct slice<List, size_args<Start, Size, Stride>> : public unnorm_li<
            List,
            typename _::slice_impl<
                to_norm_li_t<List>, list<>, Start, Size, Stride
            >::type
        > {};

        template <TypeListOrValueList List, std::size_t Start, std::size_t Size>
        struct slice<List, size_args<Start, Size>> : public slice<List, size_args<Start, Size, 0>> {};

        template <TypeListOrValueList List, std::size_t Start>
        struct slice<List, size_args<Start>> : public slice<List, size_args<Start, len_v<List>>> {};
    }

    /**
     * リストを切り出す
    */
    using slice = cbk<fn::slice, 2>;

    /**
     * リストを切り出す
    */
    template <TypeListOrValueList List, class SizeArgs>
    using slice_t = typename fn::slice<List, SizeArgs>::type;
}

#endif
