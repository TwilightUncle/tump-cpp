---
title: 標準ライブラリのメタ関数の第一級関数 - TumpCpp リファレンス
---

TumpCpp では、[{`tump::eval`や`tump::exp`|ref/expression/exp}]ですぐに使えるように、主に`<type_traits>`で定義されているメタ関数を第一級関数化する定義を行っています。  
名前空間`tump`の下に定義されており、メタ関数の名称が標準ライブラリと同じものは、機能も標準ライブラリのものと同様になります。  
例えば、`tump::is_same`は`std::is_same`を第一級関数化したメタ関数です。

第一級関数化された可変長引数のメタ関数は、受け取る引数の数をテンプレートパラメータで指定してやる必要があります。

また、引数に非型テンプレートパラメータが含まれているようなメタ関数については、第一級メタ関数化の定義を行っていませんのでご注意ください。

## 例

```cpp
#include <tump.hpp>

// 引数の数が固定のメタ関数の実行例
static_assert(tump::eval<tump::is_void, void>::value == true);
static_assert(tump::eval<tump::is_void, int>::value == false);
static_assert(tump::eval<tump::is_same, int, int>::value == true);

// 可変長引数のメタ関数
// テンプレートパラメータを指定しない場合、デフォルトの引数を受け取る
static_assert(tump::eval<tump::conjunction<>, std::true_type, std::false_type>::value == false);
static_assert(tump::eval<tump::conjunction<3>, std::true_type, std::true_type, std::true_type>::value == false);

int main() {}
```

## 第一級関数化されたメタ関数の一覧

| 識別子 | 受け取るメタ関数の数 |
| --- | --- |
| `tump::is_void` | 1 |
| `tump::is_null_pointer` | 1 |
| `tump::is_integral` | 1 |
| `tump::is_floating_point` | 1 |
| `tump::is_array` | 1 |
| `tump::is_pointer` | 1 |
| `tump::is_lvalue_reference` | 1 |
| `tump::is_rvalue_reference` | 1 |
| `tump::is_member_object_pointer` | 1 |
| `tump::is_member_function_pointer` | 1 |
| `tump::is_enum` | 1 |
| `tump::is_union` | 1 |
| `tump::is_class` | 1 |
| `tump::is_function` | 1 |
| `tump::is_reference` | 1 |
| `tump::is_arithmetic` | 1 |
| `tump::is_fundamental` | 1 |
| `tump::is_object` | 1 |
| `tump::is_scalar` | 1 |
| `tump::is_compound` | 1 |
| `tump::is_member_pointer` | 1 |
| `tump::is_scoped_enum` | 1 |
| `tump::is_const` | 1 |
| `tump::is_volatile` | 1 |
| `tump::is_trivial` | 1 |
| `tump::is_trivially_copyable` | 1 |
| `tump::is_standard_layout` | 1 |
| `tump::is_polymorphic` | 1 |
| `tump::is_abstract` | 1 |
| `tump::is_final` | 1 |
| `tump::is_aggregate` | 1 |
| `tump::is_signed` | 1 |
| `tump::is_unsigned` | 1 |
| `tump::is_bounded_array` | 1 |
| `tump::is_unbounded_array` | 1 |
| `tump::is_constructible` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::is_default_constructible` | 1 |
| `tump::is_copy_constructible` | 1 |
| `tump::is_move_constructible` | 1 |
| `tump::is_assignable` | 2 |
| `tump::is_copy_assignable` | 1 |
| `tump::is_move_assignable` | 1 |
| `tump::is_destructible` | 1 |
| `tump::is_trivially_constructible` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::is_trivially_default_constructible` | 1 |
| `tump::is_trivially_copy_constructible` | 1 |
| `tump::is_trivially_move_constructible` | 1 |
| `tump::is_trivially_assignable` | 1 |
| `tump::is_trivially_copy_assignable` | 1 |
| `tump::is_trivially_move_assignable` | 1 |
| `tump::is_trivially_destructible` | 1 |
| `tump::is_nothrow_constructible` | 1 |
| `tump::is_nothrow_default_constructible` | 1 |
| `tump::is_nothrow_copy_constructible` | 1 |
| `tump::is_nothrow_move_constructible` | 1 |
| `tump::is_nothrow_assignable` | 2 |
| `tump::is_nothrow_copy_assignable` | 1 |
| `tump::is_nothrow_move_assignable` | 1 |
| `tump::is_nothrow_destructible` | 1 |
| `tump::has_virtual_destructor` | 1 |
| `tump::is_swappable_with` | 2 |
| `tump::is_swappable` | 1 |
| `tump::is_nothrow_swappable_with` | 2 |
| `tump::is_nothrow_swappable` | 1 |
| `tump::has_unique_object_representations` | 1 |
| `tump::alignment_of` | 1 |
| `tump::rank` | 1 |
| `tump::is_same` | 2 |
| `tump::is_base_of` | 2 |
| `tump::is_convertible` | 2 |
| `tump::is_nothrow_convertible` | 2 |
| `tump::remove_const` | 1 |
| `tump::remove_volatile` | 1 |
| `tump::remove_cv` | 1 |
| `tump::add_const` | 1 |
| `tump::add_volatile` | 1 |
| `tump::add_cv` | 1 |
| `tump::remove_reference` | 1 |
| `tump::add_lvalue_reference` | 1 |
| `tump::add_rvalue_reference` | 1 |
| `tump::make_signed` | 1 |
| `tump::make_unsigned` | 1 |
| `tump::remove_extent` | 1 |
| `tump::remove_all_extents` | 1 |
| `tump::add_pointer` | 1 |
| `tump::remove_pointer` | 1 |
| `tump::is_invocable` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::is_invocable_r` | 1 つ以上の可変長引数。デフォルトは 3。 |
| `tump::is_nothrow_invocable` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::is_nothrow_invocable_r` | 1 つ以上の可変長引数。デフォルトは 3。 |
| `tump::type_identity` | 1 |
| `tump::remove_cvref` | 1 |
| `tump::decay` | 1 |
| `tump::common_type` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::common_reference` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::underlying_type` | 1 |
| `tump::invoke_result` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::unwrap_reference` | 1 |
| `tump::unwrap_ref_decay` | 1 |
| `tump::conjunction` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::disjunction` | 1 つ以上の可変長引数。デフォルトは 2。 |
| `tump::negation` | 1 |

## 関連リンク

- [{`tump::eval`|ref/expression/exp}]
