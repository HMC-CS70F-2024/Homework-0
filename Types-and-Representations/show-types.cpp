/*
 * show-types
 *
 * This program looks under the covers to see what the properties of the
 * numeric types on a particular system are.
 *
 */

#include <cstddef>
#include <cstdint>
#include <iostream>                 // provides std::cout, std::cin, std::endl
#include "show-types-internals.hpp" // provides the SHOW_NUMTYPE_INFO macro
                                    // you do NOT need to look at that file

int main() {
    // The SHOW_NUMTYPE_INFO macro is defined in show-types-internals.hpp.
    // It takes a type and prints out information about that type.  Macros are
    // an advanced C++ feature we haven't learned about yet, so don't worry
    // about how it works.

    // Information about integer types

    SHOW_NUMTYPE_INFO(char);
    SHOW_NUMTYPE_INFO(short);
    SHOW_NUMTYPE_INFO(int);
    SHOW_NUMTYPE_INFO(long);
    SHOW_NUMTYPE_INFO(long long);

    SHOW_NUMTYPE_INFO(signed char);
    SHOW_NUMTYPE_INFO(unsigned char);
    SHOW_NUMTYPE_INFO(unsigned short);
    SHOW_NUMTYPE_INFO(unsigned int);
    SHOW_NUMTYPE_INFO(unsigned long);
    SHOW_NUMTYPE_INFO(unsigned long long);

    SHOW_NUMTYPE_INFO(bool);

    // Information about some type aliases
    SHOW_NUMTYPE_INFO(size_t);      // Maximum size of anything in memory
    SHOW_NUMTYPE_INFO(ptrdiff_t);   // Essentially a signed size_t
    SHOW_NUMTYPE_INFO(int64_t);     // 64-bit signed integer
    SHOW_NUMTYPE_INFO(uint8_t);     // 8-bit unsigned integer

    // Information about floating point types

    SHOW_NUMTYPE_INFO(float);
    SHOW_NUMTYPE_INFO(double);
    SHOW_NUMTYPE_INFO(long double);

    return 0;
}
