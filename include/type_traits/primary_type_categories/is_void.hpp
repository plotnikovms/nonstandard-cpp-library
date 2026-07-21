#include <type_traits>

template <typename T>
struct is_void : std::is_same<void, std::remove_cv_t<T>> {};

template <typename T>
constexpr bool is_void_v = is_void<T>::value;