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
#include "Streamable.h"
#include <ios>
using namespace std;
namespace sdds {
Streamable::~Streamable(){};


ostream& operator<<(std::ostream& os, const Streamable& obj) {
    if (obj) {
        obj.write(os);
    }
    return os;
}

    istream& operator>>(std::istream& is, Streamable& obj) {
        obj.read(is);
        return is;
    }
}
