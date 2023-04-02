Exercitii mosteniri, compunere, polimorfism si interfete
===

In exercitiile urmatoare vom folosi exemple insiprate de [elementele din interfetele grafice](https://en.wikipedia.org/wiki/Graphical_widget#List_of_common_generic_widgets), deoarece in general acestea sunt modelate folosind POO.

## Mosteniri si interfete

### Implementare clasa de baza

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

### Implementare clasa derivata

Un **check box** este un tip special de buton care are doua stari: bifat si ne-bifat.
Implementati o clasa derivata din clasa `Button` care sa suprascrie afisarea
si sa permita retinerea celor doua stari.

Urmatoarea bucata de cod ar trebui sa poata fi executat fara erori:

```cpp
class CheckBox : public Button {
    // TODO: codul vostru aici
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