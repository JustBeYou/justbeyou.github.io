#include <iostream>
#include <exception>
#include <utility>

// regula cea sfanta: https://en.cppreference.com/w/cpp/language/rule_of_three
// copy vs assignment: https://stackoverflow.com/questions/11706040/whats-the-difference-between-assignment-operator-and-copy-constructor
// move semantics in reference: https://en.cppreference.com/w/cpp/utility/move
// when is move used: https://stackoverflow.com/questions/13125632/when-does-move-constructor-get-called

class MyClass
{
public:
    MyClass()
    {
        std::cout << "MyClass() NO params constructor" << std::endl;

        myResource = new int;
        *myResource = 0;
    }

    MyClass(int resource)
    {
        std::cout << "MyClass() params constructor" << std::endl;

        myResource = new int;
        *myResource = resource;
    }

    /* === Rule of three === */
    // Daca avem nevoie de destructor custom, copy-constructor sau operator=
    // Atunci avem sigur nevoie de toate 3
    MyClass(const MyClass &lvalue)
    {
        std::cout << "MyClass() copy constructor" << std::endl;

        if (lvalue.myResource == nullptr)
        {
            throw new std::runtime_error("Cannot copy from a NULL object");
        }

        // copiem doar valoarea, nu adresa, intr-o resursa nou alocata
        // pentru ca in copy-constructor obiectul nu e inca intializat
        myResource = new int;
        *myResource = *lvalue.myResource;
    }

    MyClass &operator=(const MyClass &lvalue)
    {
        std::cout << "MyClass() assignment operator" << std::endl;

        if (lvalue.myResource == nullptr)
        {
            throw new std::runtime_error("Cannot assign from a NULL object");
        }

        // obiectul e deja initializat, copiem doar valoarea
        *myResource = *lvalue.myResource;
        return *this;
    }

    ~MyClass()
    {
        if (myResource == nullptr)
            return;
        delete myResource;
        // myResource = nullptr; OBS: nu e necesar, obiectul nu va mai exista oricum
    }

    friend std::ostream &operator<<(std::ostream &out, const MyClass &lvalue);

    // BONUS: move semnatics, constructor de mutare

    MyClass(MyClass &&rvalue)
    {
        // OBS: obiectul primit ca argument nu mai e const

        std::cout << "MyClass() move constructor" << std::endl;

        if (rvalue.myResource == nullptr)
        {
            throw new std::runtime_error("Cannot move from a NULL object");
        }

        if (myResource != nullptr)
        {
            std::cout << "MyClass() destruct before move" << std::endl;
            delete myResource;
        }

        // de data asta copiem pointerul, nu valoarea, apoi "distrugem" obiectul mutat
        myResource = rvalue.myResource;
        rvalue.myResource = nullptr;
    }

private:
    int *myResource = nullptr;
};

std::ostream &operator<<(std::ostream &out, const MyClass &lvalue)
{
    if (lvalue.myResource == nullptr)
    {
        out << "NULL";
        return out;
    }

    out << lvalue.myResource << " " << *lvalue.myResource;
    return out;
}

int main()
{
    std::cout << "=== A ===" << std::endl;
    MyClass A;
    std::cout << A << std::endl;
    std::cout << "=== B ===" << std::endl;
    MyClass B(1);
    std::cout << B << std::endl;
    std::cout << "=== C ===" << std::endl;
    MyClass C[2];
    std::cout << C[0] << std::endl;
    std::cout << "=== D ===" << std::endl;
    MyClass D(B);
    std::cout << D << std::endl;
    std::cout << "=== D = A ===" << std::endl;
    D = A;
    std::cout << D << std::endl;
    std::cout << "=== E ===" << std::endl;
    MyClass E(2);
    std::cout << E << std::endl;
    std::cout << "=== F = move E ===" << std::endl;
    MyClass F(std::move(E));
    std::cout << F << std::endl;

    return 0;
}