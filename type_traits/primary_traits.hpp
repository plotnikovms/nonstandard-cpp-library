#include <type_traits>

template <typename T>
struct is_void : std::is_same<void, std::remove_cv_t<T>> {};

template <typename T>
struct is_null_pointer : std::is_same<std::nullptr_t, std::remove_cv_t<T>> {};

template <typename T>
struct is_integral : std::bool_constant <
  requires(T t, T* p, void (*f)(T)) {
    reinterpret_cast<T>(t);
    f(0);
    p + t;
  } > {};

template <class T>
struct is_floating_point
    : std::bool_constant<
          std::is_same_v<float, typename std::remove_cv<T>::type> ||
          std::is_same_v<double, typename std::remove_cv<T>::type> ||
          std::is_same_v<long double, typename std::remove_cv<T>::type>> {};

template <typename T>
struct is_array : std::false_type {};

template <typename T>
struct is_array<T[]> : std::true_type {};

template <typename T, size_t N>
struct is_array<T[N]> : std::true_type {};



template <typename T>
constexpr bool is_void_v = is_void<T>::value;

template <typename T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template <typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;

template <typename T>
constexpr bool is_array_v = is_array<T>::value;
