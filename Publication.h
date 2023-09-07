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
#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

namespace sdds  {
    class Publication : public Streamable {
		char* m_title{};
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int m_membership = 0;
		int m_libRef = -1;
		Date m_date;

    public:
        Publication();
        ~Publication();
        Publication(const Publication& publication);
        Publication& operator=(const Publication& publication);
        //modifiers
        void setDefault();
        void set(int member_id);
        void setRef(int value);
        void resetDate();
        //queries
        virtual char type() const;
        bool onLoan() const;
        Date checkoutDate() const;
        bool operator==(const char* title) const;
        operator const char* () const;
        int getRef() const;
        bool conIO(std::ios& io) const override;
        std::ostream& write(std::ostream& os) const override;
        std::istream& read(std::istream& istr) override;
        operator bool() const override;
        
};
} 
#endif //! SDDS_PUBLICATION_H__