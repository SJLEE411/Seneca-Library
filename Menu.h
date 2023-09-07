/*/////////////////////////////////////////////////////////////////////////
MS 02 

Full Name  : Sangjune Lee
Student ID#: 123050221
Email      : slee569@myseneca.ca
Section    : NEE

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my 
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>

namespace sdds {
        /////
        const unsigned int MAX_MENU_ITEMS = 20;


    class MenuItem {
        private:
        char* content; // cstring to hold menu items

        //constuctor
        MenuItem(const char* item);
        //destructor
        ~MenuItem();
        //bool type conversion
        operator bool() const;
        //const char* type conversion
        operator const char*() const;
        //display
        friend std::ostream& operator<<(std::ostream& os, const MenuItem& item);
        //firend class
        friend class Menu;

        //public:This class should be fully private (no public members; even constructor is private!):


        
    };

    class Menu {
        private:
        //Attributes
        MenuItem* m_title; // holds title of menu
        MenuItem* m_menuItems[MAX_MENU_ITEMS]; // array of menuitem pointer
        unsigned int m_numOfItems; // tracking menuitme obj


        void displayTitle(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);

        public:
        //constructor
        Menu();
        Menu(const char* title);
        //destructor
        ~Menu();
        void displayMenu(std::ostream& os) const;
        //run 
        unsigned int run();
        //~operator
        unsigned int operator~();
        //<<operator
        Menu& operator<<(const char* menuItemContent);

        //overloads
        operator int() const;
        operator unsigned int() const;
        operator bool() const;

        //overload indexing operator
        const char* operator[](int index) const;

    };
    std::ostream& operator<<(std::ostream& os, const Menu& menu);
}
#endif