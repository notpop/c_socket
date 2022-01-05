#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server = {0};
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(9999);
  server.sin_family = AF_INET;

  connect(sock, (struct sockaddr *)&server, sizeof(server));

  char buffer[256] = "Hello World!!";
  send(sock, buffer, sizeof(buffer), 0);

  close(sock);

  return 0;
}
