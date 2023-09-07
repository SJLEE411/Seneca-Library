/*/////////////////////////////////////////////////////////////////////////
MS 05 

Full Name  : Sangjune Lee
Student ID#: 123050221
Email      : slee569@myseneca.ca
Section    : NEE

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my 
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__

#include "Publication.h"
#include <iostream>

namespace sdds {
    class Book : public Publication {
        char* authorName;

        public:
        Book();
        Book(const Book& other);
        Book& operator=(const Book& other);
        ~Book();
        bool conIO(std::ios& io) const;
        char type() const;
        std::ostream& write(std::ostream& os = std::cout) const;
        std::istream& read(std::istream& is = std::cin);
        void set(int id);
        operator bool() const;
    };

}
#endif // !SDDS_BOOK_H__
