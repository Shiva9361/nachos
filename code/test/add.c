/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int result;

	/*
    result = Mul(41, 57);
	PrintString("Hello World ");
	PrintNum(result);
	PrintString("\n");
	*/
	PrintString("Before\n");
	Sleep(5000000);
	PrintString("Bye\n");
	PrintString("Hello");	
    Halt();
    /* not reached */
}
