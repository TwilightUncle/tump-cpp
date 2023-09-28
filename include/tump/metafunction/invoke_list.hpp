#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_LIST_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_LIST_HPP

#include <tump/metafunction/invoke.hpp>

namespace tump
{
    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    struct invoke_list;

    template <Invocable F, template <class...> class Wrapper, class... Args>
    struct invoke_list<F, Wrapper<Args...>> : public invoke<F, Args...> {};

    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires TFunctional<invoke_list<F, ArgList>>
    using invoke_list_t = typename invoke_list<F, ArgList>::type;

    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires VFunctional<invoke_list<F, ArgList>>
    constexpr auto invoke_list_v = invoke_list<F, ArgList>::value;
}

#endif
