// builtin
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>

// customize
#include "configure_server.h"
#define HANDLE_ERROR(msg) \
    do {perror(msg); exit(EXIT_FAILURE);}  while(0)
#define ERR_NULL_POINT "(null point error)"
#define ERR_SERVER_BIND "(server bind error)"
#define LISTEN_BACKLOG 50
#define ERR_SERVER_LISTEN "(server listen error)"

#ifdef DEBUG
#include "../utils/debug_utils.h"
#endif

int createSocket() {
    int sfd;
    sfd = socket(AF_INET, SOCK_STREAM, 0); // default protocol
    if (sfd == -1) {
        perror("create socket fail");
        exit(1);
    }
    return sfd;
}

static void _initSockAddr(struct sockaddr_in *saddr) {
    if (saddr == NULL) {
        fprintf(stderr, ERR_NULL_POINT);
        exit(1);
    }
    bzero(saddr, sizeof(struct sockaddr_in));
    saddr->sin_family = AF_INET;
    if (inet_aton(SERVER_ADDR, &saddr->sin_addr) == 0) {
        fprintf(stderr, "(initailize socket address error!");
        exit(EXIT_FAILURE);
    }
    saddr->sin_port = htons(SERVER_PORT);
}

void bindAddr(int sfd) {
    struct sockaddr_in saddr; 
    int res = 0;
    _initSockAddr(&saddr);
    res = bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr));
    if (res == -1) {
        perror(ERR_SERVER_BIND);
        exit(1);
    }
}

void setListen(int sfd) {
    if(listen(sfd,  LISTEN_BACKLOG) == -1) {
        HANDLE_ERROR(ERR_SERVER_LISTEN);
    }
}

int acceptRequest(int sfd) {
    struct sockaddr_in caddr;
    socklen_t caddrLen;
    int cfd;
    caddrLen = sizeof(struct sockaddr);
    cfd = accept(sfd, (struct sockaddr *)&caddr, &caddrLen);
    if (cfd == -1) {
        HANDLE_ERROR("accept client fail");
    }
    return cfd;
}
void readMsg(int fd) {
    int rlen;
    char buf[BUFSIZ];
    rlen = read(fd, buf, BUFSIZ);
    printf("read msg: %s, len = %d\n", buf, rlen);
}
void sendMsg(int fd) {
    int wlen;
    char msg[] = "hello\n";
    // char buf[BUFSIZ];
    //strncpy(buf, msg, sizeof(msg));
    wlen = write(fd,msg, 7);
}

void closeSocket(int fd) {
    if (close(fd) == -1) {
        HANDLE_ERROR("close socket error");
    }
}

int main() {
    int sfd = createSocket();
#ifdef DEBUG
    SUCCESS_PRINTF("create socket success!");
#endif
    bindAddr(sfd);
#ifdef DEBUG
    SUCCESS_PRINTF("bind address success!");
#endif
    setListen(sfd); 
#ifdef DEBUG
    SUCCESS_PRINTF("listen success!");
#endif
    int cfd = acceptRequest(sfd);
#ifdef DEBUG
    SUCCESS_PRINTF("accept client success");
    printf("cfd = %d\n", cfd);
#endif
    readMsg(cfd);
    sendMsg(cfd);
    closeSocket(cfd);
    closeSocket(sfd);
    return 0;
}
