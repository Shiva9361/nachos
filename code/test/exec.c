/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid, i;
    PrintString("In exec\n");
    pid = Exec("../test/add");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
    }
    while (1) {
        for (i = 0; i < 3000000; i++);
        PrintString("In exec\n");
    }
    Halt();
}
