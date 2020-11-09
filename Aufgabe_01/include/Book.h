#pragma once

#include <string>

class Shelf;
class Book {
public:
    Book(std::string isbn, std::string name, std::string author, bool lent);

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
