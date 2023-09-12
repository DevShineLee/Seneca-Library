#include <iostream>
#include <iomanip>
#include <cstring>
#include "Streamable.h"
using namespace std;
namespace sdds {
    ostream& operator<<(ostream& ostr, const Streamable& stream) {
        if(stream) {
            stream.write(ostr);
        }
        return ostr;
    }
    istream& operator>>(istream& istr, Streamable& stream) {
        return (stream.read(istr));
    }
}