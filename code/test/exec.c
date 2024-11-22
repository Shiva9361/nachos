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
    for (i = 0; i < 3; i++) {
        pid = Exec("../test/test_syscall");
    }
    PrintString("Hello man");
    Sleep(10000000);
}
