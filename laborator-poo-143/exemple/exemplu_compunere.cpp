#include <iostream>
#include <vector>

/**
 * Exemplu de compunere 1
 * 
 * Clasa Companie are ca membru un vector (array) de obiecte Angajat.
 */
class Angajat {};

class Companie {
    public:
        Companie() {}
        
    private:
        std::vector<Angajat> angajati;
};

/**
 * Exemplu de compunere 2
 * 
 * Clasa Masina are ca membri doua obiecte de tip Caroserie si Motor.
 * Obiectele sunt primite prin constructor.
 * 
 */
class Caroserie {};
class Motor {};

class Masina {
    public:
        Masina(Caroserie caroserie, Motor motor) {
            this->caroserie = caroserie;
            this->motor = motor;
        }
        
    private:
        Caroserie caroserie;
        Motor motor;
};

int main()
{
    Caroserie caroserie;
    Motor motor;
    Masina masina(caroserie, motor);
    
    Companie companie;

    return 0;
}
