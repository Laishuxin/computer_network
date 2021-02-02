#include <stdio.h>


int main() {
    union {
        short s;
        char c[2];
    } u;
    u.c[0] = 0x11;
    u.c[1] = 0x22;

    printf("ox%x\n", u.s);
    printf("if output is ox1122, is big endian else little endian\n");
    return 0;
}
