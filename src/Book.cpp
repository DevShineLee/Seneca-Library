#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Book.h"
using namespace std;

namespace sdds {
    Book::Book() : Publication(), m_authorName(nullptr) {}

    //The rule of three
    Book::Book(const Book& book) : Publication(book) {
        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }
        m_authorName = new char[strlen(book.m_authorName) + 1];
        strcpy(m_authorName, book.m_authorName);
    }
    Book& Book::operator=(const Book& book) {
        Publication::operator=(book);
        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }
        if (book.m_authorName) {
            m_authorName = new char[strlen(book.m_authorName) + 1];
            strcpy(m_authorName, book.m_authorName);
        }
        return *this;
    }
    Book::~Book() {
        delete[] m_authorName;
        m_authorName = nullptr;
    }

    char Book::type() const {
        return 'B';
    };

    ostream& Book::write(ostream& ostr) const {
        Publication::write(ostr);
        if (conIO(ostr)) {
            char author[SDDS_AUTHOR_WIDTH + 1] = { 0 };
            strncpy(author, m_authorName, SDDS_AUTHOR_WIDTH);
            ostr << " ";
            ostr << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
        }
        else {
            ostr << "\t" << m_authorName;
        }

        return ostr;
    }

    istream& Book::read(istream& istr) {
        char authorName[SDDS_MAX_AUTHOR_NAME]{};
        Publication::read(istr);
        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }
        if (conIO(istr)) {
            istr.ignore();
            cout << "Author: ";
        }
        else {
            istr.ignore(1000, '\t');
        }
        istr.get(authorName, SDDS_MAX_AUTHOR_NAME);
        if (istr) {
            m_authorName = new char[strlen(authorName) + 1];
            strcpy(m_authorName, authorName);
        }
        return istr;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        Publication::resetDate();
    }

    Book::operator bool() const {
        return (m_authorName && m_authorName[0] != '\0' && Publication::operator bool());
    }
}