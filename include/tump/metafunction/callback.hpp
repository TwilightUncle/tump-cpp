#ifndef TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_CALLBACK_HPP
#define TUMP_V_0_1_2_INCLUDE_GUARD_TUMP_METAFUNCTION_CALLBACK_HPP

#include <type_traits>
#include <concepts>

namespace tump_0_1_2
{
    namespace fn
    {
        namespace impl
        {
            template <unsigned int ArgsSize, bool IsCheckArgsSize>
            struct args_size_members
            {
                static constexpr auto is_check_args_size = IsCheckArgsSize;
                static constexpr auto args_size = ArgsSize;
            };

            template <class T>
            concept DerivedAsArgSizeMembers = requires {
                { T::is_check_args_size } -> std::convertible_to<bool>;
                { T::args_size } -> std::convertible_to<unsigned int>;
            };
        }

        template <unsigned int ArgsSize, class F>
        struct is_allowed_args_size : public std::false_type {};

        template <unsigned int ArgsSize, impl::DerivedAsArgSizeMembers F>
        struct is_allowed_args_size<ArgsSize, F> : public std::bool_constant<
            !F::is_check_args_size || F::args_size >= ArgsSize
        > {};

        template <unsigned int ArgsSize, class F>
        struct eq_args_size : public std::false_type {};

        template <unsigned int ArgsSize, impl::DerivedAsArgSizeMembers F>
        struct eq_args_size<ArgsSize, F> : public std::bool_constant<
            !F::is_check_args_size || F::args_size == ArgsSize
        > {};
    }

    /**
     * @class
     * @brief メタ関数をテンプレート型から型に変換する
     * @tparam MetaFunc コールバックとして扱いたいメタ関数
     * @tparam ArgsSize MetaFuncで指定したメタ関数の引数の数を指定。0の場合はメタ関数実行時に引数の数のチェックを行わない
    */
    template <template <class...> class MetaFunc, unsigned int ArgsSize = 0>
    struct callback : public fn::impl::args_size_members<ArgsSize, bool(ArgsSize)> {};

    /**
     * callback のエイリアス
    */
    template <template <class...> class MetaFunc, unsigned int ArgsSize = 0>
    using cbk = callback<MetaFunc, ArgsSize>;

    template <unsigned int ArgsSize, bool IsCheckArgsSize = bool(ArgsSize)>
    struct optional_args_for_is_callback {};

    namespace fn
    {
        namespace impl
        {
            template <class F, unsigned int CheckArgsSize, bool IsCheckArgsSize>
            using is_callback_impl = std::disjunction<
                std::bool_constant<!IsCheckArgsSize>,
                eq_args_size<CheckArgsSize, F>
            >;
        }

        /**
         * @fn
         * @brief コールバック化したか、コールバック化したメタ関数の引数を部分適用したものか判定
        */
        template <class F, class OptionalArgs = optional_args_for_is_callback<0>> struct is_callback : public std::false_type {};

        template <template <class...> class MetaFunc, unsigned int ArgsSize, unsigned int CheckArgsSize, bool IsCheckArgsSize>
        struct is_callback<callback<MetaFunc, ArgsSize>, optional_args_for_is_callback<CheckArgsSize, IsCheckArgsSize>>
            : public impl::is_callback_impl<callback<MetaFunc, ArgsSize>, CheckArgsSize, IsCheckArgsSize>
        {};
    }

    /**
     * @fn
     * @brief コールバック化したメタ関数であるか、またはコールバック化したメタ関数の引数を部分適用したものか判定
    */
    using is_callback = cbk<fn::is_callback, 2>;

    /**
     * @fn
     * @brief コールバック化したメタ関数であるか、またはコールバック化したメタ関数の引数を部分適用したものか判定
    */
    template <class F, class OptionalArgs = optional_args_for_is_callback<0>>
    constexpr auto is_callback_v = fn::is_callback<F, OptionalArgs>::value;

    /**
     * コールバック化したメタ関数であるか判定
     * 引数の数の検査を行わない
    */
    template <class F>
    concept Invocable = is_callback_v<F>;

    /**
     * コールバック化したメタ関数であるか判定
     * 該当のメタ関数に指定する引数がArgsSizeと一致するかの確認も実施
    */
    template <class F, unsigned int ArgsSize>
    concept InvocableArgN = is_callback_v<F, optional_args_for_is_callback<ArgsSize, true>>;
}

#endif
