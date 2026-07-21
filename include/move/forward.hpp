#include <type_traits>

template <typename T>
T&& forward(std::remove_reference_t<T>& value) {
  return static_cast<T&&>(value);
}

template <typename T>
T&& forward(std::remove_reference_t<T>&& value) {
  static_assert(!std::is_lvalue_reference_v<T>);
  return static_cast<T&&>(value);
}
