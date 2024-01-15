/*  _  ___   ___        _                      
   / |/ _ \ / _ \    __| | ___   ___  _ __ ___ 
   | | | | | | | |  / _` |/ _ \ / _ \| '__/ __|
   | | |_| | |_| | | (_| | (_) | (_) | |  \__ \
   |_|\___/ \___/   \__,_|\___/ \___/|_|  |___/   an example problem
                                            
   There are 100 doors in a row that are all initially closed.

   You make 100 passes by the doors.
   * The first time through, visit every door and toggle the door
     (i.e., if the door is closed, open it;  if it is open, close it).
   * The second time, only visit every 2nd door (door #2, #4, #6, ...),
     and toggle it.
   * The third time, visit every 3rd door (door #3, #6, #9, ...), etc,
   ... until you only visit the 100th door.

                        (original problem seen on rosettacode.org)

   You can compile this code and make an executable with:
   
       cc -c doors-in-c.c
       cc -o doors-in-c doors-in-c.o
       
   and then run the resulting executable with:
   
       ./doors-in-c
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    bool isOpen[100] = {};

    for (int step = 1; step <= 100; ++step) {
        for (int door = step-1; door < 100; door += step) {
            isOpen[door] = !isOpen[door];
        }
    }

    for (int door = 0; door < 100; ++door) {
        if (isOpen[door]) {
            printf("Door %d is open\n", door+1);
        }
    }

    return 0;
}