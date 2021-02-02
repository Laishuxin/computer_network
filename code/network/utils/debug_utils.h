#ifndef __DEBUG_UTILS__
#define __DEBUG_UTILS__
#include <stdio.h>
#define ERROR_PRINTF(msg) fprintf(stderr, "(debug)error: %s\n", msg);
#define SUCCESS_PRINTF(msg) fprintf(stdout, "(debug)log: %s\n", msg);
#endif // __DEBUG_UTILS__
