/*
 * show-rep
 *
 * This program looks under the covers to see what's actually in memory for
 * various C++ types.
 *
 * Feel free to edit the lines in main (at the bottom).  They should be
 * fairly self explanatory.
 */

#include <iostream>                 // provides std::cout, std::cin, std::endl
#include "show-rep-internals.hpp"   // provides the show_representation function
                                    // you do NOT need to look at that file


int main() {
    std::cout << "How integers are represented:\n" << std::endl;
    show_representation(1);
    show_representation(2);
    show_representation(3);
    show_representation(12345);
    show_representation(-1);
    show_representation(-42);
    std::cout << std::endl;

    std::cout << "Arrays do not store anything extra:\n" << std::endl;
    int array[6] = {1, 2, 3, 12345, -1, -42};
    show_representation(array);
    std::cout << std::endl;


    std::cout << "There are unsigned integers:\n" << std::endl;

    // The 'u' suffix makes this an unsigned integer literal.  The ~ operator
    // is the bitwise NOT operator, which flips all the bits in the number.
    show_representation(12345u);
    show_representation(~0u);
    std::cout << std::endl;

    std::cout << "And other sizes of integer:\n" << std::endl;

    // The 'l' suffix means a long integer literal.  The 'll' suffix
    // means a long long integer literal.  There is no suffix for a short
    // integer literal, so we have to write it out as short{42}.
    show_representation(short{42});
    show_representation(42ul);
    show_representation(987654321234567890ll);
    std::cout << std::endl;

    std::cout << "Characters are also really integers:\n" << std::endl;
    show_representation('*');
    for (signed char i = -3; i < 4; ++i) {
        show_representation(i);
    }
    std::cout << std::endl;

    char hello[5] = {'H', 'e', 'l', 'l', 'o'};
    show_representation(hello);
    std::cout << std::endl;

    std::cout << "How floating point numbers are represented:\n" << std::endl;
    // These are all float literals (rather than doubles) because they have
    // an 'f' suffix.
    show_representation(0.0f);
    show_representation(1.0f);
    show_representation(2.0f);
    show_representation(3.0f);
    show_representation(3.14159265358979323846264338327950288419717f);
    std::cout << std::endl;

    // These are all double literals.
    show_representation(0.0);
    show_representation(1.0);
    show_representation(2.0);
    show_representation(3.0);
    show_representation(3.14159265358979323846264338327950288419717);
    std::cout << std::endl;

    // These are all long double literals because they have an 'l' suffix.
    show_representation(0.0l);
    show_representation(1.0l);
    show_representation(2.0l);
    show_representation(3.0l);
    show_representation(3.14159265358979323846264338327950288419717l);
    std::cout << std::endl;

    return 0;
}
