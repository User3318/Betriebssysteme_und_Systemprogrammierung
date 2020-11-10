#pragma once

#include <string>
#include <map>

class Book;
class Visitor;
class Shelf;
class Library {
public:
    Library(std::string name);
    ~Library();

    bool addShelf(Shelf* shelf);
    bool addBook(Book* book);

    void lentBook(Book* book, Visitor* visitor);
    void returnBook(Book* book, Visitor* visitor);

    const std::map<Book *, Visitor *> &getLendings() const;

    std::string toString();

private:
    std::map<std::string, Shelf*> shelfs;
    std::map<std::string, Book*> books;
    std::map<Book* , Visitor*> lendings;
    std::string name;
};

