// https://github.com/vladfxstoader/OOP-exams/blob/master/Colocviu_POO_2021_29Mai.pdf

#include <vector>
#include <set>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <exception>

class Rootkit;

class Malware
{
public:
    virtual void read(std::istream &in) = 0;
    virtual void write(std::ostream &out) const = 0;
    virtual unsigned int computeRating() const = 0;

    static Malware *create(std::string type);

    friend std::ostream &operator<<(std::ostream &out, const Malware &malware)
    {
        malware.write(out);
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Malware &malware)
    {
        malware.read(in);
        return in;
    }
};

class Rootkit : public Malware
{
public:
    unsigned int computeRating() const override
    {
        unsigned int rating = 0;

        for (const auto &importantString : importantStrings)
        {
            if (Rootkit::dangerousImports.find(importantString) != Rootkit::dangerousStrings.end())
            {
                rating += 100;
            }
        }

        for (const auto &dllImport : dllImports)
        {
            if (Rootkit::dangerousImports.find(dllImport) != Rootkit::dangerousImports.end())
            {
                rating *= 2;
            }
        }
        return rating;
    }

    void read(std::istream &in) override
    {
        unsigned int n;
        in >> n;
        dllImports.resize(n);
        for (unsigned int i = 0; i < n; i++)
        {
            in >> dllImports[i];
        }

        in >> n;
        importantStrings.resize(n);
        for (unsigned int i = 0; i < n; i++)
        {
            in >> importantStrings[i];
        }
    }

    void write(std::ostream &out) const override
    {
        out << "Rootkit malware (rating = " << computeRating() << ")" << std::endl;
        out << "DLL imports: " << std::endl;
        for (const auto &dllImport : dllImports)
        {
            out << "- " << dllImport << std::endl;
        }
        out << "Important string: " << std::endl;
        for (const auto &importantString : importantStrings)
        {
            out << "- " << importantString << std::endl;
        }
    }

private:
    std::vector<std::string> dllImports;
    std::vector<std::string> importantStrings;

    static std::set<std::string> dangerousStrings;
    static std::set<std::string> dangerousImports;
};

std::set<std::string> Rootkit::dangerousStrings = {"SSDT", "NtCreateFile"};
std::set<std::string> Rootkit::dangerousImports = {"ntoskrnl.exe"};

Malware *Malware::create(std::string type)
{
    if (type == "Rootkit")
    {
        return new Rootkit;
    }

    throw new std::runtime_error("Unknown malware type.");
}

class Computer
{
public:
    Computer()
    {
        this->id = Computer::currentId++;
        this->rating = 0;
    };

    unsigned int getRating() const
    {
        return rating;
    }

    friend std::ostream &operator<<(std::ostream &out, const Computer &computer)
    {
        out << "Computer #" << computer.id << " (rating = " << computer.rating << ")" << std::endl;
        out << "Malware list: " << std::endl;
        for (const auto &malware : computer.malwares)
        {
            out << (*malware) << std::endl;
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Computer &computer)
    {
        unsigned int n;
        std::string malwareType;
        in >> n;
        computer.malwares.resize(n);
        for (unsigned int i = 0; i < n; i++)
        {
            in >> malwareType;
            auto newMalware = std::unique_ptr<Malware>{Malware::create(malwareType)};
            in >> *newMalware;
            computer.rating += newMalware->computeRating();
            computer.malwares[i] = std::move(newMalware);
        }
        return in;
    }

private:
    std::vector<std::unique_ptr<Malware>>
        malwares;
    unsigned int rating;
    unsigned int id;

    static unsigned int currentId;
};

unsigned int Computer::currentId = 0;

int main()
{
    std::stringstream inputs(
        "2\n"
        "1\n"
        "Rootkit 2 SSDT someString 3 ntdll system32 fakeImport\n"
        "2\n"
        "Rootkit 1 SSDT 3 ntdll system32 fakeImport\n"
        "Rootkit 1 someString 1 system32\n");

    std::vector<Computer> myComputers;
    unsigned int n = 0;

    inputs >> n;
    myComputers.resize(n);
    for (unsigned int i = 0; i < n; i++)
    {
        inputs >> myComputers[i];
    }

    sort(myComputers.begin(), myComputers.end(), [](const Computer &a, const Computer &b) -> bool
         { return a.getRating() > b.getRating(); });

    for (const auto &computer : myComputers)
    {
        std::cout << computer;
    }

    return 0;
}