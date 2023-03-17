#include <cassert>
#include <iostream>

bool is_odd(int x) {
  return x % 2 == 1;
}

void test_is_odd() {
  // https://en.cppreference.com/w/cpp/error/assert
  assert(is_odd(5));
  assert(is_odd(4) == false);
  // assert(is_odd(2));
}

int sum(int a, int b) {
  return a + b;
}

double sum(double a, double b) {
  return a + b;
}

int main() {
  test_is_odd();

  assert(sum(2, 3) == 5);
  assert(sum(1.5, 2.5) == 4.0);
  
  std::cout << "OK" << std::endl;
}
