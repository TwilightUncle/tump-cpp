#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_BIND_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_BIND_HPP

#include <tump/metafunction/callback.hpp>

namespace tump
{
    /**
     * @class
     * @brief コールバック化したメタ関数に対して、引数の部分適用を行う
     * @tparam MetaFunc コールバックとして扱いたいメタ関数
     * @tparam ArgsSize MetaFuncで指定したメタ関数の引数の数を指定。0の場合はメタ関数実行時に引数の数のチェックを行わない
    */
    template <Invocable F, class... PartialArgs>
    requires (_is_allowed_args_size<sizeof...(PartialArgs), F>::value)
    struct bind : public _args_size_members<
        F::is_check_args_size
            ? F::args_size - sizeof...(PartialArgs)
            : 0,
        F::is_check_args_size
    > {};

    template <_DerivedAsArgSizeMembers InnerF, class... PartialArgs, unsigned int ArgsSize, bool IsCheckArgsSize>
    requires (_is_callback_impl<bind<InnerF, PartialArgs...>, ArgsSize, IsCheckArgsSize>::value)
    struct is_callback<bind<InnerF, PartialArgs...>, optional_args_for_is_callback<ArgsSize, IsCheckArgsSize>> : public is_callback<
        InnerF,
        optional_args_for_is_callback<
            sizeof...(PartialArgs) + ArgsSize,
            IsCheckArgsSize
        >
    > {};
}

#endif
