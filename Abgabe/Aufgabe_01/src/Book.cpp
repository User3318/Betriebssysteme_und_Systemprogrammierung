#include "Book.h"
#include "Shelf.h"

Book::Book(std::string isbn, std::string name, std::string author, bool lent) {
    this->isbn = isbn;
    this->name = name;
    this->author = author;
    this->lent = lent;
    this->shelf = nullptr;
}

Book::Book(std::string isbn, std::string name, std::string author) {
    this->isbn = isbn;
    this->name = name;
    this->author = author;
    this->lent = false;
    this->shelf = nullptr;  //exit code -1073741819 (0xC0000005) wenn shelf nicht auf nullptr gesetzt wird. Unter Windows10 CLion2020.2.4
}

void Book::setShelf(Shelf* shelf) {
    if(shelf == nullptr) {
        return;
    }
    if(this->shelf == shelf) {
        return;
    }
    if(this->shelf != nullptr) {
        this->shelf->removeBook(this);
    }
    this->shelf = shelf;
    this->shelf->addBook(this);
}

void Book::removeShelf() {
    if(this->shelf != nullptr) {
        this->shelf->removeBook(this);
    }
    this->shelf = nullptr;
}

std::string Book::getIsbn() {
    return this->isbn;
}

std::string Book::getName() {
    return this->name;
}

std::string Book::getAuthor()  {
    return this->author;
}

bool Book::isLent()  {
    return this->lent;
}

void Book::setLent(bool lent) {
    this->lent = lent;
}
