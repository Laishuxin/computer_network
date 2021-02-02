/******************************
 * provide better utils for socket programing
 *****************************/
#ifndef __SOCKET_UTILS_H__
#define __SOCKET_UTILS_H__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

/*****************************
 * macro define
 ****************************/
int Socket(int domain, int type, int protocol);
int Socket_2();
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Bind_2(int sockfd, const char *ip, uint16_t port);
int Listen(int sockfd, int backlog);
int Listen_2(int sockfd);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Accept_2(int sockfd, struct sockaddr_in *addr, socklen_t *addrlen);
int Close(int fd);
int Close_2(int fd, bool isServer);
#endif //__SOCKET_UTILS_H__
