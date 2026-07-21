#include <type_traits>

namespace detail
{
  template <typename T>
  std::bool_constant<!std::is_union_v<T>> test_class(int T::*);

  template <typename T>
  std::false_type test_class(...);
}

template <typename T>
struct is_class : decltype(detail::test_class<T>(nullptr)) {};

template <typename T>
constexpr bool is_class_v = is_class<T>::value;