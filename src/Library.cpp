#include "../include/Library.h"
#include <iostream>


  Library::Library() : booksHead(nullptr), booksSize(1), usersSize(1), userHead(nullptr) {}

  int Library::addBook(std::string title, std::string author)
  {
    Book *newBook = new Book{booksSize++, title, author, true, nullptr, nullptr, nullptr};
    if (!booksHead)
    {
      booksHead = newBook;
      std::cout << title << " Book Got Added To The Library | ID: " << booksSize - 1 << " | Author: " << author << std::endl;
      return booksSize - 1;
    }
    Book *currentBook = booksHead;
    while (currentBook)
    {
      if (currentBook->nextBook == nullptr)
      {
        currentBook->nextBook = newBook;
        std::cout << title << " Book Got Added To The Library | ID: " << booksSize - 1 << " | Author: " << author << std::endl;
        return booksSize - 1;
      }
      currentBook = currentBook->nextBook;
    }
  }

  bool Library::searchBookById(int id)
  {
    Book *currentBook = booksHead;
    while (currentBook)
    {
      if (currentBook->id == id)
      {
        std::cout << "=============================================" << std::endl;
        std::cout << "Book ID: " << currentBook->id << std::endl;
        std::cout << "Book Title: " << currentBook->title << std::endl;
        std::cout << "Book Author: " << currentBook->author << std::endl;
        std::cout << "Book Status: " << (currentBook->isAvailable ? "Available" : "Borrowed") << std::endl;
        std::cout << "=============================================" << std::endl;
        return true;
      }
      currentBook = currentBook->nextBook;
    }
    std::cout << "Invalid Book ID." << std::endl;
    return false;
  }

  void Library::searchBookByTitle(std::string title)
  {
    Book *currentBook = booksHead;
    while (currentBook)
    {
      if (currentBook->title == title)
      {
        std::cout << "=============================================" << std::endl;
        std::cout << "Book ID: " << currentBook->id << std::endl;
        std::cout << "Book Title: " << currentBook->title << std::endl;
        std::cout << "Book Author: " << currentBook->author << std::endl;
        std::cout << "Book Status: " << (currentBook->isAvailable ? "Available" : "Borrowed") << std::endl;
        std::cout << "=============================================" << std::endl;
        return;
      }
      currentBook = currentBook->nextBook;
    }
    std::cout << "Invalid Book Title." << std::endl;
  }

  void Library::displayBooks()
  {
    Book *currentBook = booksHead;
    if (!currentBook)
    {
      std::cout << "There Is No Books In The Library." << std::endl;
      return;
    }
    std::cout << "=============================================" << std::endl;
    while (currentBook)
    {
      std::cout << "Book ID: " << currentBook->id << std::endl;
      std::cout << "Book Title: " << currentBook->title << std::endl;
      std::cout << "Book Author: " << currentBook->author << std::endl;
      std::cout << "Book Status: " << (currentBook->isAvailable ? "Available" : "Borrowed") << std::endl;
      std::cout << "=============================================" << std::endl;
      currentBook = currentBook->nextBook;
    }
  }

  int Library::registerUser(std::string name)
  {
    User *newUser = new User{usersSize++, name, nullptr};
    if (!userHead)
    {
      userHead = newUser;
      std::cout << name << " Got Added To The Library | ID: " << usersSize - 1 << std::endl;
      return usersSize - 1;
    }
    User *currentUser = userHead;
    while (currentUser)
    {
      if (currentUser->nextUser == nullptr)
      {
        currentUser->nextUser = newUser;
        std::cout << name << " Got Added To The Library | ID: " << usersSize - 1 << std::endl;
        return usersSize - 1;
      }
      currentUser = currentUser->nextUser;
    }
  }

  void Library::deleteBook(int id)
  {
    Book *currentBook = booksHead->nextBook;
    Book *prevBook = booksHead;
    if (booksHead->id == id)
    {
      Book *temp = booksHead;
      booksHead = booksHead->nextBook;
      std::cout << temp->title << " Book Got Deleted From The Library." << std::endl;
      delete temp;
      return;
    }
    while (currentBook)
    {
      if (currentBook->id == id)
      {
        Book *temp = currentBook;
        prevBook->nextBook = currentBook->nextBook;
        currentBook = currentBook->nextBook;
        delete temp;
        std::cout << currentBook->title << " Book Got Deleted From The Library." << std::endl;
        return;
      }
      currentBook = currentBook->nextBook;
      prevBook = prevBook->nextBook;
    }
    std::cout << "Invalid Book ID." << std::endl;
  }

  void Library::borrowBook(int userID, int bookID)
  {
    Book *book = getBook(bookID);
    User *user = getUser(userID);
    if (!user)
    {
      std::cout << "Invalid User ID." << std::endl;
      return;
    }
    if (!book)
    {
      std::cout << "Invalid Book ID." << std::endl;
      return;
    }
    Book *currentUserBooks = user->userBooks;
    while (currentUserBooks)
    {
      if (currentUserBooks->id == book->id)
      {
        std::cout << user->name << " Already Borrowed This Book." << std::endl;
        return;
      }
      currentUserBooks = currentUserBooks->nextBook;
    }

    if (!book->isAvailable)
    {
      enQueue(book, user);
      std::cout << book->title << " Book Is Already Borrowed, " << user->name << " Got Added To The Queue Successfully." << std::endl;
      return;
    }
    book->isAvailable = false;
    Book *newBook = new Book{book->id, book->title, book->author, book->isAvailable, nullptr, book->queueFront, book->queueRear};
    if (!user->userBooks)
    {
      user->userBooks = newBook;
      std::cout << user->name << " Borrowed The Book Successfully." << std::endl;
      return;
    }
    currentUserBooks = user->userBooks;
    while (currentUserBooks)
    {
      if (currentUserBooks->nextBook == nullptr)
      {
        currentUserBooks->nextBook = newBook;
        std::cout << user->name << " Borrowed The Book Successfully." << std::endl;
        return;
      }
      currentUserBooks = currentUserBooks->nextBook;
    }
  }
  void Library::returnBook(int bookID)
  {
    Book *book = getBook(bookID);
    User *user = userHead;
    std::string name;
    if (!user)
    {
      std::cout << "The Library Has No Users Yet." << std::endl;
      return;
    }
    else if (!book)
    {
      std::cout << "Invalid Book ID." << std::endl;
    }
    else if (book->isAvailable)
    {
      std::cout << book->title << " Book Is Already Available." << std::endl;
    }
    else
    {
      while (user)
      {
        Book *currentUserBook = user->userBooks;

        while (currentUserBook)
        {
          if (currentUserBook->id == book->id)
          {
            book->isAvailable = true;
            name = currentUserBook->title;
            deleteUserBook(user->id, book->id);
            if (book->queueFront != nullptr)
            {
              std::cout << user->name << " Returned " << name << " Book Successfully." << std::endl;
              borrowBook(book->queueFront->id, book->id);
              deQueue(currentUserBook->id);
              return;
            }
            else if (book->queueFront == nullptr)
            {
              std::cout << user->name << " Returned " << name << " Book Successfully." << std::endl;
              return;
            }
          }
          currentUserBook = currentUserBook->nextBook;
        }
        user = user->nextUser;
      }
    }
  }
  void Library::displayAvailableBooks()
  {
    if (!booksHead)
    {
      std::cout << "There Is No Books In The Library." << std::endl;
      return;
    }
    Book *currentBook = booksHead;
    bool isDisplayed = false;
    std::cout << "=============================================" << std::endl;
    while (currentBook)
    {
      if (currentBook->isAvailable)
      {
        std::cout << "Book ID: " << currentBook->id << std::endl;
        std::cout << "Book Title: " << currentBook->title << std::endl;
        std::cout << "Book Author: " << currentBook->author << std::endl;
        std::cout << "=============================================" << std::endl;
        isDisplayed = true;
      }
      currentBook = currentBook->nextBook;
    }
    if (!isDisplayed)
    {
      std::cout << "There Is No Available Books In The Library Currently." << std::endl;
    }
  }
  void Library::displayBorrowedBooks()
  {
    if (!booksHead)
    {
      std::cout << "There Is No Books In The Library." << std::endl;
      return;
    }
    Book *currentBook = booksHead;
    bool isDisplayed = false;
    std::cout << "=============================================" << std::endl;
    while (currentBook)
    {
      if (!currentBook->isAvailable)
      {
        std::cout << "Book ID: " << currentBook->id << std::endl;
        std::cout << "Book Title: " << currentBook->title << std::endl;
        std::cout << "Book Author: " << currentBook->author << std::endl;
        std::cout << "=============================================" << std::endl;
        isDisplayed = true;
      }
      currentBook = currentBook->nextBook;
    }
    if (!isDisplayed)
    {
      std::cout << "There Is No Available Books In The Library Currently." << std::endl;
    }
  }
  void Library::displayBookQueue(int bookID)
  {
    Book *book = getBook(bookID);
    if (!book)
    {
      std::cout << "Invalid Book ID." << std::endl;
    }
    else if (!book->queueFront)
    {
      std::cout << "There Is Not Queue For This Book." << std::endl;
    }
    else
    {
      User *currentUser = book->queueFront;
      int counter = 1;
      while (currentUser)
      {
        if (currentUser == book->queueFront)
        {
          std::cout << "=============================================" << std::endl;
          std::cout << "User ID: " << currentUser->id << std::endl;
          std::cout << "User Name: " << currentUser->name << std::endl;
          std::cout << "=============================================" << std::endl;
        }
        else
        {
          std::cout << " => " << currentUser->name;
        }
        currentUser = currentUser->nextUser;
      }
    }
  }
  void Library::sortBooksByTitle()
  {
    if (!booksHead)
    {
      std::cout << "There Is No Books In The Library." << std::endl;
      return;
    }
    bool isSwap = true;
    while (isSwap)
    {
      isSwap = false;
      Book *prevBook = booksHead;
      Book *currentBook = booksHead->nextBook;
      while (currentBook)
      {
        for (int i = 0; i < prevBook->title.size() && i < currentBook->title.size(); i++)
        {
          if (prevBook->title[i] > currentBook->title[i])
          {
            std::string arrStr[2] = {prevBook->title, prevBook->author};
            int arrInt[2] = {prevBook->id, prevBook->isAvailable};
            prevBook->title = currentBook->title;
            prevBook->id = currentBook->id;
            prevBook->author = currentBook->author;
            prevBook->isAvailable = currentBook->isAvailable;
            currentBook->title = arrStr[0];
            currentBook->author = arrStr[1];
            currentBook->id = arrInt[0];
            currentBook->isAvailable = arrInt[1];
            isSwap = true;
            break;
          }
        }
        currentBook = currentBook->nextBook;
        prevBook = prevBook->nextBook;
      }
    }
    std::cout << "Library`s Books Got Sorted Successfully." << std::endl;
  }

  void Library::displayUserBooks(int userID)
  {
    User *user = getUser(userID);
    if (!user)
    {
      std::cout << "User Doesn`t Exist." << std::endl;
      return;
    }
    if (user->userBooks == nullptr)
    {
      std::cout << user->name << " Have No Books." << std::endl;
      return;
    }
    Book *currentBook = user->userBooks;
    std::cout << "=============================================" << std::endl;
    while (currentBook)
    {
      std::cout << "Book ID: " << currentBook->id << std::endl;
      std::cout << "Book Title: " << currentBook->title << std::endl;
      std::cout << "Book Author: " << currentBook->author << std::endl;
      std::cout << "=============================================" << std::endl;
      currentBook = currentBook->nextBook;
    }
  }
  void Library::displayUsers()
  {
    if (!userHead)
    {
      std::cout << "There Is No Users Yet In The Library" << std::endl;
      return;
    }
    User *currentUser = userHead;
    std::cout << "=============================================" << std::endl;
    while (currentUser)
    {
      std::cout << "User Name: " << currentUser->name << " | User ID: " << currentUser->id << std::endl;
      std::cout << "=============================================" << std::endl;
      currentUser = currentUser->nextUser;
    }
  }

  Book *Library::getBook(int bookID)
  {
    if (bookID > booksSize)
    {
      std::cout << "Invalid Book ID." << std::endl;
      return nullptr;
    }
    Book *currentBook = booksHead;
    while (currentBook)
    {
      if (currentBook->id == bookID)
      {
        return currentBook;
      }
      currentBook = currentBook->nextBook;
    }
  }
  User *Library::getUser(int userID)
  {
    User *currentUser = userHead;
    while (currentUser)
    {
      if (currentUser->id == userID)
      {
        return currentUser;
      }
      currentUser = currentUser->nextUser;
    }
    return nullptr;
  }

  void Library::enQueue(Book *book, User *user)
  {
    User *newUser = new User{user->id, user->name, user->userBooks, nullptr};
    newUser->nextUser = nullptr;
    if (!book->queueFront && !book->queueRear)
    {
      book->queueFront = newUser;
      book->queueRear = newUser;
    }
    else
    {
      book->queueRear->nextUser = newUser;
      book->queueRear = newUser;
    }
  }

  bool Library::deQueue(int bookID)
  {
    Book *book = getBook(bookID);
    User *temp = book->queueFront;
    if (book->queueFront == nullptr)
    {
      return false;
    }
    else if (book->queueFront->nextUser != nullptr)
    {
      book->queueFront = book->queueFront->nextUser;
      delete temp;
      return true;
    }
    else
    {
      delete temp;
      book->queueFront = nullptr;
      book->queueRear = nullptr;
      return true;
    }
  }
  bool Library::deleteUserBook(int userID, int bookID)
  {
    User *user = getUser(userID);
    if (!user)
      return false;

    if (!getBook(bookID))
      return false;

    Book *currentUserBook = user->userBooks->nextBook;
    Book *prevUserBook = user->userBooks;
    if (!prevUserBook)
      return false;
    if (prevUserBook->id == bookID)
    {
      Book *temp = prevUserBook;
      user->userBooks = prevUserBook->nextBook;
      delete temp;
      return true;
    }
    while (currentUserBook)
    {
      if (currentUserBook->id == bookID)
      {
        Book *temp = currentUserBook;
        prevUserBook->nextBook = currentUserBook->nextBook;
        delete temp;
        return true;
      }
      currentUserBook = currentUserBook->nextBook;
      prevUserBook = prevUserBook->nextBook;
    }
    return false;
  }
