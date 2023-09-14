#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_APPLY_LIST_HPP

#include <tump/metafunction/apply.hpp>

namespace tump
{
    /**
     * コールバック化したメタ関数を実行  
     * applyとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    struct apply_list;

    template <Invocable F, template <class...> class Wrapper, class... Args>
    struct apply_list<F, Wrapper<Args...>> : public apply<F, Args...> {};

    /**
     * コールバック化したメタ関数を実行  
     * applyとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires TFunctional<apply_list<F, ArgList>>
    using apply_list_t = apply_list<F, ArgList>::type;

    /**
     * コールバック化したメタ関数を実行  
     * applyとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires VFunctional<apply_list<F, ArgList>>
    constexpr auto apply_list_v = apply_list<F, ArgList>::value;
}

#endif
