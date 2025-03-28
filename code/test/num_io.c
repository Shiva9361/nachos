/* num_io.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a syscall that read an interger and print it
 *
 */

#include "syscall.h"

int main() {
    char b[1000];
    char c[] = "Hi sir\n";
    int t = RecvMsg(b);

    PrintNum(t);
    // t = SendMsg(0, c);
    PrintString(b);
    PrintNum(t);
}
