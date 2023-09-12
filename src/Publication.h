#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

namespace sdds {
    class Publication : public Streamable {
    private:
        char* m_title;
        char m_shelfId[SDDS_SHELF_ID_LEN + 1];
        int m_membership;
        int m_libRef;
        Date m_date;
    public:
        Publication();
        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();
        virtual char type()const;
        bool onLoan()const;

        //The rule of three
        Publication(const Publication& publication);
        Publication& operator=(const Publication& publication);
        virtual ~Publication();

        Date checkoutDate() const;
        bool operator==(const char* title) const;
        operator const char* () const;
        int getRef() const;
        virtual bool conIO(std::ios& io) const;
        virtual std::ostream& write(std::ostream& ostr) const;
        virtual std::istream& read(std::istream& istr);
        operator bool() const;
    };
}
#endif //SDDS_PUBLICATION_H__