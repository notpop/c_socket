#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server, client = {0};
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(9999);
  server.sin_family = AF_INET;

  bind(sock, (struct sockaddr *)&server, sizeof(server));

  listen(sock, 1);

  socklen_t length = sizeof(client);
  int sock2 = accept(sock, (struct sockaddr *)&client, &length);

  char buffer[256];
  recv(sock2, buffer, sizeof(buffer), 0);
  printf("%s\n", buffer);

  close(sock);
  close(sock2);

  return 0;
}
