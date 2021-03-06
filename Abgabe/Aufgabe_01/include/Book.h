#pragma once

#include <string>

class Shelf;
class Book {
public:
    Book(std::string isbn, std::string name, std::string author, bool lent);

    Book(std::string isbn, std::string name, std::string author);   //new Constructor for the Constructor call in main.cpp(L.22-26)

    std::string getIsbn();
    std::string getName();
    std::string getAuthor();
    bool isLent();
    void setLent(bool lent);

    void setShelf(Shelf* shelf);
    void removeShelf();

private:
    std::string isbn;
    std::string name;
    std::string author;
    bool lent;
    Shelf* shelf;
};
