#include <iostream>
#include <string>

/* exemplu namespace-uri */

namespace laborator {
class string {};
} // namespace laborator

namespace laborator {
class vector {};
} // namespace laborator

using namespace std;
// using namespace laborator;

void exemplu_namespaceuri() {
  std::string a;
  string b;
  std::cout << "salut" << std::endl;
}

/* exemplu interschimbare */
void interschimbare(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
  std::cout << "[dupa interschimbare in functie] " << (*a) << " " << (*b)
            << std::endl;
}

void exemplu_interschimbare() {
  int a = 2, b = 3;
  std::cout << "[inainte de interschimbare] " << a << " " << b << std::endl;
  interschimbare(&a, &b);
  std::cout << "[dupa interschimbare] " << a << " " << b << std::endl;
}

/* alocare dinamica */
class MyFile {};

void exemplu_alocare_dinamica() {
  MyFile *f = new MyFile;

  std::cout << f << std::endl;

  delete f;
  f = nullptr;

  int a = 5;
  int *p = &a;
  int **q = &p;

  cout << &a << " " << a << endl;
  cout << &p << " " << p << " " << *p << endl;
  cout << &q << " " << q << " " << *q << " " << **q << endl;
}

int main() {
  std::cout << "Lab 2 - exemple pointeri" << std::endl;

  exemplu_interschimbare();
  exemplu_alocare_dinamica();

  return 0;
}
