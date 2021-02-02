#include "../utils/network/socket_utils.h"
#include "./configure_server.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * create a server and use tcp to connect in
 */
int server_tcp() {
  // define
  int sfd, cfd, nread, nwrite;
  struct sockaddr_in caddr;
  socklen_t slen = sizeof(struct sockaddr_in);
  char buf[BUFSIZ];

  // implementation
  sfd = Socket_2();
  Bind_2(sfd, SERVER_ADDR, SERVER_PORT);
  Listen_2(sfd);
  cfd = Accept_2(sfd, &caddr, &slen);
  if (cfd < 0) {
    exit(EXIT_FAILURE);
  }
  nread = read(cfd, buf, BUFSIZ);
  if (nread < 0) {
    fprintf(stderr, "read message from client fail!");
    exit(EXIT_FAILURE);
  } else {
    fprintf(stdout, "msg from client: %s\n", buf);
  }
  nwrite = write(cfd, "hello client", sizeof("hello client"));
  if (nwrite > 0) {
    fprintf(stdout, "send message to client success!");
  } else {
    fprintf(stderr, "fail to send message to client");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main() {
  server_tcp();
  return 0;
}
