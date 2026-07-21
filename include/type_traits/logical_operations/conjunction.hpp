#include <type_traits>

template <typename... Types>
struct conjunction : std::bool_constant<(Types::value && ...)> {};

template <typename... Types>
constexpr bool conjunction_v = conjunction<Types...>::value;
