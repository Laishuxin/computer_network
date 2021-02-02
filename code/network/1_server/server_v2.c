#include "../utils/network/socket_utils.h"
#include "./configure_server.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * create a server and use tcp to connect in
 */
int run() {
  // define
  int sfd, cfd, nread, nwrite;
  uint32_t cport = 0;
  struct sockaddr_in caddr;
  socklen_t slen = sizeof(struct sockaddr_in);
  char buf[BUFSIZ];
  char clientIpBuf[BUFSIZ];

  // implementation
  sfd = Socket_2();
  Bind_2(sfd, SERVER_ADDR, SERVER_PORT);
  Listen_2(sfd);
  cfd = Accept_2(sfd, &caddr, &slen);
  if (cfd < 0) {
    exit(EXIT_FAILURE);
  }

  // show information about client
  inet_ntop(cfd, &caddr.sin_addr, clientIpBuf, sizeof(struct sockaddr_in));
  cport = ntohl(caddr.sin_port);
  printf("accept client: ip=%s, port = %d\n", clientIpBuf, cport);

  while (1) {
    nread = read(cfd, buf, BUFSIZ);
    if (nread < 0) {
      fprintf(stderr, "read message from client fail!");
      exit(EXIT_FAILURE);
    }
    printf("(server): read message from client:%s\n", buf);

    int len = strlen(buf);
    char c;
    for (int i = 0; i < len; ++i) {
      c = buf[i];
      buf[i] = toupper(c);
    }
    nwrite = write(cfd, buf, len + 1);
    if (nwrite <= 0) {
      fprintf(stderr, "fail to send message to client");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}

int main() {
  run();
  return 0;
}
