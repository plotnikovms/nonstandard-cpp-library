#include <iostream>

#include "../../containers/vector.hpp"

int main() {
  Vector<int> v1;
  Vector<int> v2(5, 121);

  for (size_t i = 0; i < v2.size(); ++i) {
    std::cout << v2[i] << " ";
  }
}
