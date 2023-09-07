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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Lib.h"
#include "Publication.h"
#include "Streamable.h"
#include "Book.h"
namespace sdds {
   class LibApp {
      bool m_changed;
      Menu m_mainMenu;
      Menu m_exitMenu;

      //MS05 attributes
      char m_filename[SDDS_MAX_FILENAME + 1]; // LibApp module attribute
      Publication* m_PPA[SDDS_LIBRARY_CAPACITY];//pointer array publication
      int m_NOLP; // Num of loaded publication
      int m_LLRN; //Last Library Ref num
      Menu m_publicationType; //publication type menu
      bool confirm(const char* message);
      void load();  // prints: "Loading Data"<NEWLINE>
      void save();  // prints: "Saving Data"<NEWLINE>
      int search(int searchType);  // prints: "Searching for publication"<NEWLINE>
      Publication* getPub(int libRef);
      void returnPub();  /*  Calls the search() method.
                             prints "Returning publication"<NEWLINE>
                             prints "Publication returned"<NEWLINE>
                             sets m_changed to true;
                         */
      void newPublication();
      void removePublication();
      void checkOutPub();
      public:

      void run();
      LibApp(const char* filename);
      ~LibApp();
   };
}
#endif // !SDDS_LIBAPP_H



