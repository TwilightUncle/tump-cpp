#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_PARTIAL_APPLY_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_PARTIAL_APPLY_HPP

#include TUMP_V_0_1_2_COMMON_INCLUDE(metafunction/callback.hpp)

namespace tump_0_1_2
{
    /**
     * @class
     * @brief コールバック化したメタ関数に対して、引数の部分適用を行う
     * @tparam MetaFunc コールバックとして扱いたいメタ関数
     * @tparam ArgsSize MetaFuncで指定したメタ関数の引数の数を指定。0の場合はメタ関数実行時に引数の数のチェックを行わない
    */
    template <Invocable F, class... PartialArgs>
    requires (fn::is_allowed_args_size<sizeof...(PartialArgs), F>::value)
    struct partial_apply : public fn::impl::args_size_members<
        F::is_check_args_size
            ? F::args_size - sizeof...(PartialArgs)
            : 0,
        F::is_check_args_size
    > {};

    namespace fn
    {
        template <impl::DerivedAsArgSizeMembers InnerF, class... PartialArgs, unsigned int ArgsSize, bool IsCheckArgsSize>
        requires (impl::is_callback_impl<partial_apply<InnerF, PartialArgs...>, ArgsSize, IsCheckArgsSize>::value)
        struct is_callback<partial_apply<InnerF, PartialArgs...>, optional_args_for_is_callback<ArgsSize, IsCheckArgsSize>> : public is_callback<
            InnerF,
            optional_args_for_is_callback<
                sizeof...(PartialArgs) + ArgsSize,
                IsCheckArgsSize
            >
        > {};
    }
}

#endif
