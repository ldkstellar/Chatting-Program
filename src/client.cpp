#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

void *recv(void *arg) {
  int sock = *reinterpret_cast<int *>(arg);
  char buff[500];
  int len;
  while (true) {
    len = read(sock, buff, sizeof(buff));
    if (len == -1) {
      printf("sock close\n");
      break;
    }
    printf("%s", buff);
  }
  pthread_exit(0);
  return NULL;
}

int main(int argc, char const *argv[]) {
  int sock;
  struct sockaddr_in serv_addr;
  pthread_t rcv_thread;
  void *thread_result;

  char id[100];
  if (argc < 2) {
    printf("you have to enter ID\n");
    return 0;
  }
  strcpy(id, argv[1]);

  printf("id: %s\n", id);

  sock = socket(PF_INET, SOCK_STREAM, 0);

  if (sock == -1)
    printf("socket Error\n");
  else {
    printf("Socket successfully created\n");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;  // tcp
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(7889);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    printf("connect Error\n");
  } else {
    printf("Connected\n");
  }

  // pthread_create(&rcv_thread, NULL, recv, reinterpret_cast<void *>(sock));
  char chat[100];
  char msg[1000];

  printf("while before\n");

  while (true) {
    std::cin.getline(chat, sizeof(chat));
    sprintf(msg, "[%s] :%s", id, chat);
    printf("send: %s\n", msg);
    write(sock, msg, strlen(msg) + 1);
    sleep(2);
  }
  printf("while after");
  close(sock);
  return 0;
}
