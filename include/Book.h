#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
    int id;
    std::string title;
    std::string author;
    bool isAvailable;
    Book* nextBook;
    struct User* queueFront;
    struct User* queueRear;
};

#endif