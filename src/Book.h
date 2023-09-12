#ifndef SDDS_BOOK__
#define SDDS_BOOK__
#include "Publication.h"

namespace sdds {
    class Book : public Publication {
        char* m_authorName;

    public:
        Book();

        //The rule of three
        Book(const Book& book);
        Book& operator=(const Book& book);
        ~Book();

        char type() const;
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
        void set(int member_id);
        operator bool() const;
    };
}
#endif //SDDS_BOOK__