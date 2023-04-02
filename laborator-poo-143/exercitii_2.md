Exercitii mosteniri, polimorfism si interfete
===

## A. Introducere

In exercitiile urmatoare vom folosi exemple insiprate de [elementele din interfetele grafice](https://en.wikipedia.org/wiki/Graphical_widget#List_of_common_generic_widgets), deoarece in general acestea sunt modelate folosind POO. Vom creea cateva obiecte care sa mimeze functionalitatea unor
elemente grafice si vom creea o ierarhie simpla de mosteniri si implementari de interfete
care sa modeleze corespunzator problema.

### 1. Implementare clasa de baza

Implementati o clasa `Button` care are urmatoarea declaratie:
```cpp
class Button
{
public:
    // Tip de date asociat unei functii care nu returneaza nimic.
    // Vezi mai multe pe https://en.cppreference.com/w/cpp/language/pointer : Pointers to functions
    using onClickHandler = void();

    /**
     * Un buton este format dintr-un text ce trebuie afisat si o actiune
     * ce va fi executata atunci cand butonul este apasat. 
     */
    Button(std::string _text, onClickHandler *_onClick);

    /**
     * Atunci cand click() este apelata, se va executa actiunea onClick().
     */
    void click();

    /**
     * Se va afisa pe ecran butonul impreuna cu textul sau.
     */
    void draw() const;

// TODO: adaugati membrii necesari
};

Dupa implementare, urmatoarea bucata de cod ar trebui sa ruleze fara erori:
```cpp
void aButtonWasClicked()
{
    std::cout << "Wow! You clicked a button!" << std::endl;
}

int main() {
    Button myButton("Click me!", aButtonWasClicked);
    myButton.draw();
    myButton.click();

    return 0;
}
```

Un output posibil este urmatorul:
```
************
* Click me *
************
Wow! You clicked a button!
```

### 2. Implementare clasa derivata

Un **check box** este un tip special de buton care are doua stari: bifat si ne-bifat.
Implementati o clasa derivata din clasa `Button` care sa suprascrie afisarea
si sa permita retinerea celor doua stari.

**Obs.** Pentru metoda `click()` nu reimplementati logica de apelare a lui `onClick()`, ci
refolositi-o apeland metoda din clasa de baza astfel: `Button::click()`.

Urmatoarea bucata de cod ar trebui sa poata fi executata fara erori:

```cpp
class CheckBox : public Button {
    // TODO: codul vostru aici

    void click() {
        // apelam metoda din clasa de baza pentru a reutiliza logica
        Button::click();
        // ... logica voastra ...
    }
}

// ...

int main() {
    CheckBox myCheckBox("Check me", aButtonWasClicked);
    myCheckBox.draw();
    myCheckBox.click();
    myCheckBox.draw();

    return 0;
}
```

Un posibil output este urmatorul (observati schimbarea de stare a check box-ului la a doua afisare):
```
          ---
Check me |   |
          ---
Wow! You clicked a button!
          ---
Check me | X |
          ---
```

### 3. Polimorfism: Override si virtual

Deoarece `CheckBox` este o clasa derivata a `Button`, putem stoca un pointer de tip
`CheckBox*` intr-un pointer de tip `Button*`. Executati urmatoarea bucata de cod care
ilustreaza acest lucru:
```cpp
// ...
int main() {
    Button *myButtons[] = {
        new Button("Click me!", aButtonWasClicked),
        new CheckBox("Check me", aButtonWasClicked)
    }

    for (auto myButton: myButtons) {
        myButton->draw();
    }

    return 0;
}
```

**Obs.** De ce ambele apeluri la metoda `->draw()` afiseaza output-ul corespunzator clasei de baza?

Modificati clasa `CheckBox` astfel incat sa foloseasca keyword-ul `override` pentru metodele
pe care le suprascrie din clasa parinte, adica:
 ```cpp
class CheckBox : public Button {
    // ...
    void click() override { /* codul vostru */ }
    void draw() const override { /* codul vostru */ }
}
```

**Obs.** Codul nu mai compileaza, de ce? Daca adaugam keyword-ul `virtual` la definirea functiilor
in clasa de baza, codul compileaza din nou. De ce e nevoie de keyword-ul virtual?

```cpp
class Button
{
public:
    // ...
    virtual void click() { /* ... */ }
    virtual void draw() const { /* ... */ }
};
```

Rulati din nou codul de la inceputul acestui exercitiu (3). Observati ca acum codul afiseaza
output-ul asteptat.

### 4. Interfete (clase pur abstracte)

Implementati inca o clasa numita `List` care va stoca si desena o lista
de texte si care are urmatoarea definitie:
```cpp
class List
{
public:
    List(std::vector<std::string> _items);
    void draw() const;
}
```

Un exemplu de utilizare al clasei:
```cpp
List myList = List({"milk", "eggs", "a coffin"});
myList->draw();
```

Poate avea urmatorul output:
```
* milk
* eggs
* a coffin
```

**Obs.** Atat `Button`, `CheckBox` cat si `List` definesc o metoda `draw()`. Pentru a profita de 
polimorfism si comportamentul lor comun, putem folosi interfetele.

Definiti urmatoarea interfata si apoi modificati toate clasele definite astfel incat sa o implementeze:
```cpp
class Drawable
{
public:
    virtual void draw() const = 0;
};
```

Dupa modificarea codului, urmatoarea bucata de cod ar trebui sa poata fi rulata fara erori:
```cpp
Drawable *toDraw[] = {
    new Button("Click me", aButtonWasClicked),
    new CheckBox("Check me", aButtonWasClicked),
    new List({"milk", "eggs", "a coffin"})};
for (auto element : toDraw)
{
    element->draw();
}

for (auto element : toDraw)
{
    delete element;
}
```

### Sumar

Dupa exercitiile de mai sus, urmatoarele concepte ar trebui sa intelegi urmatoarele concepete:

* mostenirea poate ajuta sa nu duplicam logica/cod (exemplul cu reutilizarea `Button::click`)
* mostenirea ne poate ajuta sa folosim polimorfismul la executie (apelam o metoda derivata printr-un pointer la clasa de baza)
* pentru polimorfismul la executie trebuie sa folosim keyword-ul `virtual` pentru a face compilatorul
sa intelega ca avem nevoie de acest comportament
* cand avem clase care au similaritati de comportament, dar nu impart aceasi logica, putem folosi
interfete (clase pur abstracte)
* interfetele ajuta la "decuplarea" utilizarii unei clase de implementarea ei concreta (orice `Drawable` va fi folosit la fel, indiferent de implementarea sa)

Daca exista neclaritati, pune-mi o **intrebare** :)

## B. ??? (work in progress)

### 1. Destructor virtual

### 2. Mostenirea multipla si virtuala

### 3. Compunere in locul mostenirii (composition over inheritance)

### 4. Runtime type information (RTTI)