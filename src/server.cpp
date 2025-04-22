#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

#define CLNT_MAX 10

int main(int argc, char const *argv[]) {
  int clnt_sock;
  int serv_sock;

  struct sockaddr_in serv_addr;

  struct sockaddr_in clnt_addr;
  int clnt_addr_size;

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  serv_addr.sin_family = AF_INET;  // addres
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // 어떤 주소로 bind 할것인가? ip주소가 바뀔때 마다 자동으로 갱신
  serv_addr.sin_port = htons(7889);  // 포트번호 지정

  if (bind(serv_sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) ==
      -1) {
    printf("bind error \n");
  }

  if (listen(serv_sock, 5) == -1) printf("listen error");

  char buff[100];
  int recv_len = 0;

  while (1) {
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr,
                       (socklen_t *)&clnt_addr_size);

    while (1) {
      recv_len = read(clnt_sock, buff, 100);
      if (recv_len == 0) {
        break;
      }

      printf("recv : ");

      for (size_t i = 0; i < recv_len; i++) {
        if (buff[i] == '\0') {
          break;
        }

        printf("%c", buff[i]);
      }

      printf("\n");
    }
  }

  // 몇명을 대기 시킬건가

  return 0;
}
