#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Menu.h"
using namespace std;
namespace sdds {

    MenuItem::MenuItem() {
        m_content = nullptr;
    }

    MenuItem::MenuItem(const char* content) {
        if (content != nullptr) {
            m_content = new char[strlen(content) + 1];
            strcpy(m_content, content);
        }
        else {
            m_content = nullptr;
        }
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    bool MenuItem::isEmpty() const {
        return m_content == nullptr;
    }

    MenuItem::operator bool() const {
        return !isEmpty();
    }

    MenuItem::operator const char* () const {
        return m_content;
    }

    void MenuItem::display(ostream& os) const {
        if (!isEmpty()) {
            os << m_content;
        }
    }

    // Menu ///////////////////
    Menu::Menu() {
        m_title = nullptr;
        m_numItems = 0;

        for (unsigned i = 0; i < MAX_MENU_ITEMS; i++) {
            m_menuItems[i] = nullptr;
        }
    }

    Menu::Menu(const char* title) {
        m_title = new MenuItem(title);
        m_numItems = 0;

        for (unsigned i = 0; i < MAX_MENU_ITEMS; i++) {
            m_menuItems[i] = nullptr;
        }
    }

    Menu::~Menu() {
        delete m_title;

        for (unsigned i = 0; i < m_numItems; i++) {
            delete m_menuItems[i];
        }
    }

    void Menu::displayTitle(ostream& os) const {
        if (m_title != nullptr) {
            const char* titleContent = *m_title;
            os << titleContent;
        }
    }

    void Menu::displayMenu(ostream& os) const {
        displayTitle(os);
        if (m_title != nullptr) {
            os << endl;
        }
        for (unsigned i = 0; i < m_numItems; i++) {
            os << right << setw(2) << i + 1 << "- ";
            m_menuItems[i]->display(os);
            os << endl;
        }
        os << " 0- Exit" << endl;
        os << "> ";
    }

    int Menu::run() const {
        unsigned int selection;
        bool isValidSelection = false;

        do {
            displayMenu(cout);
            do {
                cin >> selection;

                if (cin.fail() || selection < 0 || selection > m_numItems) {
                    cout << "Invalid Selection, try again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    isValidSelection = true;
                }
            } while (!isValidSelection);

            isValidSelection = true;

        } while (!isValidSelection);

        return selection;
    }

    int Menu::operator~() const {
        return run();
    }

    Menu& Menu::operator<<(const char* menuItemContent) {
        if (m_numItems < MAX_MENU_ITEMS) {
            m_menuItems[m_numItems] = new MenuItem(menuItemContent);
            m_numItems++;
        }
        return *this;
    }

    Menu::operator int() const {
        return m_numItems;
    }

    Menu::operator unsigned int() const {
        return (unsigned int)(m_numItems);
    }

    Menu::operator bool() const {
        return m_numItems > 0;
    }

    ostream& operator<<(ostream& os, const Menu& menu) {
        menu.displayTitle(os);
        return os;
    }

    const char* Menu::operator[](int index) const {
        const char* menuItemContent = nullptr;
        if (m_numItems > 0) {
            int adjustedIndex = index % m_numItems;
            menuItemContent = (const char*)(*m_menuItems[adjustedIndex]);
        }
        return menuItemContent;
    }

}
