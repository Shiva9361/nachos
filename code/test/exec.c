/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1
int a[999];
int main() {
    int pid, i;
    a[1];
    pid = Exec("../test/test_syscall");
    PrintString("Hello man");
    Wait2(pid);
    // Join(pid);
}
