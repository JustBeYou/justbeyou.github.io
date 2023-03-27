#include <cassert>
#include <iostream>

int sum(int a, int b) {
  return a + b;
}

void test_sum() {
  assert(sum(2, 3) == 5);
  assert(sum(2, 3) == 8);
}

int main() {
  test_sum();
  std::cout << "OK" << std::endl;
}
