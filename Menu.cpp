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
#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include <cstring>
using namespace std;

namespace sdds {
        //MENUITEM
        //char* content;


        //constructor
        MenuItem::MenuItem(const char* item) {
            if (item != nullptr && item[0] != '\0') {
                content = new char[strlen(item) + 1];
                strcpy(content, item);
            }
            else {
                content = nullptr;
            }
        }

        //destructor
        MenuItem::~MenuItem() {
            delete[] content;

        }

        //bool type conversion
        MenuItem::operator bool() const {
            return content != nullptr;
        }

        //const char* type conversion
        MenuItem::operator const char*() const {
            return content;
        }

        //display
        ostream& operator<<(ostream& os, const MenuItem& item) {
            if (item.content != nullptr) {
                os << item.content;
            }
            return os;
        }

    /////MENU
        //Constructor
        Menu::Menu() {
            m_title = nullptr;
            m_numOfItems = 0;
            for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
                m_menuItems[i] = nullptr;
            }
        }

        Menu::Menu(const char* title) {
            m_numOfItems = 0;
            m_title = new MenuItem(title);
            for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
                m_menuItems[i] = nullptr;
            }        
        };

        //Destructor: looping through the menuitem array of pointers, deletes each pointer
        Menu::~Menu() { 
            delete m_title;
            m_title = nullptr;

            for(unsigned int i = 0; i < m_numOfItems; i++) {
                delete m_menuItems[i];
                m_menuItems[i] = nullptr;
            }
        }

        //Methods
        //display title : private
        //title empty then do nothing
        void Menu::displayTitle(ostream& os) const {
            if(m_title) {
            os << *m_title  << endl;
            }
        }

        //displaymenu
        void Menu::displayMenu(ostream& os) const {
            displayTitle(os);
            for (unsigned int i = 0; i < m_numOfItems; i++) {
                os << " " << i + 1 << "- " << *m_menuItems[i] << endl;
            }
        os << " 0- Exit" << endl;
        os << "> ";
        }

        //run
        unsigned int Menu::run() {
        unsigned int selection = 0;
        bool isValidSelection = false;

        do {
            displayMenu(cout);
            selection = getIntInputWithinRange(0, m_numOfItems);

            if (selection == 0 || (selection >= 1 && selection <= m_numOfItems)) {
                isValidSelection = true;
            }
        } while (!isValidSelection);
        return selection;
        }


        //~operator
        unsigned int Menu::operator~() {
            return run();
        }

        //<<operator
        Menu& Menu::operator<<(const char* menuItemContent) {
            if (m_numOfItems < MAX_MENU_ITEMS) {
                m_menuItems[m_numOfItems] = new MenuItem(menuItemContent);
                m_numOfItems++;
            }
            return *this;
        }
        

        //overloads
        //int
        Menu::operator int() const {
            return m_numOfItems;
        }

        //unsigned int
        Menu::operator unsigned int() const {
            return m_numOfItems;
        }

        //bool
        Menu::operator bool() const {
            return m_numOfItems > 0;
        }

            //insertion operator overload
        ostream& operator<<(ostream& os, const Menu& menu) {
        if (menu.m_title != nullptr) {
            os << *menu.m_title;
        }
        return os;
        }

        const char* Menu::operator[](int index) const {
        if (m_numOfItems == 0) {
            return nullptr;
        }
        index = index % m_numOfItems; // loop back if exceeds
        return (const char*)(*m_menuItems[index]);
        }
}