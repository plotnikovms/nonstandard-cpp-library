#include <iostream>

#include "is_same_many.hpp"
#include "print.hpp"
#include "is_prime.hpp"

int main() {
  std::cout << is_same_many<int, int, int, double>::value << "\n";

  print(3, "324234", 342.4234, 3.0f);

  std::cout << is_prime<115249>::value;
}
