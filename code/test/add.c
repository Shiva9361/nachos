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
    int pid;

    result = Mul(41, 57);
    PrintString("Hello World ");
    PrintString("\n");
    PrintNum(result);
    PrintString("\n");

    // pid = ExecP("../test/test_syscall");
    PrintString("Before\n");
    // Wait2(pid);
    PrintString("Bye\n");
    // PrintString("Hello");
    PrintString("Byeeeeeeeee\n");
    // for (i = 0; i < 1500000; i++);
    // Sleep(10000000);
    PrintString("Byeeee from child\n");
    // Exit(0);
    /* not reached */
}
