int main()
{
    int x = 5;

    const int &cir = x;
    int const &icr = x;
    // invalid:
    // int &const irc = x;
    // const int &const circ = x;
    // int const &const icrc = x;

    // Referintele nu sunt la fel de complicate ca pointerii,
    // const int& e suficient ca valoarea la care se face referinta sa NU
    // poata fi schimbata. Variabila la care se face referinta NU se poate
    // schimba nici in cazul unui int& simplu.

    // cir = 1;  -- expression must be a modifiable lvalue
    // icr = 1;  -- expression must be a modifiable lvalue

    // Pointeri vs referinte:
    // https://stackoverflow.com/questions/2336230/difference-between-const-pointer-and-reference
    // https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable/57492#57492
}
