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
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
namespace sdds  {
    //Default constructor set all to default
Publication::Publication()
{
    setDefault();
}

Publication::Publication(const Publication& publication) {
    *this = publication;
}

Publication& Publication::operator=(const Publication& publication) {
    set(publication.m_membership);
    setRef(publication.m_libRef);
    strcpy(m_shelfId, publication.m_shelfId);
    m_date = publication.m_date;

    if (m_title)
    {
        delete[] m_title;
        m_title = nullptr;
    }
    if (publication.m_title != nullptr) {
        m_title = new char[strlen(publication.m_title) + 1];
        strcpy(m_title, publication.m_title);
    }
    else {
        m_title = nullptr;
    }

    return *this;
}

Publication::~Publication() 
{
delete[] m_title;
}
void Publication::setDefault() {
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
}   
void Publication::set(int member_id) {
    m_membership = member_id;
}

void Publication::setRef(int value) {
    m_libRef = value;
}

void Publication::resetDate() {
    m_date.setToToday();
}

char Publication::type() const {
    return 'P';
}

bool Publication::onLoan() const {
    return (m_membership != 0);
}

Date Publication::checkoutDate() const {
    return m_date;
}

bool Publication::operator==(const char* title) const {
    return strstr(m_title, title) != nullptr;
}

Publication::operator const char* () const {
    return m_title;
}

int Publication::getRef() const {
    return m_libRef;
}

bool Publication::conIO(ios& io) const {
    return (&io == &cin || &io == &cout);
}


ostream& Publication::write(ostream& os) const {
    if (conIO(os)) {
        os << "| " << setw(SDDS_SHELF_ID_LEN) << m_shelfId << " | ";
        int i = 0;
        for (i = 0; i < SDDS_TITLE_WIDTH && m_title[i] != '\0'; i++) {
            os << m_title[i];
        }

        for (; i < SDDS_TITLE_WIDTH; i++) {
            os << ".";
        }

        os << " | ";
        
        if (m_membership != 0) {
            os << setw(5) << m_membership << " | ";
        } else {
            os << setw(4) << "N/A" << "  | ";
        }

        os << m_date << " |";
    } else {
        os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t';
        
        if (m_membership != 0) {
            os << m_membership;
        } else {
            os << "0";
        }
        
        os << '\t' << m_date;
        

    }

    return os;
}


istream& Publication::read(istream& istr) {
		//temps
		char temp_title[256]{};
        char temp_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int temp_libRef = -1;
        int temp_membership = 0;
		Date date;
		//deallocate if exist
		if (m_title) {
			delete[] m_title;
			m_title = nullptr;
		}
		setDefault();
		if (conIO(istr)) 
        {
			cout << "Shelf No: ";
			istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1);
			if (strlen(temp_shelfId) != SDDS_SHELF_ID_LEN) 
            {
            istr.setstate(ios::failbit);
			}
			cout << "Title: ";
			istr.getline(temp_title, 256);
			cout << "Date: ";
			istr >> date;
		}
		else 
		{
			istr >> temp_libRef;
			istr.ignore();
			istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(temp_title, 256, '\t');
			istr >> temp_membership;
			istr.ignore();
			istr >> date;
		}
		if (!date) 
        {
			istr.setstate(ios::failbit);
		}
		if (istr) 
        {
			m_title = new char[strlen(temp_title) + 1];
			strcpy(m_title, temp_title);
			strcpy(m_shelfId, temp_shelfId);
			m_membership = temp_membership;
			m_date = date;
			m_libRef = temp_libRef;
		}
		return istr;
	}

Publication::operator bool() const {
    bool ans = false;
    if (m_title != nullptr && m_shelfId[0] != '\0') {
        ans = true;
    }
    return ans;
}

}
