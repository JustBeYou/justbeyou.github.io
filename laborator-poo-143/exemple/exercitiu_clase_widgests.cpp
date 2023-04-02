#include <iostream>
#include <string>
#include <vector>

class Drawable
{
public:
    virtual void draw() const = 0;
};

class Button : public Drawable
{
public:
    using onClickHandler = void();
    Button(std::string _text, onClickHandler *_onClick) : text(_text), onClick(_onClick) {}

    virtual void click()
    {
        if (onClick == nullptr)
            return;

        onClick();
    }

    virtual void draw() const override
    {
        for (int i = 0; i < text.size() + 4; i++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
        std::cout << "* " << text << " *" << std::endl;
        for (int i = 0; i < text.size() + 4; i++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

protected:
    std::string text;

private:
    onClickHandler *onClick;
};

class CheckBox : public Button
{
public:
    CheckBox(std::string _text, onClickHandler *_onClick) : Button(_text, _onClick), checked(false) {}

    void click() override
    {
        checked = !checked;
        Button::click();
    }

    void draw() const override
    {
        for (int i = 0; i < text.size() + 1; i++)
        {
            std::cout << " ";
        }
        std::cout << " ---" << std::endl;
        std::cout << text << " | ";
        if (checked)
        {
            std::cout << "X";
        }
        else
        {
            std::cout << " ";
        }
        std::cout << " |" << std::endl;
        for (int i = 0; i < text.size() + 1; i++)
        {
            std::cout << " ";
        }
        std::cout << " ---" << std::endl;
    }

private:
    bool checked;
};

class List : public Drawable
{
public:
    List(std::vector<std::string> _items) : items(_items) {}

    void draw() const override
    {
        for (auto item : items)
        {
            std::cout << "* " << item << std::endl;
        }
    }

private:
    std::vector<std::string> items;
};

void aButtonWasClicked()
{
    std::cout << "Wow! You clicked a button!" << std::endl;
}

int main()
{
    Button helloButton("Click me", aButtonWasClicked);
    helloButton.draw();
    helloButton.click();

    CheckBox myCheckBox("Check me", aButtonWasClicked);
    myCheckBox.draw();
    myCheckBox.click();
    myCheckBox.draw();
    myCheckBox.click();
    myCheckBox.draw();

    Button *buttons[] = {&helloButton, &myCheckBox};
    for (auto button : buttons)
    {
        button->draw();
    }

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

    return 0;
}