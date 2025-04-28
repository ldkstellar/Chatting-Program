#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_result;

    char id[100];
    strcpy(id, argv[1]);
    printf("id: %s\n", id);


    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        printf("socket Error\n");
    else {
        printf("Socket successfully created\n");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET; // tcp
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(7889);

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        printf("connect Error\n");
    } else {
        printf("Connected\n");
    }
    char msg[200];
    sprintf(msg, "[%s] : hello world\n", id);
    printf("while before");

    while (true) {

        printf("send: %s\n", msg);
        write(sock, msg, strlen(msg) + 1);
        sleep(2);
    }
    printf("while after");
    close(sock);
    return 0;
}
