#include <type_traits>


template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};



template <typename T, typename U, typename... Types>
struct is_same_many {
  static const bool value = is_same<T, U>::value && is_same_many<U, Types...>::value;
};

template <typename T, typename U>
struct is_same_many<T, U> {
  static const bool value = is_same<T, U>::value;
};