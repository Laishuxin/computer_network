#include "./socket_utils.h"
#include "./config_utils.h"
#include "./error_utils.h"
#include <strings.h>

int Socket(int domain, int type, int protocol) {
  int sfd;
  sfd = socket(domain, type, protocol);
  if (sfd == -1) {
    HANDLE_ERROR(ERR_CREATE_SOCKET);
  }
  return sfd;
}

int Socket_2() { return Socket(AF_INET, SOCK_STREAM, 0); }

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int res;
  res = bind(sockfd, addr, addrlen);
  if (res == -1) {
    HANDLE_ERROR(ERR_BIND_ADDR);
  }
  return res;
}

static void _initSockAddr(struct sockaddr_in *saddr, const char *ip,
                          uint16_t port) {
  if (saddr == NULL) {
    fprintf(stderr, ERR_NULL_POINT);
    exit(1);
  }
  bzero(saddr, sizeof(struct sockaddr_in));
  saddr->sin_family = AF_INET;
  if (inet_aton(ip, &saddr->sin_addr) == 0) {
    fprintf(stderr, "(initailize socket address error!");
    exit(EXIT_FAILURE);
  }
  saddr->sin_port = htons(port);
}

int Init_addr(struct sockaddr_in *addr, const char *ip, u_int16_t port) {
  if (!addr || !ip) {
    fprintf(stderr, ERR_NULL_POINT);
    return -1;
  }
  _initSockAddr(addr, ip, port);
  return 1;
}
int Bind_2(int sockfd, const char *ip, uint16_t port) {
  if (ip == NULL) {
    HANDLE_ERROR(ERR_NULL_POINT);
  }
  int res;
  struct sockaddr_in addr;
  _initSockAddr(&addr, ip, port);
  res = Bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
  return res;
}

int Listen(int sockfd, int backlog) {
  int res;
  res = listen(sockfd, backlog);
  if (res == -1) {
    HANDLE_ERROR(ERR_LISTEN_BACKLOG);
  }
  return res;
}

int Listen_2(int sockfd) {
  return Listen(sockfd, CONFIG_DEFAULT_LISTEN_BACKLOG);
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  int cfd;
  cfd = accept(sockfd, addr, addrlen);
  if (cfd == -1) {
    fprintf(stderr, "(%s-%s)accept client fail", __DATE__, __TIME__);
  }
  return cfd;
}
int Accept_2(int sockfd, struct sockaddr_in *addr, socklen_t *addrlen) {
  return Accept(sockfd, (struct sockaddr *)addr, addrlen);
}

int Connect(int fd, const struct sockaddr *addr, socklen_t addrlen) {
  int sfd;
  sfd = connect(fd, addr, addrlen);
  if (sfd == -1) {
    HANDLE_ERROR(ERR_CONNECT_FAIL);
  }
  return sfd;
}

int Connect_2(int fd, const struct sockaddr_in *addr) {
  return Connect(fd, (struct sockaddr *)addr, sizeof(struct sockaddr));
}

int Close(int fd) {
  int res;
  res = close(fd);
  if (res == -1) {
    fprintf(stderr, "(%s-%s)close fd fail", __DATE__, __TIME__);
  }
  return res;
}

int Close_2(int fd, bool isServer) {
  int res;
  res = Close(fd);
  if (isServer && (res == -1)) {
    exit(EXIT_FAILURE);
  }
  return res;
}
