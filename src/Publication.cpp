#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Publication.h"

using namespace std;
namespace sdds {
    Publication::Publication() : m_title(nullptr), m_membership(0), m_libRef(-1), m_date(Date()) {
        m_shelfId[0] = '\0';
    }

    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return (m_membership != 0);
    }

    // The rule of three
    Publication::Publication(const Publication& publication) {
        *this = publication;
    }
    Publication& Publication::operator=(const Publication& publication) {
        set(publication.m_membership);
        setRef(publication.m_libRef);
        strcpy(m_shelfId, publication.m_shelfId);
        m_date = publication.m_date;
        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }
        if (publication.m_title != nullptr) {
            int len = strlen(publication.m_title) + 1;
            m_title = new char[len];
            strcpy(m_title, publication.m_title);
        }
        else {
            m_title = nullptr;
        }
        return *this;
    }
    Publication::~Publication() {
        delete[] m_title;
        m_title = nullptr;
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
        return &io == &cin || &io == &cout;
    }

    ostream& Publication::write(ostream& ostr) const {
        char title[SDDS_TITLE_WIDTH + 1] = { 0 };
        strncpy(title, m_title, SDDS_TITLE_WIDTH);

        if (conIO(ostr)) {
            ostr << "| " << m_shelfId << " | " << setw(30) << left << setfill('.') << title << " | ";
            if (m_membership != 0) {
                ostr << m_membership;
            }
            else {
                ostr << " N/A ";
            }
            ostr << " | " << m_date << " |";
        }
        else {
            ostr << type();
            ostr << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
            if (m_membership >= 0) {
                ostr << m_membership;
            }
            else {
                ostr << " N/A ";
            }
            ostr << "\t" << m_date;
        }
        return ostr;
    }

    istream& Publication::read(istream& istr) {
        char t_title[SDDS_MAX_TITLE]{};
        char t_shelfId[SDDS_SHELF_ID_LEN + 1]{};
        int t_libRef = -1;
        int t_membership = 0;
        Date t_date;
        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }
        *this = Publication();
        if (conIO(istr)) {
            cout << "Shelf No: ";
            istr.getline(t_shelfId, SDDS_SHELF_ID_LEN + 1);

            if (strlen(t_shelfId) != SDDS_SHELF_ID_LEN) {
                istr.setstate(ios::failbit);
            }
            cout << "Title: ";
            istr.getline(t_title, SDDS_MAX_TITLE);
            cout << "Date: ";
            istr >> t_date;
        }
        else {
            istr >> t_libRef;
            istr.ignore();
            istr.getline(t_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            istr.getline(t_title, SDDS_MAX_TITLE, '\t');
            istr >> t_membership;
            istr.ignore();
            istr >> t_date;
        }
        if (!t_date) {
            istr.setstate(ios::failbit);
        }
        if (istr) {
            int len = strlen(t_title) + 1;
            m_title = new char[len];
            strcpy(m_title, t_title);
            strcpy(m_shelfId, t_shelfId);
            m_membership = t_membership;
            m_date = t_date;
            m_libRef = t_libRef;
        }
        return istr;
    }

    Publication::operator bool() const {
        return (m_title != nullptr && m_shelfId[0] != '\0');
    }
}