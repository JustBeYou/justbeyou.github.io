Exercitii mosteniri, compunere, polimorfism si interfete
===

## 1. Implementare naiva

Implementati doua clase `Rectangle(width, height)` si `Waves(width, heigh)` care vor avea urmatoarele metode:
```cpp
    void scale(uint numerator, uint denominator);
    std::string compute() const;
    std::string computeStrips() const;
    void draw(bool strips = false) const;
``` 

Metoda `scale()` va redimensiona lungimea si latimea obiectului. Veti lucra doar cu numere
intregi pentru simplitate. Metoda `compute()` va returna un string specific fiecarei clase,
dupa cum urmeaza:
```
Pentru rectangle de 3x4:
****
****
****

Pentru waves de 4x3 (4 valuri de nivel maxim 3):
*
**
***
*
**
***
*
**
***
*
**
***
```

Metoda `computeStrips` se va folosi de valoarea returnata de `compute()` si va inlocui
fiecare caracter `*` par (numarand de la 1) cu un spatiu alb. Exemplu pentru rectangle:
```
* * 
* * 
* * 
```

Metoda `draw()` va afisa pe ecran rezultatul lui `compute()` sau `computeStrips()`.
Exemplu de utilizare:
```cpp
    Rectangle r(4, 8);
    r.draw();
    r.draw(true);

    Waves w(2, 3);
    w.draw();
    w.draw(true);
```

**Intrebare:** cum ati putea reduce codul duplicat intre Rectangle si Waves? Cum ati putea
stoca obiecte de ambele tipuri intr-un singur array?

## 2. Polimorfism cu mostenire din clasa parinte

Implementati o clasa `Shape` care sa contina codul duplicat intre `Rectangle` si `Waves`.
Transformati clasele astfel incat sa mosteneasca clasa `Shape` si sa spurascrie doar
metoda specifica fiecareia, anume `compute()`. Implementarea voastra ar trebui sa 
permita urmatorului cod sa ruleze fara erori:
```cpp
    Shape *shapes[] = {new Rectangle(2, 3), new Waves(3, 3)};
    for (Shape *shape : shapes)
    {
        shape->draw();
    }
```

## 3. Mostenire dificila

Implementati o noua clasa numita `HallowTriangle(height)` care sa afiseze conturul
unui triunghi, astfel:
```
*
**
* *
*  *
*   *
******
```

Urmatorul cod ar trebui sa poata fi executat fara erori:
```cpp
    Shape *shapes[] = {new Rectangle(2, 3), new Waves(3, 3), new HallowTriangle(6)};
    for (auto shape : shapes)
    {
        shape->draw();
    }
```

**Intrebare:** Ce observati referitor la membrul `width`? Pare ca `HallowTriangle: Shape` 
este o mostenire potrivita?

## 4. Problema diamantului

Incercati sa implementati o clasa numita `RectangleWaves` care sa calculeze corpul
unui dreptunghi urmat de "valuri". Incercati sa refolositi codul din clasele existente
mostenind `Rectangle` si `Waves`.

**Intrebare:** Ce observati? Cum credeti ca ati putea rezolva problema diamantului?

## 5. Interfete

Vom inlocui mostenirea unei clase parinte cu polimorfismul bazat pe implementarea
interfetelor. Transformati clasele care inainte mosteneau `Shape` in asa fel incat
sa implementeze doar urmatoarele doua interfete (renuntati la restul codului):

```cpp
    class ComputableShape
    {
    public:
        virtual std::string compute() const = 0;
    };

    class ScalableShape
    {
    public:
        virtual void scale(uint numerator, uint denominator) = 0;
    };
```

## 6. Compozitie

Considerand urmatoarea interfata:

```cpp
    class Drawable
    {
    public:
        virtual void draw() const = 0;
    };
```

Implementati o clasa `ShapeDrawer(ComputableShape* shape)` care sa implementeze interfata si care sa permita
desenarea claselor care implementeaza `ComputableShape`. Codul urmator ar trebui sa poata fi
executat fara erori:
```cpp
    Drawable *toDraw[] = {
        new ShapeDrawer(new Rectangle(2, 3)),
        new ShapeDrawer(new Waves(4, 3))};

    for (auto drawable : toDraw)
    {
        drawable->draw();
    }
```

## 7. Rezolvarea diamantului prin compozitie

Incercati din nou sa implementati `RectangleWaves` folosind compozitia de clase si fara
a duplica implementarea `Rectangle` sau `Waves`.

**Discussion time**:
* avantaje/dezavantaje mostenire
* avantaje/dezavantaje interfete
* de ce e bun polimorfismul?
* de ce am vrea sa folosim interfete?
* opinii personale?