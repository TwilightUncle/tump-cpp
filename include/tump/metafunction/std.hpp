#ifndef TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_STD_HPP
#define TUMP_INCLUDE_GUARD_TUMP_METAFUNCTION_STD_HPP

#include TUMP_COMMON_INCLUDE(version.hpp)
#include TUMP_COMMON_INCLUDE(metafunction/invoke_result.hpp)

namespace tump
{
    // -------------------------------------------------------------------
    // バージョンに左右されるが常にほしいものやちょっといじったものをあらかじめ定義
    // -------------------------------------------------------------------

    namespace fn
    {
        /**
         * scoped enum判定
         * c++23未対応の場合、boostソースより
        */
#ifdef TUMP_ENABLE_CPP23
        template <class T>
        using is_scoped_enum = std::is_scoped_enum<T>;
#else
        template <class T>
        struct is_scoped_enum
            : std::conjunction<std::is_enum<T>, std::negation<std::is_convertible<T, int> > >::type {};
#endif

        /**
         * is_sameの逆
        */
        template <class T1, class T2>
        using is_not_same = typename std::negation<std::is_same<T1, T2>>::type;
    }

    /**
     * scoped enum判定
    */
    template <class T>
    constexpr auto is_scoped_enum_v = fn::is_scoped_enum<T>::value;

    template <class T1, class T2>
    constexpr auto is_not_same_v = fn::is_not_same<T1, T2>::value;


    // -------------------------------------------------------------------
    // 標準ライブラリのメタ関数をあらかじめコールバック化
    // -------------------------------------------------------------------

    using is_void                       = cbk<std::is_void,                     1>;
    using is_null_pointer               = cbk<std::is_null_pointer,             1>;
    using is_integral                   = cbk<std::is_integral,                 1>;
    using is_floating_point             = cbk<std::is_floating_point,           1>;
    using is_array                      = cbk<std::is_array,                    1>;
    using is_pointer                    = cbk<std::is_pointer,                  1>;
    using is_lvalue_reference           = cbk<std::is_lvalue_reference,         1>;
    using is_rvalue_reference           = cbk<std::is_rvalue_reference,         1>;
    using is_member_object_pointer      = cbk<std::is_member_object_pointer,    1>;
    using is_member_function_pointer    = cbk<std::is_member_function_pointer,  1>;
    using is_enum                       = cbk<std::is_enum,                     1>;
    using is_union                      = cbk<std::is_union,                    1>;
    using is_class                      = cbk<std::is_class,                    1>;
    using is_function                   = cbk<std::is_function,                 1>;

    template <class T>
    struct fn::mp_invoke_result<is_void, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_null_pointer, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_integral, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_floating_point, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_array, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_pointer, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_lvalue_reference, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_rvalue_reference, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_member_object_pointer, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_member_function_pointer, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_enum, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_union, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_class, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_function, T> : public constraint_bool_constant {};

    using is_reference      = cbk<std::is_reference,        1>;
    using is_arithmetic     = cbk<std::is_arithmetic,       1>;
    using is_fundamental    = cbk<std::is_fundamental,      1>;
    using is_object         = cbk<std::is_object,           1>;
    using is_scalar         = cbk<std::is_scalar,           1>;
    using is_compound       = cbk<std::is_compound,         1>;
    using is_member_pointer = cbk<std::is_member_pointer,   1>;
    using is_scoped_enum    = cbk<fn::is_scoped_enum,       1>;

    template <class T>
    struct fn::mp_invoke_result<is_reference, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_arithmetic, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_fundamental, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_object, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_scalar, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_compound, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_member_pointer, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_scoped_enum, T> : public constraint_bool_constant {};

