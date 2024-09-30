/* test_syscall.c
 *	Simple program to test whether the systemcall interface works.
 */

#include "syscall.h"

int main() {
    int i;
    int result = Add(1, 2);
    /* Don't need to Halt() anymore because the PC will increase automatically
     */
    result = Add(2, 3);
    for (i = 0; i < 10000000; i++);
    PrintString("Bye from Grandchild");
}
