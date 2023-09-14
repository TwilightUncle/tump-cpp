#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_CALLBACK_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_CALLBACK_HPP

#include <type_traits>
#include <concepts>

namespace tump {
    template <unsigned int ArgsSize, bool IsCheckArgsSize>
    struct _args_size_members
    {
        static constexpr auto is_check_args_size = IsCheckArgsSize;
        static constexpr auto args_size = ArgsSize;
    };

    template <class T>
    concept _DerivedAsArgSizeMembers = requires {
        { T::is_check_args_size } -> std::convertible_to<bool>;
        { T::args_size } -> std::convertible_to<unsigned int>;
    };

    /**
     * @class
     * @brief メタ関数をテンプレート型から型に変換する
     * @tparam MetaFunc コールバックとして扱いたいメタ関数
     * @tparam ArgsSize MetaFuncで指定したメタ関数の引数の数を指定。0の場合はメタ関数実行時に引数の数のチェックを行わない
    */
    template <template <class...> class MetaFunc, unsigned int ArgsSize = 0>
    struct callback : public _args_size_members<ArgsSize, bool(ArgsSize)> {};

    /**
     * @fn
     * @brief コールバック化したか、コールバック化したメタ関数の引数を部分適用したものか判定
    */
    template <class F> struct is_callback : public std::false_type {};

    template <template <class...> class MetaFunc, unsigned int ArgsSize>
    struct is_callback<callback<MetaFunc, ArgsSize>> : public std::true_type {};

    template <template <class...> class OuterF, _DerivedAsArgSizeMembers InnerF, class... PartialArgs>
    struct is_callback<OuterF<InnerF, PartialArgs...>> : public is_callback<InnerF> {};

    /**
     * @fn
     * @brief コールバック化したメタ関数であるか、またはコールバック化したメタ関数の引数を部分適用したものか判定
    */
    template <class F>
    constexpr auto is_callback_v = is_callback<F>::value;

    template <class F>
    concept Invocable = is_callback_v<F> && _DerivedAsArgSizeMembers<F>;

    template <class F>
    concept InvocableArg1 = Invocable<F> && (F::args_size == 1 || !F::is_check_args_size);

    template <class F>
    concept InvocableArg2 = Invocable<F> && (F::args_size == 2 || !F::is_check_args_size);
}

#endif
