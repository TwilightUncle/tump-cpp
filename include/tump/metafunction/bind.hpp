#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_BIND_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_BIND_HPP

#include <concepts>
#include <tump/metafunction/callback.hpp>

namespace tump
{
    template <unsigned int ArgsSize, class F>
    struct _is_allowed_args_size : public std::false_type {};

    template <unsigned int ArgsSize, _DerivedAsArgSizeMembers F>
    struct _is_allowed_args_size<ArgsSize, F> : public std::bool_constant<
        !F::is_check_args_size || F::args_size >= ArgsSize
    > {};

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
}

#endif
