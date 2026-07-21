#include <type_traits>

template <class T>
struct is_floating_point
    : std::bool_constant<
          std::is_same_v<float, typename std::remove_cv<T>::type> ||
          std::is_same_v<double, typename std::remove_cv<T>::type> ||
          std::is_same_v<long double, typename std::remove_cv<T>::type>> {};

template <typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;
