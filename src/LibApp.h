#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "Streamable.h"
#include "Lib.h"
namespace sdds {

   class LibApp : public Menu {
        char m_fileName[SDDS_MAX_FILENAME];
        Publication* m_PPA[SDDS_LIBRARY_CAPACITY]{};
        int m_NOLP;
        int m_LLRN;

        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_publicationType;

        bool confirm(const char* message);

        void load();
        void save();
        int search(int searchType);
        void returnPub();

        void newPublication();
        void removePublication();
        void checkOutPub();

    public: 
        LibApp(const char* filename);
        ~LibApp();
        void run();
        Publication* getPub(int libRef);
   };
}
#endif // !SDDS_LIBAPP_H