    using is_const                              = cbk<std::is_const,                            1>;
    using is_volatile                           = cbk<std::is_volatile,                         1>;
    using is_trivial                            = cbk<std::is_trivial,                          1>;
    using is_trivially_copyable                 = cbk<std::is_trivially_copyable,               1>;
    using is_standard_layout                    = cbk<std::is_standard_layout,                  1>;
    using is_polymorphic                        = cbk<std::is_polymorphic,                      1>;
    using is_abstract                           = cbk<std::is_abstract,                         1>;
    using is_final                              = cbk<std::is_final,                            1>;
    using is_aggregate                          = cbk<std::is_aggregate,                        1>;
    using is_signed                             = cbk<std::is_signed,                           1>;
    using is_unsigned                           = cbk<std::is_unsigned,                         1>;
    using is_bounded_array                      = cbk<std::is_bounded_array,                    1>;
    using is_unbounded_array                    = cbk<std::is_unbounded_array,                  1>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using is_constructible                      = cbk<std::is_constructible,             ArgsSize>;
    using is_default_constructible              = cbk<std::is_default_constructible,            1>;
    using is_copy_constructible                 = cbk<std::is_copy_constructible,               1>;
    using is_move_constructible                 = cbk<std::is_move_constructible,               1>;
    using is_assignable                         = cbk<std::is_assignable,                       2>;
    using is_copy_assignable                    = cbk<std::is_copy_assignable,                  1>;
    using is_move_assignable                    = cbk<std::is_move_assignable,                  1>;
    using is_destructible                       = cbk<std::is_destructible,                     1>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using is_trivially_constructible            = cbk<std::is_trivially_constructible,   ArgsSize>;
    using is_trivially_default_constructible    = cbk<std::is_trivially_default_constructible,  1>;
    using is_trivially_copy_constructible       = cbk<std::is_trivially_copy_constructible,     1>;
    using is_trivially_move_constructible       = cbk<std::is_trivially_move_constructible,     1>;
    using is_trivially_assignable               = cbk<std::is_trivially_assignable,             1>;
    using is_trivially_copy_assignable          = cbk<std::is_trivially_copy_assignable,        1>;
    using is_trivially_move_assignable          = cbk<std::is_trivially_move_assignable,        1>;
    using is_trivially_destructible             = cbk<std::is_trivially_destructible,           1>;
    using is_nothrow_constructible              = cbk<std::is_nothrow_constructible,            1>;
    using is_nothrow_default_constructible      = cbk<std::is_nothrow_default_constructible,    1>;
    using is_nothrow_copy_constructible         = cbk<std::is_nothrow_copy_constructible,       1>;
    using is_nothrow_move_constructible         = cbk<std::is_nothrow_move_constructible,       1>;
    using is_nothrow_assignable                 = cbk<std::is_nothrow_assignable,               2>;
    using is_nothrow_copy_assignable            = cbk<std::is_nothrow_copy_assignable,          1>;
    using is_nothrow_move_assignable            = cbk<std::is_nothrow_move_assignable,          1>;
    using is_nothrow_destructible               = cbk<std::is_nothrow_destructible,             1>;
    using has_virtual_destructor                = cbk<std::has_virtual_destructor,              1>;
    using is_swappable_with                     = cbk<std::is_swappable_with,                   2>;
    using is_swappable                          = cbk<std::is_swappable,                        1>;
    using is_nothrow_swappable_with             = cbk<std::is_nothrow_swappable_with,           2>;
    using is_nothrow_swappable                  = cbk<std::is_nothrow_swappable,                1>;
    using has_unique_object_representations     = cbk<std::has_unique_object_representations,   1>;

    template <class T>
    struct fn::mp_invoke_result<is_const, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_volatile, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivial, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_copyable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_standard_layout, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_polymorphic, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_abstract, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_final, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_aggregate, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_signed, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_unsigned, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_bounded_array, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_unbounded_array, T> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class T, class... Args>
    struct fn::mp_invoke_result<is_constructible<ArgsSize>, T, Args...> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_default_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_copy_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_move_constructible, T> : public constraint_bool_constant {};
    template <class To, class From>
    struct fn::mp_invoke_result<is_assignable, To, From> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_copy_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_move_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_destructible, T> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class T, class... Args>
    struct fn::mp_invoke_result<is_trivially_constructible<ArgsSize>, T, Args...> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_default_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_copy_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_move_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_copy_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_move_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_trivially_destructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_default_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_copy_constructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_move_constructible, T> : public constraint_bool_constant {};
    template <class To, class From>
    struct fn::mp_invoke_result<is_nothrow_assignable, To, From> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_copy_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_move_assignable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_destructible, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<has_virtual_destructor, T> : public constraint_bool_constant {};
    template <class T1, class T2>
    struct fn::mp_invoke_result<is_swappable_with, T1, T2> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_swappable, T> : public constraint_bool_constant {};
    template <class T1, class T2>
    struct fn::mp_invoke_result<is_nothrow_swappable_with, T1, T2> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<is_nothrow_swappable, T> : public constraint_bool_constant {};
    template <class T>
    struct fn::mp_invoke_result<has_unique_object_representations, T> : public constraint_bool_constant {};

