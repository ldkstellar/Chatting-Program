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
#define BUFFSIZE 200
int g_clnt_socks[CLNT_MAX];
int g_clnt_count = 0;
void *clnt_connection(void *arg) {

    int clnt_sock = *reinterpret_cast<int *>(arg);
    char msg[BUFFSIZE];
    int str_len = 0;
    int i;
    while (true) {
        str_len = read(clnt_sock, msg, sizeof(msg));
        if (str_len == -1) {
            printf("clnt[%d] close\n", clnt_sock);
            break;
        }
        printf("%s\n", msg);
    }
    close(clnt_sock);
    pthread_exit(0);
    return NULL;
}
int main(int argc, char const *argv[]) {
    int clnt_sock;
    int serv_sock;

    pthread_t t_thread;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET; // addres
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 어떤 주소로 bind 할것인가? ip주소가 바뀔때 마다 자동으로 갱신
    serv_addr.sin_port = htons(7889); // 포트번호 지정

    if (bind(serv_sock, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        printf("bind error \n");
    }

    if (listen(serv_sock, 5) == -1)
        printf("listen error");

    char buff[100];
    int recv_len = 0;

    while (true) {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, (socklen_t *) &clnt_addr_size);
        pthread_create(&t_thread, NULL, clnt_connection, (void *)&clnt_sock);
    }

    // 몇명을 대기 시킬건가

    return 0;
}
