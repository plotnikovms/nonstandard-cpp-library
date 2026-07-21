#include <type_traits>

template <typename T>
struct is_null_pointer : std::is_same<std::nullptr_t, std::remove_cv_t<T>> {};

template <typename T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
