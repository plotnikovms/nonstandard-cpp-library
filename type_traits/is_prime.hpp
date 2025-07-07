#include <type_traits>

template <int N, int K, bool larger_then_square = (K * K >= N)>
struct helper {
  static constexpr bool value =  (N % K != 0) && helper<N, K + 1>::value;
};

template <int N, int K>
struct helper<N, K, true> {
  static constexpr bool value = true;
};

template <int N>
struct is_prime {
  static constexpr bool value = helper<N, 2>::value;
};
