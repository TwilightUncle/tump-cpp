#ifndef TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_LIST_HPP
#define TUMP_V_1_0_0_INCLUDE_GUARD_TUMP_METAFUNCTION_INVOKE_LIST_HPP

#include TUMP_COMMON_INCLUDE(metafunction/invoke.hpp)

namespace tump_1_0_0
{
    namespace fn
    {
        /**
         * コールバック化したメタ関数を実行  
         * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
        */
        template <Invocable F, class ArgList>
        struct invoke_list;

        template <Invocable F, template <class...> class Wrapper, class... Args>
        struct invoke_list<F, Wrapper<Args...>> : public invoke<F, Args...> {};
    }

    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    using invoke_list = cbk<fn::invoke_list, 2>;

    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires TFunctional<fn::invoke_list<F, ArgList>>
    using invoke_list_t = typename fn::invoke_list<F, ArgList>::type;

    /**
     * コールバック化したメタ関数を実行  
     * invokeとは異なり、引数はリストとして一つの型にまとめたものを使用
    */
    template <Invocable F, class ArgList>
    requires VFunctional<fn::invoke_list<F, ArgList>>
    constexpr auto invoke_list_v = fn::invoke_list<F, ArgList>::value;
}

#endif
