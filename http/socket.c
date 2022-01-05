#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
  char sendbuffer[256];
  memset(sendbuffer, 0, sizeof(sendbuffer));
  snprintf(sendbuffer, sizeof(sendbuffer),
    "HTTP/1.1 200 OK\r\n"
    "Date: Mon, DD MMM YYYY H:MM:SS GMT\r\n"
    "Server: Apache/2.2\r\n"
    "Content-Length: 13\r\n"
    "\r\n"
    "Hello Client\r\n"
  );

  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server, client = {0};
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(9999);
  server.sin_family = AF_INET;

  bind(sock, (struct sockaddr *)&server, sizeof(server));

  listen(sock, 5);

  for (;;) {
    socklen_t length = sizeof(client);
    int sock2 = accept(sock, (struct sockaddr *)&client, &length);

    char buffer[256];
    recv(sock2, buffer, sizeof(buffer), 0);
    send(sock2, sendbuffer, sizeof(sendbuffer), 0);

    close(sock2);
  }

  close(sock);


  return 0;
}
