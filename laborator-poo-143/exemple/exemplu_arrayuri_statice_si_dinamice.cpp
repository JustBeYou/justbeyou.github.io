#include <iostream>

using namespace std;

void exemplu_array_static() {
    const int n = 100;

    // array (aka vector) alocat static, pe stiva (stack, memorie in care se aloca punand 
    // variabilele unele dupa altele, memorie managed "de procesor" prin instructiuni de push/pop si
    // modificarea registrului spre capul stivei (esp/rsp). posibil sa se fi discutat la ASC in detaliu despre
    // ce e si cum merge stiva)
    
    // array-ul asta nu poate fi eliberat manual si nici transmis in exteriorul functiei,
    // adica "return arr;" nu e corect (compileaza, dar va cauza probleme)
    int arr[n];

    // sintaxa de accesare a valorilor e cea cu []
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }
}

void exemplu_array_dinamic() {
    int n;
    cin >> n;

    // array-ul asta e alocat dinamic, pe heap (nu stiu traducerea in romana, regiune de memorie
    // unde variabilele nu trebuie sa fie neaparat continue, managed de sistemul de operare)
    int* arr = new int[n];

    // sintaxa de accesare e identica, int* si int[] sunt in general doua tipuri echivalente din cate imi amintesc
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }

    // array-ul poate fi sters manual, la cerere
    // IMPORTANT: e obligatoriu sa pui [] la delete daca stergi un array!
    delete[] arr;

    // memoria alocata dinamica nu e eliberata cand se termina functia, poate fi folosita
    // mai departe, deci "return arr" ar fi un lucru valid de facut (dar nu daca i-ai dat delete deja :P)

    // IMPORTANT: daca ai alocat memorie cu new sau new[], e frumos sa o stergi cand nu mai
    // ai nevoie de ea cu delete/delete[]. (daca ai alocat in constructor, dai delete in destructor)
}

void exemplu_array_dinamic_pe_stica() {
    int n;
    cin >> n;

    // in ultimele versiuni de C++ (nu mai stiu de la ce standard in sus), ai voie sa aloci
    // dinamic pe stiva, DAR tot nu poti elibera memoria manual sau sa transmiti array-ul in exeriorul functiei
    // prin return sau parametri
    int arr[n];
}

int main() {
    return 0;
}
