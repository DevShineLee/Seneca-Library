#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20;
    class MenuItem {
        char* m_content;
        friend class Menu;
        MenuItem();
        MenuItem(const char* content = nullptr);
        ~MenuItem();
        MenuItem(const MenuItem& other) = delete;
        MenuItem& operator=(const MenuItem& other) = delete;
        bool isEmpty() const;
        void display(std::ostream& os) const;
        operator bool() const;
        operator const char* () const;
    };

    class Menu {
        MenuItem* m_title;
        MenuItem* m_menuItems[MAX_MENU_ITEMS];
        unsigned int m_numItems;
    public:
        Menu();
        Menu(const char* title);
        ~Menu();

        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

        void displayTitle(std::ostream& os) const;
        void displayMenu(std::ostream& os) const;
        int run() const;

        int operator~() const;
        Menu& operator<<(const char* menuItemContent);

        operator int() const;
        operator unsigned int() const;
        operator bool() const;

        const char* operator[](int index) const;
    };

    std::ostream& operator<<(std::ostream& os, const Menu& menu);
}
#endif // SDDS_MENU_H__
