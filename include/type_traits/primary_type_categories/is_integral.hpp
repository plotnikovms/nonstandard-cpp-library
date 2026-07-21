#include <type_traits>

template <typename T>
struct is_integral : std::bool_constant <
  requires(T t, T* p, void (*f)(T)) {
    reinterpret_cast<T>(t);
    f(0);
    p + t;
  } > {};

template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;