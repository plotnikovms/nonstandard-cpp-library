#include <iostream>

#include "../../type_traits/primary_traits.hpp"

int main() {
  std::cout << is_void_v<const void> << "\n";
  std::cout << is_void_v<int> << "\n";

  std::cout << is_integral_v<float> << "\n";
  float a = 1.0;
  int b = 1;
  int c = reinterpret_cast<int>(b);
}
