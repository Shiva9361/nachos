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
    PrintString("In exec\n");
    // Sleep(2000000);
    Wait2(pid);
    Sleep(2000000);
    PrintString("Done\n");
}
