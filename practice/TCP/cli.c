#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
    char str[50];
    struct sockaddr_in serv;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*) &serv, sizeof(serv));

    while (1)
    {
        bzero(str, 50);
        printf("CLIENT:");
        fgets(str, 50, stdin);
        send(sock, str, 50, 0);

        if(strstr(str, "bye")!=NULL)
            break;

        bzero(str, 50);
        recv(sock, str, 50, 0);
        printf("SERVER: %s", str);
    }
    close(sock);
}