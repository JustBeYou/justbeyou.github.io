#include <iostream>

int main()
{
    int x = 5;

    const int *cip = &x;
    int const *icp = &x;
    int *const ipc = &x;
    const int *const cipc = &x;
    int const *const icpc = &x;

    // *cip = 5;    -- expression must be a modifiable lvalue
    // *icp = 5;    -- expression must be a modifiable lvalue
    // const int * si int const * sunt echivalente si
    // ambele desemneaza un pointer spre o valoare constanta

    // pointerul NU este constant, locul in care pointeaza poate fi schimbat
    cip = reinterpret_cast<const int *>(0xdeadbeef);
    icp = reinterpret_cast<const int *>(0xdeadbeef);

    // *cip va provoca segmentation fault pe linia asta, adresa din pointer nu e valida

    // De ce reinterpret_cast<> ?
    // reinterpret_cast permite orice fel de cast fara compile-time checks/
    // static_cast in acelasi caz nu functioneaza. explicatii:
    // https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used

    *ipc = 5;
    // ipc = reinterpret_cast<const int *>(0xdeadbeef);     -- expression must be a modifiable lvalue
    // int *const desemneaza un pointer constant, valoarea se poate modifica, dar adresa pointerului NU

    // cipc = reinterpret_cast<const int *>(0xdeadbeef);     -- expression must be a modifiable lvalue
    // *cipc = 5;                                            -- expression must be a modifiable lvalue
    // cipc = reinterpret_cast<const int *>(0xdeadbeef);     -- expression must be a modifiable lvalue
    // *cipc = 5;                                            -- expression must be a modifiable lvalue
    // const int *const si int const *const sunt echivalente si
    // ambele desemneaza atat un POINTER constant, cat si o VALOARE constanta

    // de obicei, const preceda tipul, deci se prefera: const int in loc de int const

    return 0;
}