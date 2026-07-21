#include "is_same.hpp"

template <typename T, typename U, typename... Types>
struct is_same_many {
  static const bool value = is_same<T, U>::value && is_same_many<U, Types...>::value;
};

template <typename T, typename U>
struct is_same_many<T, U> {
  static const bool value = is_same<T, U>::value;
};

template <typename T>
constexpr bool is_same_many_v = is_same_many<T>::value;