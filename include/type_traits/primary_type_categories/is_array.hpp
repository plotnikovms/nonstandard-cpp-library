#include <type_traits>

template <typename T>
struct is_array : std::false_type {};

template <typename T>
struct is_array<T[]> : std::true_type {};

template <typename T, size_t N>
struct is_array<T[N]> : std::true_type {};

template <typename T>
constexpr bool is_array_v = is_array<T>::value;