#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    perror("[ERROR]: Cannot create socket");
    return 0;
  }

  const char* host = "127.0.0.1";
  int port = 33333;
  struct sockaddr_in srvaddr;
  memset((char *)&srvaddr, 0, sizeof(srvaddr));
  srvaddr.sin_family = AF_INET;
  inet_pton(AF_INET, host, &srvaddr.sin_addr.s_addr);
  srvaddr.sin_port = htons(port);

  int bd = bind(fd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
  if (bd < 0) {
    perror("[ERROR]: Cannot bind socket");
    return 0;
  }

  int recvlen;
  size_t bufsize = 2048;
  unsigned char buf[bufsize];
  struct sockaddr_in remaddr;
  socklen_t addrlen = sizeof(remaddr);
  for (;;) {
    printf("waiting on port %d\n", port);
    recvlen = recvfrom(fd, buf, bufsize, 0, (struct sockaddr *)&remaddr, &addrlen);
    if (recvlen > 0) {
      buf[recvlen] = 0;
      printf("received message: \%s\n", buf);
    }
  }
}