    using alignment_of  = cbk<std::alignment_of,    1>;
    using rank          = cbk<std::rank,            1>;
    // テンプレートパラメータが未対応
    // using extent        = cbk<std::extent,          1>;

    // template <class T>
    // struct mp_invoke_result<alignment_of, T> : public {};
    // template <class T>
    // struct mp_invoke_result<rank, T> : public {};
    // template <class T>
    // struct mp_invoke_result<extent, T> : public {};

    using is_same                               = cbk<std::is_same,                             2>;
    using is_not_same                           = cbk<fn::is_not_same,                          2>;
    using is_base_of                            = cbk<std::is_base_of,                          2>;
    using is_convertible                        = cbk<std::is_convertible,                      2>;
    using is_nothrow_convertible                = cbk<std::is_nothrow_convertible,              2>;
    // なんかいなかった
    // using is_layout_compatible                  = cbk<std::is_layout_compatible,                2>;
    // using is_pointer_interconvertible_base_of   = cbk<std::is_pointer_interconvertible_base_of, 2>;
#ifdef TUMP_ENABLE_CPP23
    using reference_constructs_from_temporary   = cbk<std::reference_constructs_from_temporary, 2>;
    using reference_converts_from_temporary     = cbk<std::reference_converts_from_temporary,   2>;
#endif

    template <class T1, class T2>
    struct fn::mp_invoke_result<is_same, T1, T2> : public constraint_bool_constant {};
    template <class T1, class T2>
    struct fn::mp_invoke_result<is_not_same, T1, T2> : public constraint_bool_constant {};
    template <class Base, class Derived>
    struct fn::mp_invoke_result<is_base_of, Base, Derived> : public constraint_bool_constant {};
    template <class From, class To>
    struct fn::mp_invoke_result<is_convertible, From, To> : public constraint_bool_constant {};
    template <class From, class To>
    struct fn::mp_invoke_result<is_nothrow_convertible, From, To> : public constraint_bool_constant {};
    // template <class T1, class T2>
    // struct mp_invoke_result<is_layout_compatible, T1, T2> : public constraint_bool_constant {};
    // template <class T1, class T2>
    // struct mp_invoke_result<is_pointer_interconvertible_base_of, T1, T2> : public constraint_bool_constant {};
#ifdef TUMP_ENABLE_CPP23
    template <class T1, class T2>
    struct fn::mp_invoke_result<reference_constructs_from_temporary, T1, T2> : public constraint_bool_constant {};
    template <class T1, class T2>
    struct fn::mp_invoke_result<reference_converts_from_temporary, T1, T2> : public constraint_bool_constant {};
#endif

    using remove_const      = cbk<std::remove_const,    1>;
    using remove_volatile   = cbk<std::remove_volatile, 1>;
    using remove_cv         = cbk<std::remove_cv,       1>;
    using add_const         = cbk<std::add_const,       1>;
    using add_volatile      = cbk<std::add_volatile,    1>;
    using add_cv            = cbk<std::add_cv,          1>;

    // template <class T>
    // struct mp_invoke_result<remove_const, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<remove_volatile, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<remove_cv, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<add_const, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<add_volatile, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<add_cv, T> : public constraint_bool_constant {};

    using remove_reference      = cbk<std::remove_reference,        1>;
    using add_lvalue_reference  = cbk<std::add_lvalue_reference,    1>;
    using add_rvalue_reference  = cbk<std::add_rvalue_reference,    1>;

    // template <class T>
    // struct mp_invoke_result<remove_reference, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<add_lvalue_reference, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<add_rvalue_reference, T> : public constraint_bool_constant {};

    using make_signed   = cbk<std::make_signed,     1>;
    using make_unsigned = cbk<std::make_unsigned,   1>;

    // template <class T>
    // struct mp_invoke_result<make_signed, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<make_unsigned, T> : public constraint_bool_constant {};

