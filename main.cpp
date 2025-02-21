#include <iostream>
#include <string>
#include "include/Library.h"
#include "include/LibraryListNode.h"
#include "src/Library.cpp"
#include <exception>


int main()
{

    int LibraryIDs = 1;
    std::string input;
    LibraryListNode *currentLibrary = front;
    while (true)
    {
        std::cout << "{0} Create A New Library" << std::endl;
        std::cout << "Options:" << std::endl;
        currentLibrary = front;
        if (!currentLibrary)
        {
            std::cout << "\tNo Libraries Created Yet" << std::endl;
        }
        else
        {
            while (currentLibrary)
            {
                std::cout << "\t{" << currentLibrary->id << "} Library Name: " << currentLibrary->name << " || Library ID: " << currentLibrary->id << std::endl;
                currentLibrary = currentLibrary->nextLibrary;
            }
        }
        std::cout << "\t{-1} Exit" << std::endl;
        std::cout << "Input => ";

        std::cin >> input;
        try
        {
            std::stoi(input);
        }
        catch (const std::invalid_argument &)
        {
            std::cout << "Invalid Input || Numbers Only" << std::endl;
            continue;
        }
        if (input == "-1")
            return 0;

        else if (input == "0")
        {
            Library *theLibrary = new Library;
            LibraryListNode *newLibraryNode = new LibraryListNode;
            newLibraryNode->nextLibrary = nullptr;
            newLibraryNode->library = theLibrary;
            newLibraryNode->id = LibraryIDs++;
            std::cout << "Enter Library`s Name => ";
            std::cin.ignore();
            std::getline(std::cin, newLibraryNode->name);
            if (front == nullptr)
            {
                front = newLibraryNode;
                back = newLibraryNode;
            }
            else
            {
                back->nextLibrary = newLibraryNode;
                back = back->nextLibrary;
            }
            continue;
        }
        else if (input >= "1" && std::stoi(input) <= LibraryIDs)
        {
            currentLibrary = front;
            while (currentLibrary)
            {
                if (currentLibrary->id == std::stoi(input))
                    break;
                currentLibrary = currentLibrary->nextLibrary;
            }
            while (currentLibrary)
            {
                int id;
                std::string name;
                std::string author;
                std::cout << "Options:" << std::endl;
                std::cout << "\t{1} Book Options" << std::endl;
                std::cout << "\t{2} User Options" << std::endl;
                std::cout << "\t{3} Search Options" << std::endl;
                std::cout << "\t{4} Display Options" << std::endl;
                std::cout << "\t{5} Sort Library`s Books" << std::endl;
                std::cout << "\t{-1} Back" << std::endl;
                std::cout << "Input => ";
                std::cin >> input;
                try
                {
                    std::stoi(input);
                }
                catch (const std::invalid_argument &)
                {
                    std::cout << "Invalid Input || Numbers Only" << std::endl;
                    continue;
                }
                if (std::stoi(input) == 1)
                {
                    std::cout << "\tOptions:" << std::endl;
                    std::cout << "\t\t{1} Add A New Book" << std::endl;
                    std::cout << "\t\t{2} Delete A Book" << std::endl;
                    std::cout << "\t\t{-1} Back" << std::endl;
                    std::cout << "Input => ";
                    std::cin >> input;

                    try
                    {
                        std::stoi(input);
                    }
                    catch (const std::invalid_argument &)
                    {
                        std::cout << "Invalid Input || Numbers Only" << std::endl;
                        continue;
                    }
                    if (std::stoi(input) == 1)
                    {
                        std::cout << "Enter The Book`s Title => ";
                        std::cin.ignore();

                        std::getline(std::cin, name);
                        std::cout << "Enter The Book`s Author => ";
                        std::getline(std::cin, author);
                        currentLibrary->library->addBook(name, author);
                    }
                    else if (std::stoi(input) == 2)
                    {
                        std::cout << "Enter Book`s ID222 => ";
                        std::cin >> id;
                        currentLibrary->library->deleteBook(id);
                    }
                }
                else if (std::stoi(input) == 2)
                {
                    std::cout << "\tOptions:" << std::endl;
                    std::cout << "\t\t{1} Register A New User From The Library" << std::endl;
                    std::cout << "\t\t{2} Borrow A Book For A User" << std::endl;
                    std::cout << "\t\t{3} Return A Book" << std::endl;
                    std::cout << "\t\t{-1} Back" << std::endl;
                    std::cout << "Input => ";
                    std::cin >> input;
                    try
                    {
                        std::stoi(input);
                    }
                    catch (const std::invalid_argument &)
                    {
                        std::cout << "Invalid Input || Numbers Only" << std::endl;
                        continue;
                    }
                    if (std::stoi(input) == 1)
                    {
                        std::cout << "Enter User Name => ";
                        std::cin.ignore();
                        std::getline(std::cin, name);
                        currentLibrary->library->registerUser(name);
                    }

                    else if (std::stoi(input) == 2)
                    {
                        int id2;
                        std::cout << "Enter User`s ID => ";
                        std::cin >> id;
                        std::cout << "Enter Book`s ID => ";
                        std::cin >> id2;
                        currentLibrary->library->borrowBook(id, id2);
                    }
                    else if (std::stoi(input) == 3)
                    {
                        std::cout << "Enter Book ID => ";
                        std::cin >> id;
                        currentLibrary->library->returnBook(id);
                    }
                }
                else if (std::stoi(input) == 3)
                {
                    std::cout << "\tOptions:" << std::endl;
                    std::cout << "\t\t{1} Search By ID" << std::endl;
                    std::cout << "\t\t{2} Search By Title" << std::endl;
                    std::cout << "\t\t{-1} Back" << std::endl;
                    std::cout << "Input => ";
                    std::cin >> input;
                    try
                    {
                        std::stoi(input);
                    }
                    catch (const std::invalid_argument &)
                    {
                        std::cout << "Invalid Input || Numbers Only" << std::endl;
                        continue;
                    }
                    if (std::stoi(input) == 1)
                    {
                        std::cout << "Enter Book`s ID => ";
                        std::cin >> id;
                        currentLibrary->library->searchBookById(id);
                    }
                    else if (std::stoi(input) == 2)
                    {
                        std::cout << "Enter Book`s Title => ";
                        std::cin.ignore();

                        std::getline(std::cin, name);
                        currentLibrary->library->searchBookByTitle(name);
                    }
                }
                else if (std::stoi(input) == 4)
                {
                    std::cout << "\tOptions:" << std::endl;
                    std::cout << "\t\t{1} Display Library's Books" << std::endl;
                    std::cout << "\t\t{2} Display Library's Users" << std::endl;
                    std::cout << "\t\t{3} Display Available Books" << std::endl;
                    std::cout << "\t\t{4} Display Borrowed Books" << std::endl;
                    std::cout << "\t\t{5} Display Book`s Queue" << std::endl;
                    std::cout << "\t\t{6} Display User's Books" << std::endl;
                    std::cout << "\t\t{-1} Back" << std::endl;
                    std::cout << "Input => ";
                    std::cin >> input;
                    try
                    {
                        std::stoi(input);
                    }
                    catch (const std::invalid_argument &)
                    {
                        std::cout << "Invalid Input || Numbers Only" << std::endl;
                        continue;
                    }
                    if (std::stoi(input) == 1)
                    {
                        currentLibrary->library->displayBooks();
                    }
                    else if (std::stoi(input) == 2)
                    {
                        currentLibrary->library->displayUsers();
                    }
                    else if (std::stoi(input) == 3)
                    {
                        currentLibrary->library->displayAvailableBooks();
                    }
                    else if (std::stoi(input) == 4)
                    {
                        currentLibrary->library->displayBorrowedBooks();
                    }
                    else if (std::stoi(input) == 5)
                    {
                        std::cout << "Enter Book`s ID => ";
                        std::cin >> id;
                        currentLibrary->library->displayBookQueue(id);
                    }
                    else if (std::stoi(input) == 6)
                    {
                        std::cout << "Enter User`s ID => ";
                        std::cin >> id;
                        currentLibrary->library->displayUserBooks(id);
                    }
                    else if (std::stoi(input) > 6 && std::stoi(input) <= 0 && std::stoi(input) != -1)
                    {
                        std::cout << "Invalid Input" << std::endl;
                    }
                }
                else if (std::stoi(input) == 5)
                {
                    currentLibrary->library->sortBooksByTitle();
                }
                else if (std::stoi(input) == -1)
                {
                    break;
                }
            }
        }
    }
}
