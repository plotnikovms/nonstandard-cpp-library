#include <iostream>
#include "swap.hpp"

int main() {
  {
    int x = 5;
    int y = 7;
    swap(x, y);
    std::cout << x << " " << y <<"\n"; 
  }
}