    using remove_extent         = cbk<std::remove_extent,       1>;
    using remove_all_extents    = cbk<std::remove_all_extents,  1>;

    // template <class T>
    // struct mp_invoke_result<remove_extent, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<remove_all_extents, T> : public constraint_bool_constant {};

    using add_pointer       = cbk<std::add_pointer,     1>;
    using remove_pointer    = cbk<std::remove_pointer,  1>;

    // template <class T>
    // struct mp_invoke_result<add_pointer, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<remove_pointer, T> : public constraint_bool_constant {};

    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using is_invocable              = cbk<std::is_invocable,            ArgsSize>;
    template <unsigned int ArgsSize = 3>
    requires (ArgsSize > 1)
    using is_invocable_r            = cbk<std::is_invocable_r,          ArgsSize>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using is_nothrow_invocable      = cbk<std::is_nothrow_invocable,    ArgsSize>;
    template <unsigned int ArgsSize = 3>
    requires (ArgsSize > 1)
    using is_nothrow_invocable_r    = cbk<std::is_nothrow_invocable_r,  ArgsSize>;

    template <unsigned int ArgsSize, class Callable, class... Args>
    struct fn::mp_invoke_result<is_invocable<ArgsSize>, Callable, Args...> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class Rx, class Callable, class... Args>
    struct fn::mp_invoke_result<is_invocable_r<ArgsSize>, Rx, Callable, Args...> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class Callable, class... Args>
    struct fn::mp_invoke_result<is_nothrow_invocable<ArgsSize>, Callable, Args...> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class Rx, class Callable, class... Args>
    struct fn::mp_invoke_result<is_nothrow_invocable_r<ArgsSize>, Rx, Callable, Args...> : public constraint_bool_constant {};

    using type_identity             = cbk<std::type_identity,           1>;
    using remove_cvref              = cbk<std::remove_cvref,            1>;
    using decay                     = cbk<std::decay,                   1>;
    // テンプレートパラメータが未対応
    // using conditional               = cbk<std::conditional,             1>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using common_type               = cbk<std::common_type,      ArgsSize>;
    template <unsigned int ArgsSize = 1>
    using void_t                    = cbk<std::void_t,           ArgsSize>;
    // テンプレートパラメータが未対応
    // using basic_common_reference    = cbk<std::basic_common_reference,  1>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using common_reference          = cbk<std::common_reference, ArgsSize>;
    using underlying_type           = cbk<std::underlying_type,         1>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using invoke_result             = cbk<std::invoke_result,    ArgsSize>;
    using unwrap_reference          = cbk<std::unwrap_reference,        1>;
    using unwrap_ref_decay          = cbk<std::unwrap_ref_decay,        1>;

    // template <class T>
    // struct mp_invoke_result<type_identity, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<remove_cvref, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<decay, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<conditional, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<common_type, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<void_t, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<basic_common_reference, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<common_reference, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<underlying_type, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<result_of, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<mp_invoke_result, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<unwrap_reference, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<unwrap_ref_decay, T> : public constraint_bool_constant {};
    
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using conjunction   = cbk<std::conjunction, ArgsSize>;
    template <unsigned int ArgsSize = 2>
    requires (ArgsSize > 0)
    using disjunction   = cbk<std::disjunction, ArgsSize>;
    using negation      = cbk<std::negation,    1>;

    template <unsigned int ArgsSize, class... Traits>
    struct fn::mp_invoke_result<conjunction<ArgsSize>, Traits...> : public constraint_bool_constant {};
    template <unsigned int ArgsSize, class... Traits>
    struct fn::mp_invoke_result<disjunction<ArgsSize>, Traits...> : public constraint_bool_constant {};
    template <class Trait>
    struct fn::mp_invoke_result<negation, Trait> : public constraint_bool_constant {};

    // なんかいない
    // using is_pointer_interconvertible_with_class = cbk<std::is_pointer_interconvertible_with_class, 2>;
    // using is_corresponding_member = cbk<std::is_corresponding_member, 4>;
    
    // template <class T>
    // struct mp_invoke_result<is_pointer_interconvertible_with_class, T> : public constraint_bool_constant {};
    // template <class T>
    // struct mp_invoke_result<is_corresponding_member, T> : public constraint_bool_constant {};
}

#endif
