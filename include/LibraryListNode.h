#ifndef LIBRARYLISTNODE_H
#define LIBRARYLISTNODE_H

#include <string>
#include "Library.h"

struct LibraryListNode {
    Library* library;
    LibraryListNode* nextLibrary;
    int id;
    std::string name;
};
LibraryListNode *front = nullptr, *back = nullptr;

#endif