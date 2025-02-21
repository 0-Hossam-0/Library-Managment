#ifndef USER_H
#define USER_H

#include <string>
#include "Book.h"

struct User {
    int id;
    std::string name;
    Book* userBooks;
    User* nextUser;
};

#endif