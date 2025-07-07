#include <iostream>

template <typename Head>
void print(Head head) {
  std::cout << head << "\n";
}

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
  std::cout << head << " ";
  print(tail...);
}
