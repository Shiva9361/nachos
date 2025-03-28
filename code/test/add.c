/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"
char b[10000];
int main() {
    int result;
    int i;
    int pid;
    char a[] = "Hello beta\n";

    pid = Exec("../test/num_io");
    i = SendMsg(pid, a);
    result = SendMsg(3, a);
    result = i;
    PrintNum(i);
    PrintNum(result);
    PrintString("\n");
    // i = RecvMsg(b);
    PrintNum(i);
    PrintString("\n");
    PrintString(b);
    // Exit(0);
    /* not reached */
}
