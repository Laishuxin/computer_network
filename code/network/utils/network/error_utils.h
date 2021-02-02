#ifndef __ERROR_UTILS_H__
#define __ERROR_UTILS_H__
/***************************
 * error msg
 **************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define ERR_NULL_POINT "(error)null point error"
#define ERR_CREATE_SOCKET "(error)create socket error"
#define ERR_BIND_ADDR "(error)bind address error"
#define ERR_LISTEN_BACKLOG "(error)listen backlog error"
#define ERR_ACCEPT_CLIENT "(error)accept client error"
#define ERR_CONNECT_FAIL "(error)connect server error"
/**************************
 * error handler
 *************************/
#define HANDLE_ERROR(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)
#endif // __ERROR_UTILS_H__
