#include <type_traits>


template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T>
constexpr bool is_same_v = is_same<T>::value;