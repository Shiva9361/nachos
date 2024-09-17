/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int result;
    int i;

    /*
    result = Mul(41, 57);
    PrintString("Hello World ");
    PrintNum(result);
    PrintString("\n");
    */
    // PrintString("Before\n");
    // Sleep(5000000);
    // PrintString("Bye\n");
    // PrintString("Hello");
    while (1) {
        for (i = 0; i < 1500000; i++);
        PrintString("In add\n");
    }
    Halt();
    /* not reached */
}
