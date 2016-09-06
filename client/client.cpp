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
  unsigned short port  = 33333;
  struct sockaddr_in srvaddr;
  memset((char *)&srvaddr, 0, sizeof(srvaddr));
  srvaddr.sin_family = AF_INET;
  inet_pton(AF_INET, host, &srvaddr.sin_addr.s_addr);
  srvaddr.sin_port = htons(port);

  const char* my_message = "This is a test message";
  int st = sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
  if (st < 0) {
    perror("[ERROR]: sentto faild");
    return 0;
  }  
}
