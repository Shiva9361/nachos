/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid, i;
    PrintString("In exec\n");
    pid = ExecP("../test/add", 1);
    ExecP("../test/random", 2);
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
    }
    // Sleep(2000000);
    Wait2(pid);
    PrintString("In exec\n");
    // Sleep(2000000);
    // PrintString("Done\n");
    // pid = ExecP("../test/add", 1);
    // pid = ExecP("../test/test_syscall", 2);
    // for (i = 0; i < 10000000; i++);
    // PrintString("Hello");
}
