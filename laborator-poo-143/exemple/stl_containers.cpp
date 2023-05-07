#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>

// Clasa necesara pentru exemplul 8. Ignora pentru moment
class MyClass {
    public:
        MyClass(int x): x(x) {}

        bool operator<(const MyClass& rightHandSide) const {
            return x < rightHandSide.x;
        }

        bool operator>(const MyClass& rightHandSide) const {
            return x > rightHandSide.x;
        }

        int getX() const {
            return x;
        }

    private:
        int x;
};

bool comparatorMyClass(const MyClass& leftHandSide, const MyClass& rightHandSide) {
    return leftHandSide.getX() < rightHandSide.getX();
}

int main() {
    /**
     * Scurt ghid pentru containerele din STL
     * STL = Standard Template Library
     * STL = structuri de date generice (cu sabloane/templates) pre-implementate pe care le
     * puteti folosi comod fara alocari dinamice.
     */

    // 1. std::string in loc de char*
    // https://en.cppreference.com/w/cpp/string/basic_string
    // Foarte similare cu string-urile din Python atunci cand le folositi
    
    std::string s("acesta este un sir de caractere");
    s += "care permite concatenarea cu operatorul +";
    std::cout << "si accesul cu operatorul []: " << s[3] << std::endl;

    auto position = s.find("este");
    std::cout << "cautarea in string se face cu metoda find(): " << position << std::endl;

    // 2. std::pair din header-ul <utility>
    // https://en.cppreference.com/w/cpp/utility/pair
    // Un fel de tuple din Python, dar doar cu 2 elemente

    std::pair<int, std::string> perecheaMea(0, "Ionica");
    std::cout << "primul element: " << perecheaMea.first 
        << " al doilea element: " << perecheaMea.second << std::endl;

    auto oAltaPereche = std::make_pair<unsigned int, char>(6, 'b');
    // Tip-urile pentru template (ce este intre <>) se pot omite atunci cand compilatorul le poate deduce
    auto altaPereche = std::make_pair(5, "Traian");

    // 3. std::tuple este similar unui tuple din Python
    // https://en.cppreference.com/w/cpp/utility/tuple
    std::tuple<int, char, float> unTuplu(1, 'c', 2.5);

    std::cout << std::get<0>(unTuplu) << " " << std::get<2>(unTuplu) << std::endl;

    // 4. std::vector este un array dinamic pentru care nu trebuie sa alocati voi dinamic manual
    // https://en.cppreference.com/w/cpp/container/vector

    std::vector<int> v;
    for (int i = 0; i < 5; i++) {
        // Puteti adauga elemente la finlaul vectorului, se va redimensiona automat
        v.push_back(i);
    }

    std::vector<int> altVector(5);
    for (int i = 0; i < 5; i++) {
        // Sau puteti sa il prealocati
        altVector[i] = i;
    }
    // Adaugarea este permisa si daca prealocati
    altVector.push_back(1337);

    // 5. std::set este ca set() din Python, tine doar elemente unice
    // https://en.cppreference.com/w/cpp/container/set

    std::set<int> mySet;
    mySet.insert(3);
    mySet.insert(3);
    mySet.insert(4);
    mySet.erase(4);

    // Observatie: iterarea prin containerele STL se face prin intermediul iteratorilor
    // si se comporta similar pentru toate containerele
    // https://en.cppreference.com/w/cpp/iterator
    for (const auto& elem: mySet) {
        std::cout << elem << std::endl;
    }

    // 6. std::map este similar cu un dictionar din Python, tine chei si valori
    // https://en.cppreference.com/w/cpp/container/map

    std::map<char, unsigned int> frecventa;
    std::string myString("aaabbccdddd");

    for (const auto& caracter: myString) {
        // Elementele care nu exista se vor initializa cu 0
        frecventa[caracter]++;
    }

    // Iterarea peste std::map va returna un std::pair care contine cheia si valoarea
    for (const auto& cheieSiValoare: frecventa) {
        std::cout << cheieSiValoare.first << " " << cheieSiValoare.second << std::endl;
    }

    // In general, std::orice_container.end() este un iterator in afara containerului
    // (va puteti imagina fiind pozitia n intr-un vector de la 0 la n-1)
    // Acest iterator este folosit pentru a semnala valorile care nu exista atunci cand
    // folosim metodele de cautare ale containerelor din STL

    if (frecventa.find('e') == frecventa.end()) {
        std::cout << "caracterul 'e' nu exista in map" << std::endl;
    }

    // 7. std::sort din <algorithm> ne poate ajuta sa ordonam elemente
    // Este similar cu .sort() sau sorted() din Python
    // https://en.cppreference.com/w/cpp/algorithm/sort

    std::vector<int> mySortedVector{4, 3, 2, 6, 8, 5};
    // Comportamentul de baza este sa sorteze crescator
    std::sort(mySortedVector.begin(), mySortedVector.end());

    // Se poate altera printr-un parametru aditional, less<> sau greater<> din <functionl>
    std::sort(mySortedVector.begin(), mySortedVector.end(), std::greater<>());

    // Sort se poate apela si pentru array-uri clasice C-style
    int myArray[] = {4, 3, 2, 6, 8, 5};
    std::sort(myArray, myArray + 6);

    // 8. Containere si std::sort pentru clase si structuri
    // Clasele si structurile pot fi puse in containere precum std::vector sau std::list
    // fara a indeplini vreo conditie. Pentru containere cu proprietati speciale precum 
    // std::set sau std::map, ele trebuie sa aiba implementat operatorul < (lower than).
    // Acelasi operator trebuie sa fie implementat pentru a folosi std::sort cu std::lower,
    // iar pentru sort cu std::greater se va implementa operatorul >.

    std::set<MyClass> myClassSet;
    myClassSet.insert(MyClass(5));

    std::vector<MyClass> myClassSetVector{MyClass(2), MyClass(3), MyClass(4)};
    std::sort(myClassSetVector.begin(), myClassSetVector.end(), std::greater<>());

    // O alta metoda de a folosi std::sort cu o clasa sau structura este trimitand
    // o functie de comparare ca al treilea argument (poate fi si o lambda expresie)

    std::sort(myClassSetVector.begin(), myClassSetVector.end(), comparatorMyClass);

    std::sort(myClassSetVector.begin(), myClassSetVector.end(), [](const MyClass& leftHandSide, const MyClass& rightHandSide) {
        return leftHandSide.getX() < rightHandSide.getX();
    });

    return 0;
}