#include "Book.h"
#include <cstring>
#include "Utils.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace sdds  {


Book::Book() : authorName(nullptr) {
}

Book::Book(const Book& other) : Publication(other) {
    *this = other;
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        Publication::operator=(other);
        delete[] authorName;
        if (other.authorName) {
            authorName = new char[strlen(other.authorName) + 1];
            strcpy(authorName, other.authorName);
        } else {
            authorName = nullptr;
        }
    }
    return *this;
}

Book::~Book() {
    delete[] authorName;
}

char Book::type() const {
    return 'B';
}

bool Book::conIO(ios& io) const {
    return &io == &cin || &io == &cout;
}

ostream& Book::write(ostream& os) const {
Publication::write(os);
    if (conIO(os)) {
        os << " ";
        int i = 0;
        for (i = 0; i < SDDS_AUTHOR_WIDTH && authorName[i] != '\0'; i++) {
            os << authorName[i];
        }
        for (int j = i; j < SDDS_AUTHOR_WIDTH; j++) {
            os << " ";
        }
        os << " |";
    }
    else {
        os << '\t';
        int i = 0;
        for (i = 0; authorName[i] != '\0'; i++) {
            os << authorName[i];
        }

    }
    return os;
}

istream& Book::read(istream& is) {
    Publication::read(is);
    char authorBuffer[256];

    if (authorName) {
        delete[] authorName;
    }
    authorName = nullptr;

    if (conIO(is)) {
        is.ignore(1);
        cout << "Author: ";
        is.get(authorBuffer, 256);
    } else {
        is.ignore(1);
        is.get(authorBuffer, 256);
    }
    if (!is.fail()) {
        authorName = new char[strlen(authorBuffer) + 1];
        strcpy(authorName, authorBuffer);
    }
    return is;
}

void Book::set(int id) {
    Publication::set(id);
    resetDate();
}

Book::operator bool() const {
    return (authorName && authorName[0] != '\0' && Publication::operator bool());
}



}