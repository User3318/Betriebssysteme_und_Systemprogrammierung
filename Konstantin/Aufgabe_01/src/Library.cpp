#include "Library.h"
#include "Book.h"
#include "Visitor.h"
#include "Shelf.h"
#include <sstream>

Library::Library(std::string name)
{
    this->name = name;
}

Library::~Library(){

}

bool Library::addShelf(Shelf* shelf)
{
    if (this->shelfs.find(shelf->getId()) != this->shelfs.end()) {
        return false;
    }
    this->shelfs.emplace(shelf->getId(), shelf);
    return true;
}

bool Library::addBook(Book* book)
{
    if (this->books.find(book->getIsbn()) != this->books.end()) {
        return false;
    }
    this->books.emplace(book->getIsbn(), book);
    return true;
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
        this->lendings.erase(book);
    }
}

std::string Library::toString()
{
    std::stringstream output;
    output << name << "\n\n";
    for (auto const& currentShelf : shelfs) {
        output << "Regal: " << currentShelf.first << "\n\n";
        for (auto const& currentBook : currentShelf.second->getBooks()) {
            output << currentBook->getName()
                   << " (ISBN: " << currentBook->getIsbn() << ") von "
                   << currentBook->getAuthor()
                   << "\n       Leihstatus: ";
            if (currentBook->isLent()) {
                output << "verliehen an " << lendings.at(currentBook)->getName();
            } else {
                output << "Verfügbar";
            }
            output << "\n\n";
            
        }
        output << "\n";
    }
    return output.str();
}

const std::map<Book*, Visitor*>& Library::getLendings() const
{
    return lendings;
}
