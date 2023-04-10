#include <iostream>

using namespace std;

class Product {
private:
  float price;

public:
  Product(float price) : price(price) {}

  virtual 

float computePrice() { return price; }
};

class ProductWithDiscount : public Product {
private:
  float discount;

public:
  ProductWithDiscount(float price, float discount)
      : Product(price), discount(discount) {}

  float computePrice() override { return Product::computePrice() * discount; }
};

int main() { 
  ProductWithDiscount p(10, 2);
  cout << p.computePrice() << endl;

  Product *p2 = &p;
  cout << p2->computePrice() << endl;
}
