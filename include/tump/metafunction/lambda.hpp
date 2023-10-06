#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_LAMBDA_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_LAMBDA_HPP

#include <tump/metafunction/expression.hpp>
#include <tump/algorithm/unique.hpp>
#include <tump/algorithm/replace_if.hpp>
#include <tump/algorithm/zip.hpp>

// TODO: invoke_resultの特殊化を書く

namespace tump
{
    /**
     * ラムダ式の仮引数登録用
    */
    template <class Head, class... Types>
    requires (is_unique_v<list<Head, Types...>>)
    using lambda_args = list<Head, Types...>;

    /**
     * ラムダ式の、式
    */
    template <class Head, class... Types>
    using lambda_exp = fn::exp<Head, Types...>;

    /**
     * わかりやすいようにラムダ式用のそれっぽい仮引数の型を定義しておく
     * 別の型と識別させることが目的のため、テンプレートパラメータ自体には意味はない
    */
    template <auto V>
    struct _farg {};

    using _arg1 = _farg<1>;
    using _arg2 = _farg<2>;
    using _arg3 = _farg<3>;
    using _arg4 = _farg<4>;

    using _argx = _farg<'x'>;
    using _argy = _farg<'y'>;
    using _argz = _farg<'z'>;

    using _arga = _farg<'a'>;
    using _argb = _farg<'b'>;
    using _argc = _farg<'c'>;

    namespace fn
    {
        /**
         * 仮引数を実引数に置き換える
        */
        template <TypeList ArgPaire, TypeList Expression>
        struct lambda_impl;

        template <class FormalArg, class ActualArg, TypeList Expression>
        struct lambda_impl<list<FormalArg, ActualArg>, Expression> : public replace<FormalArg, ActualArg, Expression> {};
        
        /**
         * ラムダ式生成
        */
        template <TypeList FormalArgList, TypeList Expression, class... ActualArgs>
        requires (!is_empty_v<FormalArgList> && is_exp_v<Expression> && len_v<FormalArgList> == sizeof...(ActualArgs))
        using lambda = unnorm_li_t<
            empty<exp>,
            foldr_t<
                cbk<lambda_impl, 2>,
                to_norm_li_t<Expression>,
                zip_t<FormalArgList, list<ActualArgs...>>
            >
        >;
    }

    /**
     * ラムダ式
    */
    template <TypeList FormalArgList, class Expression>
    using lambda = partial_apply<cbk<fn::lambda, 2 + len_v<FormalArgList>>, FormalArgList, Expression>;

    /**
     * ラムダ式
    */
    template <TypeList FormalArgList, TypeList Expression, class... ActualArgs>
    using lambda_t = typename fn::lambda<FormalArgList, Expression, ActualArgs...>::type;
}

#endif
