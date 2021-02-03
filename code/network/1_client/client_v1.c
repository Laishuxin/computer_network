#include "../utils/network/socket_utils.h"
#include "./configure_client.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void run() {
  // initalization
  printf("(client)startting...\n");
  int cfd, sfd, nwrite, nread;
  struct sockaddr_in saddr;
  // char *msg = "hello, i am client";
  char buf[BUFSIZ];

  bzero(&saddr, sizeof(struct sockaddr_in));
  // implementation
  cfd = Socket_2();
  // Bind_2(cfd, CLIENT_ADDR, CLIENT_PORT);
  Init_addr(&saddr, BAIDU_SERVER_ADDR, SERVER_PORT);
  sfd = Connect_2(cfd, &saddr);
  printf("(client)server fd = %d\n", sfd);

  if (sfd < 0) {
    fprintf(stderr, "connect server fail\n");
    exit(EXIT_FAILURE);
  }
  printf("(client)connect server successfully!\n");
  while (fgets(buf, BUFSIZ, stdin)) {
    nwrite = write(sfd, buf, strlen(buf));
    if (nwrite <= 0) {
      fprintf(stderr, "(client)write fail\n");
      exit(EXIT_FAILURE);
    }
    bzero(buf, BUFSIZ);
    nread = read(sfd, buf, BUFSIZ);
    if (nread <= 0) {
      fprintf(stderr, "(client)read fail\n");
      exit(EXIT_FAILURE);
    }
    buf[nread] = '\0';
    printf("(client)read message from server:%s\n", buf);
  }
  Close(sfd);
  Close(cfd);
  printf("(client)ending...\n");
}

int main() {
  run();
  return 0;
}
