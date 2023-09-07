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
#ifndef SDDS_LIB_H_
#define SDDS_LIB_H_
namespace sdds {
const int SDDS_MAX_LOAN_DAYS = 15; 
     // maximum number of day a publication can be borrowed with no penalty
const int SDDS_TITLE_WIDTH = 30;
    // The width in which the title of a publication should be printed on the console
const int SDDS_AUTHOR_WIDTH = 15;
    // The width in which the author name of a book should be printed on the console
const int SDDS_SHELF_ID_LEN = 4;
   // The width in which the shelf id of a publication should be printed on the console
const int SDDS_LIBRARY_CAPACITY = 333;
   // Maximum number of publications the library can hold.
const int SDDS_MAX_FILENAME = 256;
    //MS05 filename length
}
#endif //! Lib_H_