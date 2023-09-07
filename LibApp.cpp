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
#include "LibApp.h"
#include "Menu.h"
#include "Utils.h"
#include "Publication.h"
#include "PublicationSelector.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;
namespace sdds {
    LibApp::LibApp(const char* filename)
        : m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_publicationType("Choose the type of publication:") {
        if (filename) {
            strcpy(m_filename, filename);
        }
        m_changed = false;
        m_NOLP = 0;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationType << "Book" << "Publication";
        load();
    }
    LibApp::~LibApp() {

        for (int i = 0; i < m_NOLP; i++) {
            delete m_PPA[i];
        }
    }
    
    bool LibApp::confirm(const char* message) {
        Menu menu(message);
        menu << "Yes";
        return menu.run() == 1;
    }


    //MS05 Method modification
    void LibApp::load() {
        cout << "Loading Data" << endl;// cout loading data
        ifstream infile(m_filename);//open data file for reading from PPA
        char type{}; // to readfirst letter
        for(int i = 0; infile && i < SDDS_LIBRARY_CAPACITY; i++)
        { //B	1001	C544	The Hobbit	35277	2023-07-14	J. R. R. Tolkien
            infile >> type;
            infile.ignore();
            if (infile) {
                if(type == 'P')
                    m_PPA[i] = new Publication;
                else if(type == 'B')
                    m_PPA[i] = new Book;

                if(m_PPA[i]) {
                    infile >> *m_PPA[i];
                    m_NOLP++; //add one to the NOLP
                    m_LLRN = m_PPA[i] ->getRef();
                }
            }
        }
    }
    
    void LibApp::save() {
        cout << "Saving Data" << endl; // print
        ofstream out_file(m_filename);
        for(int i = 0; i < m_NOLP; i++)
        {
            if(m_PPA[i]->getRef() != 0)
            {
                out_file << *m_PPA[i] << endl;
            }
        }
        out_file.close();
    }
    int LibApp::search(int searchType) {
    //cout << "Searching for publication" << endl; 
    // 1.Search all
    // 2.Search Checkout Items Search only those publications which are on loan by library members
    // 3.Search Available Items Search only those publications which are not on loan
    // will use PublicationSelector
    char title[256]{};
    int libRef = 0; 
    char typeChar;
    PublicationSelector pubSelector("Select one of the following found matches:", 15);
    int selType = m_publicationType.run();
    typeChar = (selType == 1) ? 'B' : 'P';
    // Searching ppa
    cin.ignore(1000, '\n');
    cout << "Publication Title: ";
    cin.getline(title, 256);
    
    for (int i = 0; i < m_NOLP; i++) {
        if (m_PPA[i] -> operator==(title)
         && m_PPA[i] -> type() == typeChar
         && m_PPA[i] -> getRef() != 0) {
            if ((searchType == 1) ||
                (searchType == 2 && m_PPA[i]->onLoan()) ||
                (searchType == 3 && !m_PPA[i]->onLoan())) {
                    pubSelector << m_PPA[i];
            }
        }
    }

    if (pubSelector) {
            pubSelector.sort();
            libRef = pubSelector.run();
            if (libRef > 0) {
                cout << *getPub(libRef) << endl;
            } else {
                cout << "Aborted!" << endl;
            }
        } else {
            cout << "No matches found!" << endl;
        }

    return libRef;
    }

    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() == libRef) {
                return m_PPA[i];
            }
        }
        return nullptr;
    }

    void LibApp::newPublication() {
    if (m_NOLP == SDDS_LIBRARY_CAPACITY) {
    cout << "Library is at its maximum capacity!\n" << endl;
    return;
    }
    cout << "Adding new publication to the library" << endl;
    int pubType = m_publicationType.run();
    cin.ignore(1000, '\n');
    Publication* p = nullptr;
    if (pubType == 0) {
        cout << "Aborted!\n" << endl;
        return;
    }

    
    if (pubType == 1) {
        p = new Book;
    }
    else if (pubType == 2) {
        p = new Publication;
    }

    if (p) {
        cin >> *p;
        if (cin.fail()) {
            cin.ignore(1000, '\n');
            cin.clear();
            cout << "Aborted!" << endl;
            delete p;
            return;
        }

        if (confirm("Add this publication to the library?")) {
            if (*p) {
                m_LLRN++;
                p->setRef(m_LLRN);
                m_PPA[m_NOLP++] = p;
                m_changed = true;
                cout << "Publication added" << endl;
            }
            else {
                cout << "Failed to add publication!" << endl;
                delete p;
            }
        }
        else {
            delete p;
        }
    }
    cout << endl;
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int libRef = search(1); // search pub 
        if (libRef) {
            if (confirm("Remove this publication from the library?")) {
                Publication* pubToRemove = getPub(libRef);
                if (pubToRemove) {
                    pubToRemove->setRef(0);
                    m_changed = true;
                    cout << "Publication removed" << endl;
                }
                else {
                    cout << "Publication not found!" << endl;
                }
            }
        }
        cout << endl;
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int ref = search(3); 
        if (ref > 0) {
            if (confirm("Check out publication?")) {
                cout << "Enter Membership number: ";
                int inputMembership = getIntInputWithinRange(10000, 99999, "Invalid membership number, try again: ");
                Publication* pub = getPub(ref);
                pub->set(inputMembership);
                pub->resetDate(); 
                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
        cout << endl;
    }

    void LibApp::returnPub() {
        Date now;
        cout << "Return publication to the library" << endl;
        int ref = search(2);
        if (ref != 0) {
            bool confirmed = confirm("Return Publication?");
            if (confirmed) {
                int lateDays = now - getPub(ref)->checkoutDate();
                if (lateDays > SDDS_MAX_LOAN_DAYS) {
                    double penalty = (lateDays - SDDS_MAX_LOAN_DAYS) * 0.50;
                    cout << "Please pay $" << fixed << setprecision(2) 
                    << penalty << " penalty for being " 
                    << (lateDays - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
                }
                if (getPub(ref)->type() == 'B') { 
                    Book* book = dynamic_cast<Book*>(getPub(ref));
                    if (book) {
                        book->resetDate();
                    }
                }
                getPub(ref)->set(0);
                m_changed = true;
                cout << "Publication returned" << endl;
            }
        }
        cout << endl;
    }

    void LibApp::run() {
    while (true) {
            int userInputMenu = m_mainMenu.run();

            switch (userInputMenu) {
                case 0:
                    if (m_changed) {
                        int userInputExit = m_exitMenu.run();

                        switch (userInputExit) {
                            case 0:
                                if (confirm("This will discard all the changes are you sure?")) {
                                    m_changed = false;
                                }
                                break;
                            case 1:
                                save();
                                break;
                            case 2:
                                continue;
                        }
                    }
                    break;
                case 1:
                    newPublication();
                    break;
                case 2:
                    removePublication();
                    break;
                case 3:
                    checkOutPub();
                    break;
                case 4:
                    returnPub();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

            if (userInputMenu == 0) {
                cout << endl;
                break;
            }
        }
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }
}