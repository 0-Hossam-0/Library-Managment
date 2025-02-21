#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "Book.h"
#include "User.h"

class Library {
private:
    Book* booksHead;
    User* userHead;
    int booksSize;
    int usersSize;

    Book* getBook(int bookID);
    User* getUser(int userID);
    void enQueue(Book* book, User* user);
    bool deQueue(int bookID);
    bool deleteUserBook(int userID, int bookID);

public:
    Library();
    int addBook(std::string title, std::string author);
    bool searchBookById(int id);
    void searchBookByTitle(std::string title);
    void displayBooks();
    int registerUser(std::string name);
    void deleteBook(int id);
    void borrowBook(int userID, int bookID);
    void returnBook(int bookID);
    void displayAvailableBooks();
    void displayBorrowedBooks();
    void displayBookQueue(int bookID);
    void sortBooksByTitle();
    void displayUserBooks(int userID);
    void displayUsers();
};

#endif