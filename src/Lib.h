#ifndef SDDS_LIB_H__
#define SDDS_LIB_H__
namespace sdds {
    const int SDDS_MAX_LOAN_DAYS = 15;
    // maximum number of day a publication can be borrowed with no penalty
    const int SDDS_TITLE_WIDTH = 30;
    // The width in which the title of a publication should be printed on the console
    const int SDDS_AUTHOR_WIDTH = 15;
    // The width in which the author name of a book should be printed on the console
    const int SDDS_SHELF_ID_LEN = 4;
    // The width in which the shelf id of a publication should be printed on the console
    //const int SDDS_LIBRARY_CAPACITY = 5000;
    // Maximum number of publications the library can hold.

    // MS5
    const int SDDS_MAX_FILENAME = 256;
    const int SDDS_MAX_TITLE = 256;
    const int SDDS_MAX_AUTHOR_NAME = 256;
    const int SDDS_LIBRARY_CAPACITY = 333;
}
#endif //SDDS_LIB_H__