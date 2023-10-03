#ifndef TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_ZIP_HPP
#define TUMP_INCLUDE_GUARD_TUMP_ALGORITHM_ZIP_HPP

#include <tump/algorithm/pop.hpp>

namespace tump
{
    namespace fn
    {
        template <TypeList Result, TypeList... Lists>
        struct zip_impl : public zip_impl<
            push_back_t<Result, list<get_front_t<Lists>...>>,
            pop_front_t<to_norm_li_t<Lists>>...
        > {};

        // GCC-10 でrequire節のみでの特殊化をはじかれたため、修正
        // reverse.hpp のほうでは特にエラーを吐かないので、これが通らないのが謎
        // template <TypeList Result, TypeList... Lists>
        // requires (std::is_same_v<list<>, Lists> && ...)
        // struct zip_impl<Result, Lists...> : public std::type_identity<Result> {};
        
        template <class... ZipedElements, TypeList... Lists>
        requires (std::is_same_v<list<>, Lists> && ...)
        struct zip_impl<list<ZipedElements...>, Lists...> : public std::type_identity<list<ZipedElements...>> {};

        /**
         * 2 つのリストから同じインデックスの型を 1 つずつ取り出し、ペアとした要素を持つリストを作成する
        */
        template <TypeList... Lists>
        requires ((len_v<Lists> == ...) && sizeof...(Lists) >= 2)
        using zip = zip_impl<list<>, Lists...>;
    }

    /**
     * 2 つのリストから同じインデックスの型を 1 つずつ取り出し、ペアとした要素を持つリストを作成する
    */
    using zip = cbk<fn::zip, 2>;

    /**
     * リストの中身をDestにコピーする
    */
    template <TypeList... Lists>
    using zip_t = typename fn::zip<Lists...>::type;

    template <std::size_t ArgsSize, TypeList... Lists>
    struct fn::mp_invoke_result<cbk<fn::zip, ArgsSize>, Lists...> : public constraint_st_type_list<list<>> {};
}

#endif