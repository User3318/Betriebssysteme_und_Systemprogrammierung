#include "Library.h"
#include "Book.h"
#include "Visitor.h"
#include <sstream>

Library::Library(std::string name)
{
    this->name = name;
}

bool Library::addShelf(Shelf* shelf)
{
    if (this->shelfs.find(shelf->getId()) != this->shelfs.end()) {
        return false;
    }
    this->shelfs.emplace(shelf->getId(), shelf);
}

bool Library::addBook(Book* book)
{
    if (this->books.find(book->getIsbn()) != this->books.end()) {
        return false;
    }
    this->books.emplace(book->getIsbn(), book);
}

void Library::lentBook(Book* book, Visitor* visitor)
{
    if (book == nullptr) {
        return;
    }
    if (visitor == nullptr) {
        return;
    }
    visitor->addToLentBooks(book);
    book->setLent(true);
    this->lendings.emplace(book, visitor);

}

void Library::returnBook(Book* book, Visitor* visitor)
{
    if (book == nullptr) {
        return;
    }
    if (visitor == nullptr) {
        return;
    }
    if (visitor->removeFromLentBooks(book)) {
        book->setLent(false);
        this->getLendings().erase(book);
    }
}

std::string Library::toString()
{
    return "";
}

const std::map<Book*, Visitor*>& Library::getLendings() const
{
    return lendings;
}
