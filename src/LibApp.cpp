#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"
#include "PublicationSelector.h"
using namespace std;
namespace sdds {

    LibApp::LibApp(const char* fileName) : m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_publicationType("Choose the type of publication:") {

        strcpy(m_fileName, fileName);
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

    Publication* LibApp::getPub(int libRef) {
        Publication* result = nullptr;
        for (int i = 0; i < m_NOLP; i++)
        {
            if (m_PPA[i]->getRef() == libRef) {
                result = m_PPA[i];
            }
        }
        return result;
    }

    bool LibApp::confirm(const char* message) {
        Menu confirmMenu(message);
        confirmMenu << "Yes";
        int selection = confirmMenu.run();
        return (selection == 1);
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream file(m_fileName);
        char pubType = 'x';
        int i = 0;

        while (file && i < SDDS_LIBRARY_CAPACITY) {
            file >> pubType;
            file.ignore();

            if (file) {
                if (pubType == 'P')
                    m_PPA[i] = new Publication;
                else if (pubType == 'B')
                    m_PPA[i] = new Book;

                if (m_PPA[i]) {
                    file >> *m_PPA[i];
                    m_NOLP++;
                    m_LLRN = m_PPA[i]->getRef();
                }
            }
            i++;
        }
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream file(m_fileName);
        for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() != 0) {
                file << *m_PPA[i] << endl;
            }
        }
        file.close();
    }

    int LibApp::search(int searchType) {
        char title[SDDS_MAX_TITLE]{};
        int selectedType = 0;
        int i = 0;
        int libRef = 0;
        char type = 'z';
        PublicationSelector pubSel("Select one of the following found matches:", 15);

        selectedType = m_publicationType.run();
        if (selectedType == 1) {
            type = 'B';
        }
        else if (selectedType == 2) {
            type = 'P';
        }

        cin.ignore(1000, '\n');
        cout << "Publication Title: ";
        cin.getline(title, SDDS_MAX_TITLE);

        if (searchType == 1) {
            for (i = 0; i < m_NOLP; i++) {
                if (*m_PPA[i] == title && 
                    type == m_PPA[i]->type() &&
                    m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
        }
        else if (searchType == 2) {
            for (i = 0; i < m_NOLP; i++) {
                if (*m_PPA[i] == title && 
                    m_PPA[i]->onLoan() && 
                    type == m_PPA[i]->type() && 
                    m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
        }
        else if (searchType == 3) {
            for (i = 0; i < m_NOLP; i++) {
                if (*m_PPA[i] == title && 
                    !m_PPA[i]->onLoan() && 
                    type == m_PPA[i]->type() && 
                    m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
        }
        if (pubSel) {
            pubSel.sort();
            libRef = pubSel.run();
            if (libRef > 0) {
                cout << *getPub(libRef) << endl;
            }
            else {
                cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }
        return libRef;
    }

    void LibApp::run() {
        int selection, exit;
        do {
            selection = m_mainMenu.run();
            switch (selection) {
            case 0:
                if (m_changed == true) {
                    exit = m_exitMenu.run();
                    switch (exit) {
                    case 0:
                        if (confirm("This will discard all the changes are you sure?")) {
                            m_changed = false;
                        }
                        break;
                    case 1:
                        save();
                        break;
                    case 2:
                        selection = 1;
                        break;
                    }
                }
                cout << endl;
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
            }
        } while (selection != 0);

        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }

    void LibApp::newPublication() {
        if (m_NOLP == SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
            cout << endl;
        }
        else {
            cout << "Adding new publication to the library" << endl;
            int pubType = m_publicationType.run();
            cin.ignore(1000, '\n');

            Publication* newPub = nullptr;
            if (pubType == 1) {
                newPub = new Book;
            }
            else if (pubType == 2) {
                newPub = new Publication;
            }

            if (!newPub) {
                cout << "Aborted!" << endl;
                cout << endl;
            }
            else {
                cin >> *newPub;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    delete newPub;
                    cout << "Aborted!" << endl;
                }
                else {
                    confirm("Add this publication to the library?");
                    if (newPub->conIO(cin) && newPub->operator bool()) {
                        newPub->setRef(++m_LLRN);
                        m_PPA[m_NOLP++] = newPub;
                        m_changed = true;
                        cout << "Publication added" << endl;
                        cout << endl;
                    }
                    else {
                        cout << "Failed to add publication!" << endl;
                        delete newPub;
                    }
                }
            }
        }
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int libRef = search(1);
        if (libRef) {
            if (confirm("Remove this publication from the library?")) {
                getPub(libRef)->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
        cout << endl;
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int libRef = search(3);
        if (libRef > 0) {
            if (confirm("Check out publication?")) {
                cout << "Enter Membership number: ";
                int membership;
                do {
                    cin >> membership;
                    if (cin.fail() || membership < 10000 || membership > 99999) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid membership number, try again: ";
                    }
                } while (membership < 10000 || membership > 99999);
                getPub(libRef)->set(membership);
                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
        cout << endl;
    }

    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int libRef = search(2);
        if (libRef > 0) {
            if (confirm("Return Publication?")) {
                int days = Date() - getPub(libRef)->checkoutDate();

                if (days > SDDS_MAX_LOAN_DAYS) {
                    double penalty = (days - SDDS_MAX_LOAN_DAYS) * 0.5;
                    cout << fixed << setprecision(2);
                    cout << "Please pay $" << penalty << " penalty for being " << (days - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
                }
                getPub(libRef)->set(0);
                m_changed = true;
            }
            cout << "Publication returned" << endl;
        }
        cout << endl;
    }
}
