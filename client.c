#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>



int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    
    sock=socket(PF_INET,SOCK_STREAM,0);
    
    if (sock ==-1)
    {
        printf("socket Error\n");
        /* code */
    }

    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET; // tcp
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(7889);

    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        
    {
        printf("connect Error\n");
    }

    char msg[100];

    while (1)
    {
        scanf("%s",msg);
        printf("send: %s\n",msg);
        write(sock,msg,100);
        sleep(1);
        memset(msg, 0, sizeof(msg));
    }
    close(sock);  
    return 0;
}
