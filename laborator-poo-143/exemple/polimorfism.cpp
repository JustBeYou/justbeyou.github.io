#include <iostream>

class Eater {
    public:
        virtual void eat() const = 0;
};

class Dog: public Eater {
    public:
        void eat() const override {
            std::cout << "Bark, bark, I like to eat bones!" << std::endl;
        }
};

class Cat: public Eater {
    public:
        void eat() const override {
            std::cout << "Meow, meow, I like to eat fish!" << std::endl;
        }
};

void eat_something(const Eater& eater) {
    eater.eat();
}

int main() {
    Dog d;
    Cat c;

    eat_something(d);
    eat_something(c);

    return 0;
}
